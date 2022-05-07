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

int WaitForPlayerToJoin(){
	int server_socket = 0, client_socket = 0;
	struct sockaddr_in ipOfServer;
	server_socket = socket(AF_INET, SOCK_STREAM, 0); // creating socket
	memset(&ipOfServer, '0', sizeof(ipOfServer));
	ipOfServer.sin_family = AF_INET;
	ipOfServer.sin_addr.s_addr = htonl(INADDR_ANY);
	ipOfServer.sin_port = htons(PORT); // this is the port number of running server
	bind(server_socket, (struct sockaddr*)&ipOfServer , sizeof(ipOfServer));
	listen(server_socket , 1); // Start listening

	client_socket = accept(server_socket, (struct sockaddr*)NULL, NULL);
	return client_socket;
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

			int socketForClient = WaitForPlayerToJoin();

			constexpr int dataSendSize = 256;
			char dataSend[dataSendSize];
			memset(dataSend, '\0' ,dataSendSize);

			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//The players and profs that will be moving around on the screen
			Player player1(72, 300);
			Player player2(1032, 350);
			Prof Prof1(72, 380);
			Prof Prof2(1152, 434);
			Prof Prof3(660, 648);
			//Prof Prof4(660, 156);
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
					player1.handleEvent( e );
				}

				//Move the players and profs
				player1.movePlayer(map);
				Prof1.moveProf(player1 , player2, map);
				Prof2.moveProf(player1 , player2, map);
				Prof3.moveProf(player1 , player2, map);
				//Prof4.update(player1 , player2, map);
				//Prof5.update(player1 , player2, map);

			// Handle server/client communication

				// Send player1 position to client
				memset(dataSend, '\0', dataSendSize);
				memcpy(&dataSend[0 * sizeof(int)], &player1.mPosX, sizeof(int));
				memcpy(&dataSend[1 * sizeof(int)], &player1.mPosY, sizeof(int));
				send(socketForClient, dataSend, sizeof(int) * 2, 0);

				// Receive player2 position from server
                memset(dataSend, '\0', dataSendSize);
                int sizeRead = read(socketForClient, dataSend, dataSendSize);
                memcpy(&player2.mPosX, &dataSend[0 * sizeof(int)], sizeof(int));
                memcpy(&player2.mPosY, &dataSend[1 * sizeof(int)], sizeof(int));

			
			//Clear screen
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );

				Prof1.collided(player1);
				Prof1.collided(player2);
				Prof2.collided(player1);
				Prof2.collided(player2);
				Prof3.collided(player1);
				Prof3.collided(player2);
				//Prof4.collided(player1);
				//Prof4.collided(player2);
				//Prof5.collided(player1);
				//Prof5.collided(player2);

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

				player1.renderPlayer(gRenderer, gPlayer1Texture);
				player2.renderPlayer(gRenderer, gPlayer2Texture);
				Prof1.renderProf(gRenderer, gProfTexture);
				//Prof2.renderProf(gRenderer, gProfTexture);
				//Prof3.renderProf(gRenderer, gProfTexture);
				//Prof4.renderProf(gRenderer, gProfTexture);
				//Prof5.renderProf(gRenderer, gProfTexture);
				
				//WTexture::renderText(gRenderer, gFont, (char *)"Hello", 600, 0, TEXT_WIDTH, TEXT_HEIGHT);


			//Update screen
				SDL_RenderPresent( gRenderer );

			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}