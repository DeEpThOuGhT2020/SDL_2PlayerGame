#include "Game.h"
#include "Player.h"
#include "Constants.h"
#include "Guard.h"

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

			//The dot that will be moving around on the screen
			Player player1(72, 300);
			Player player2(1032, 350);
			Guard guard1(72, 325);
			//Guard guard2(60, 300);
			//Guard guard3(60, 400);
			//Guard guard4(648, 744);
			//Guard guard5(348, 72);

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

				//Move the dot
				player1.movePlayer(map);
				guard1.moveGuard(player1 , player2, map);
				//guard2.moveGuard(player1 , player2, map);
				//guard3.moveGuard(player1 , player2, map);
				//guard4.update(player1 , player2, map);
				//guard5.update(player1 , player2, map);

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
				guard1.renderGuard(gRenderer, gGuardTexture);
				//guard2.renderGuard(gRenderer, gGuardTexture);
				//guard3.renderGuard(gRenderer, gGuardTexture);
				//guard4.renderGuard(gRenderer, gGuardTexture);
				//guard5.renderGuard(gRenderer, gGuardTexture);

			//Update screen
				SDL_RenderPresent( gRenderer );

			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}