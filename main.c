#include <stdio.h>

#include "graphics/SPChessGUIManager.h"
int main(int argc, char** argv){
	char flagMode;
	if (argc == 1) {
		//Opens console as default mode
		flagMode='c';
	}
	else if (argc == 2) {
		if ((strstr(argv[1], "c"))!=NULL) {
			flagMode='c';
		}
		else if ((strstr(argv[1], "g"))!=NULL) {
			flagMode='g';
		}
		else {
			printf("Error: wrong execution command\n");
		}
	}
	else {
		printf("Error: wrong execution command\n");
	}
	if(flagMode=='c'){
		SPFiarGame *game= spFiarGameCreate(undoListSize);
//		printf("mode %d color %d c.player %d\n",game->gameMode,game->userColor,game->currentPlayer);fflush(stdout);
		if (game->gameMode==1){
			if(game->userColor != game->currentPlayer){//if we chose black the computer has to start
//				printf("line 29");fflush(stdout);
				computerStrategy(game);
				game->lista=spArrayListCreate(undoListSize);
			}
		}

		spPrintBoard(game,1);
		SPFiarPlay(game);
		spFiarGameDestroy(game);
//		SPCommand* com=createCommand();
//
//		destroyCom(com);
		return 1;
	}
	else{// if(flagMode=='g'){
		if (SDL_Init(SDL_INIT_VIDEO) < 0) { //SDL2 INIT
			printf("ERROR: unable to init SDL: %s\n", SDL_GetError());
			return 1;
		}
		SPGuiManager* manager = spManagerCreate();
		if (manager == NULL ) {
	//		printf("dczxc\n");fflush(stdout);
			SDL_Quit();
			return 0;
		}
		SDL_Event event;
		while (1) {
			SDL_WaitEvent(&event);
			if(event.type == SDL_QUIT){
				break;
			}
			if(spManagerHandleEvent(manager, &event)==SP_MANAGER_QUTT)
				break;;
			//In this example we draw the window every time... in many case we shouldn't
			spManagerDraw(manager);
		}
		spManagerDestroy(manager);
		SDL_Quit();
		return 0;
	}
}




