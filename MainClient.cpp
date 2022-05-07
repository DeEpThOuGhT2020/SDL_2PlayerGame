#include "Game.h"
#include "Player.h"
#include "Constants.h"
#include "Prof.h"

// For multiplayer we need tcp/ip support
#include <sys/types.h> //contains a number of basic derived types that should be used whenever appropriate
#include <arpa/inet.h> // defines in_addr structure
#include <sys/socket.h> // for socket creation
#include <netinet/in.h> //contains constants and structures needed for internet domain addresses
#include <netdb.h>
#include <unistd.h>

int JoinServer(){
	int socketCreated = 0;
	struct sockaddr_in ipOfServer;
	socketCreated = socket(AF_INET, SOCK_STREAM, 0); // creating socket
	memset(&ipOfServer, '0', sizeof(ipOfServer));
	ipOfServer.sin_family = AF_INET;
	// Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "127.0.0.1", &ipOfServer.sin_addr)<=0) 
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }	
	ipOfServer.sin_port = htons(PORT); // this is the port number of running server

 	if (connect(socketCreated, (struct sockaddr *)&ipOfServer, sizeof(ipOfServer)) < 0){
        printf("\nConnection Failed \n");
        return -1;
    }	
	return socketCreated;
}

int main( int argc, char* args[] ){
	//Start up SDL and create window
	if( !init() ){
		printf( "Failed to initialize!\n" );
	}
	else{
		//Load media
		if( !loadMedia() ){
			printf( "Failed to load media!\n" );
		}
		else{

            int dataSendSize = 256;
            char dataSend[dataSendSize];
            memset(dataSend, '\0' ,sizeof(dataSend));

            int socketForClient = JoinServer();

			//Main loop flag
			bool quit = false;
			bool start=true;
			bool popped = false;

			int task1, task2;
			int x1, y1, x2, y2;

			bool completed1=false;
			bool completed2=false;

			//Event handler
			SDL_Event e;

			//The players and profs that will be moving around on the screen
			Player player1(72, 300);
			Player player2(1032, 348);
			Prof Prof1(12, 12);
			Prof Prof2(1152, 432);
			Prof Prof3(660, 648);
			Prof Prof4(660, 156);
			Prof Prof5(348, 72);

			//While application is running
			while( !quit ){
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 ){
					//User requests quit
					if( e.type == SDL_QUIT ){
						quit = true;
					}

					//Handle input for the dot
					player2.handleEvent( e );
				}

				//Move the players and profs
				player2.movePlayer(map);
				Prof1.moveProf(player1 , player2, map);
				Prof2.moveProf(player1 , player2, map);
				Prof3.moveProf(player1 , player2, map);
				Prof4.moveProf(player1 , player2, map);
				Prof5.moveProf(player1 , player2, map);

			// Handle server/client communication

                // Receive player1 position from server
                memset(dataSend, '\0', dataSendSize);
                int sizeRead = read(socketForClient, dataSend, dataSendSize);
                memcpy(&player1.mPosX, &dataSend[0 * sizeof(int)], sizeof(int));
                memcpy(&player1.mPosY, &dataSend[1 * sizeof(int)], sizeof(int));

				// Send player2 position to client
				memset(dataSend, '\0', dataSendSize);
				memcpy(&dataSend[0 * sizeof(int)], &player2.mPosX, sizeof(int));
				memcpy(&dataSend[1 * sizeof(int)], &player2.mPosY, sizeof(int));
				send(socketForClient, dataSend, sizeof(int) * 2, 0);


			//Clear screen
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );


			//Render objects
				for (int i = 0 ; i < 70 ; i++){
					for (int j = 0 ; j < 100 ; j ++){
						if (map[i][j] == 0){
							gBackgroundTexture.render(gRenderer, TILE_SIZE*j,TILE_SIZE*i, TILE_SIZE, TILE_SIZE);
						}
                        else if(map[i][j] == 1){
							gRoadTexture.render(gRenderer, TILE_SIZE*j,TILE_SIZE*i, TILE_SIZE, TILE_SIZE);
						}
						else if(map[i][j] == 2){
							gGrassTexture.render(gRenderer, TILE_SIZE*j,TILE_SIZE*i, TILE_SIZE, TILE_SIZE);
						}
						else if(map[i][j] == 3){
							gBuildingTexture.render(gRenderer, TILE_SIZE*j,TILE_SIZE*i, TILE_SIZE, TILE_SIZE);
						}
					}
				}

				if(Prof1.collided(player1) || Prof2.collided(player1) || Prof3.collided(player1) || Prof4.collided(player1) || Prof5.collided(player1))	player1.transport();
                
                if(Prof1.collided(player2) || Prof2.collided(player2) || Prof3.collided(player2) || Prof4.collided(player2) || Prof5.collided(player2))	player2.transport();
			
				player1.renderPlayer(gRenderer, gPlayer1Texture);
				player2.renderPlayer(gRenderer, gPlayer2Texture);
				Prof1.renderProf(gRenderer, gProfTexture);
				Prof2.renderProf(gRenderer, gProfTexture);
				Prof3.renderProf(gRenderer, gProfTexture);
				Prof4.renderProf(gRenderer, gProfTexture);
				Prof5.renderProf(gRenderer, gProfTexture);

				completed1=player1.completedTask(task1);
				completed2=player1.completedTask(task2);
				
				if (start){
					WTexture::renderText(gRenderer, gFont, (char *)"Welcome! Your tasks are being generated!", 200, 0, TEXT_WIDTH, TEXT_HEIGHT);
					SDL_RenderPresent( gRenderer );
					SDL_Delay(3000);

					srand(time(0));

					task1 = rand()%7;
					task2 = rand()%7;
					WTexture::renderText(gRenderer, gFont, ("Player1: "+tasks[task1]).c_str(), 100, 2*TEXT_HEIGHT, TEXT_WIDTH, TEXT_HEIGHT);
					WTexture::renderText(gRenderer, gFont, ("Player2: "+tasks[task2]).c_str(), 100, 3*TEXT_HEIGHT, TEXT_WIDTH, TEXT_HEIGHT);

					SDL_RenderPresent( gRenderer );
					SDL_Delay(10000);

					x1 = std::get<0>(locPoints[task1]);
					y1 = std::get<1>(locPoints[task1]);
					x2 = std::get<0>(locPoints[task2]);
					y2 = std::get<1>(locPoints[task2]);
					start=false;
				}

				if (completed1){
					WTexture::renderText(gRenderer, gFont, (char *)"Player1 has won the game!", 200, 0, TEXT_WIDTH, TEXT_HEIGHT);
					SDL_RenderPresent( gRenderer );
					SDL_Delay(10000);
					quit = true;
				}

				if (completed2){
					WTexture::renderText(gRenderer, gFont, (char *)"Player2 has won the game!", 200, 0, TEXT_WIDTH, TEXT_HEIGHT);
					SDL_RenderPresent( gRenderer );
					SDL_Delay(10000);
					quit = true;
				}

				gTask1.render(gRenderer, x1, y1, TILE_SIZE, TILE_SIZE);
				gTask2.render(gRenderer, x2, y2, TILE_SIZE, TILE_SIZE);

			//Update screen
				SDL_RenderPresent( gRenderer );
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}