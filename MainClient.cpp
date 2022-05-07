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

            constexpr int dataSendSize = 256;
            char dataSend[dataSendSize];
            memset(dataSend, '\0' ,sizeof(dataSend));

            int socketForClient = JoinServer();

			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//The dot that will be moving around on the screen
			Player player1(72, 300);
			Player player2(1032, 350);
			Prof Prof1(72, 325);
			//Prof Prof2(60, 300);
			//Prof Prof3(60, 400);
			//Prof Prof4(648, 744);
			//Prof Prof5(348, 72);

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

				//Move the dot
				player2.movePlayer(map);
				Prof1.moveProf(player1 , player2, map);
				//Prof2.moveProf(player1 , player2, map);
				//Prof3.moveProf(player1 , player2, map);
				//Prof4.update(player1 , player2, map);
				//Prof5.update(player1 , player2, map);
				

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
							gBackgroundTexture.render(gRenderer, TILE_SIZE*j,TILE_SIZE*i);
						}
                        else if(map[i][j] == 1){
							gRoadTexture.render(gRenderer, TILE_SIZE*j,TILE_SIZE*i);
						}
						else if(map[i][j] == 2){
							gGrassTexture.render(gRenderer, TILE_SIZE*j,TILE_SIZE*i);
						}
						else if(map[i][j] == 3){
							gBuildingTexture.render(gRenderer, TILE_SIZE*j,TILE_SIZE*i);
						}
					}
				}
			
				player1.renderPlayer(gRenderer, gPlayer1Texture);
				player2.renderPlayer(gRenderer, gPlayer2Texture);
				Prof1.renderProf(gRenderer, gProfTexture);
				//Prof2.renderProf(gRenderer, gProfTexture);
				//Prof3.renderProf(gRenderer, gProfTexture);
				//Prof4.renderProf(gRenderer, gProfTexture);
				//Prof5.renderProf(gRenderer, gProfTexture);

			//Update screen
				SDL_RenderPresent( gRenderer );

			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}