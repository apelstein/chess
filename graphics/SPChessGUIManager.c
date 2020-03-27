#include <stdio.h>
#include <stdlib.h>
#include "SPChessGUIManager.h"

SPGuiManager* spManagerCreate() {
	SPGuiManager* res = (SPGuiManager*) malloc(sizeof(SPGuiManager));
	if (res == NULL ) {
		return NULL ;
	}
	res->mainWin = createMainWindow();
	if (res->mainWin == NULL ) {
		free(res);
		return NULL ;
	}
	res->settingsWin = NULL;
	res->loadWin = NULL;
	res->gameWin = NULL;
	res->activeWin=SP_MAIN_WINDOW;
	return res;
}
void spManagerDestroy(SPGuiManager* src) {
	if (!src) {
		return;
	}

	destroyWindow(src->mainWin);
	destroyWindow(src->loadWin);
	destroyWindow(src->settingsWin);
	destroyWindow(src->gameWin);
	free(src);
}
void spManagerDraw(SPGuiManager* src) {
	if (!src) {
		return;
	}
	if(src->activeWin==SP_GAME_WINDOW){
//		printf("line 37 before draw\n");fflush(stdout);
		drawSimpleWindow(src->gameWin);
//		printf("line 39 after draw\n");fflush(stdout);
	}
	if(src->activeWin==SP_SETTINGS_WINDOW) drawSimpleWindow(src->settingsWin);
	if(src->activeWin==SP_MAIN_WINDOW) drawSimpleWindow(src->mainWin);
	if(src->activeWin==SP_LOAD_WINDOW){
		drawSimpleWindow(src->loadWin);
//		printf("line 41\n ");fflush(stdout);
	}

}
SP_MANAGER_EVENET handleManagerDueToGameEvent(SPGuiManager* src,
		SP_WIN_MESSAGE event){

	if (src == NULL ) {
		return SP_MANAGER_QUTT;
	}
	if (event == WINDOW_CHANGE_TO_MAIN) {

			src->lastWindow=SP_GAME_WINDOW;
			destroySimpleWindow(src->gameWin);
			src->gameWin=NULL;

			src->activeWin=SP_MAIN_WINDOW;
			src->mainWin = createMainWindow();
			if (src->mainWin == NULL ) {
				printf("Couldn't create load window\n");
				return SP_MANAGER_QUTT;
			}

	}


	if (event == WINDOW_CHANGE_TO_LOAD) {

		src->lastWindow=SP_GAME_WINDOW;
		spWindowHide(src->gameWin);
		src->activeWin=SP_LOAD_WINDOW;
		src->loadWin = createLoadWindow();
		spWindowShow(src->loadWin);
		if (src->loadWin == NULL ) {
			printf("Couldn't create load window\n");
			return SP_MANAGER_QUTT;
		}

	}

	if (event == WINDOW_GAME_PLAYER1_WIN) {
		printf("Checkmate! White player wins the game\n");fflush(stdout);

		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Checkmate!",
				"White player wins the game", NULL );
		return SP_MANAGER_QUTT;
	}

	if (event == WINDOW_GAME_PLAYER2_WIN) {
		printf("Checkmate! Black player wins the game\n");fflush(stdout);
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Checkmate!",
				"Black player wins the game", NULL );
		return SP_MANAGER_QUTT;
	}
	if (event == WINDOW_GAME_TIE) {
		printf("The game ends in a tie\n");fflush(stdout);

		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Tie!",
				"The game ends in a tie", NULL );
		return SP_MANAGER_QUTT;
	}

	if (event == WINDOW_QUIT) {
		return SP_MANAGER_QUTT;
	}

	if(event== WINDOW_INVALID){
		return SP_MANAGER_NONE;
	}

	return SP_MANAGER_NONE;

}

SP_MANAGER_EVENET handleManagerDueToSettingsEvent(SPGuiManager* src,
		SP_WIN_MESSAGE event){
	int settingsFlags[3];
	if (src == NULL ) {
		return SP_MANAGER_QUTT;
	}


	if ((event >= WINDOW_SETTINGS_1_PLAYER_NOOB_WHITE)&&(event<=WINDOW_SETTINGS_2_PLAYER)){
		src->lastWindow = SP_SETTINGS_WINDOW;
		destroyWindow(src->settingsWin);
		src->settingsWin = NULL;
		src->activeWin= SP_GAME_WINDOW;
		settingsFlagsDecider(event,settingsFlags);
		src->gameWin = createGameWindow(WINDOW_CHANGE_TO_NEW_GAME,settingsFlags);
				if (src->gameWin == NULL ) {
					printf("Couldn't create load window\n");
					return SP_MANAGER_QUTT;
				}
	}
	if(event==WINDOW_CHANGE_TO_MAIN){
		src->lastWindow=SP_SETTINGS_WINDOW;
		destroyWindow(src->settingsWin);
		src->settingsWin=NULL;
		src->activeWin=SP_MAIN_WINDOW;
		src->mainWin = createMainWindow();
		if (src->mainWin == NULL ) {
			printf("Couldn't create load window\n");
			return SP_MANAGER_QUTT;
		}
	}
	return SP_MANAGER_NONE;
}

void settingsFlagsDecider(SP_WIN_MESSAGE event,int *settingsFlags){

	switch(event){
		case WINDOW_SETTINGS_1_PLAYER_NOOB_WHITE:
			settingsFlags[0] =settingsFlags[1] =settingsFlags[2] = 1;
			break;
		case WINDOW_SETTINGS_1_PLAYER_EASY_WHITE:
			settingsFlags[0] = 1;
			settingsFlags[1] = 1;
			settingsFlags[2] = 2;
			break;
		case WINDOW_SETTINGS_1_PLAYER_MODERATE_WHITE:
			settingsFlags[0] = 1;
			settingsFlags[1] = 1;
			settingsFlags[2] = 3;
			break;
		case WINDOW_SETTINGS_1_PLAYER_HARD_WHITE:
			settingsFlags[0] = 1;
			settingsFlags[1] = 1;
			settingsFlags[2] = 4;
			break;
		case WINDOW_SETTINGS_1_PLAYER_NOOB_BLACK:
			settingsFlags[0] = 1;
			settingsFlags[1] = 0;
			settingsFlags[2] =1;
			break;
		case WINDOW_SETTINGS_1_PLAYER_EASY_BLACK:
			settingsFlags[0] = 1;
			settingsFlags[1] = 0;
			settingsFlags[2] = 2;
			break;
		case WINDOW_SETTINGS_1_PLAYER_MODERATE_BLACK:
			settingsFlags[0] = 1;
			settingsFlags[1] = 0;
			settingsFlags[2] = 3;
			break;
		case WINDOW_SETTINGS_1_PLAYER_HARD_BLACK:
			settingsFlags[0] = 1;
			settingsFlags[1] = 0;
			settingsFlags[2] = 4;
			break;
		case WINDOW_SETTINGS_2_PLAYER:
			settingsFlags[0] = 2;
			settingsFlags[1] = 1;
			settingsFlags[2] = 0;
			break;
		default:
			break;
	}

}


SP_MANAGER_EVENET handleManagerDueToLoadEvent(SPGuiManager* src,
		SP_WIN_MESSAGE event){

	if (src == NULL ) {
		return SP_MANAGER_QUTT;
	}
	if(event==WINDOW_CHANGE_TO_LAST){
		if(src->lastWindow==SP_MAIN_WINDOW){

			src->lastWindow=SP_LOAD_WINDOW;
			destroyWindow(src->loadWin);
			src->loadWin=NULL;
			src->activeWin=SP_MAIN_WINDOW;
			src->mainWin = createMainWindow();
			if (src->mainWin == NULL ) {
				printf("Couldn't create load window\n");
				return SP_MANAGER_QUTT;
			}


		}
		else{
			src->lastWindow=SP_LOAD_WINDOW;
			destroyWindow(src->loadWin);
			src->loadWin=NULL;
			src->activeWin=SP_GAME_WINDOW;
			spWindowShow(src->gameWin);

		}
	}
	if((event>=WINDOW_CHANGE_TO_LOAD_SLOT_1)&&(event<=WINDOW_CHANGE_TO_LOAD_SLOT_5)){
		src->lastWindow=SP_LOAD_WINDOW;
		destroyWindow(src->loadWin);
		src->loadWin=NULL;
		src->activeWin=GAME_WIN;
		if(src->gameWin!=NULL){
			destroyWindow(src->gameWin);
			src->gameWin=NULL;
		}
		src->gameWin = createGameWindow(event,NULL);
		if(src->gameWin->theGame->userColor==0){
			src->gameWin->theGame->currentPlayer=0;
		}
		if (src->gameWin == NULL ) {
			printf("Couldn't create load window\n");
			return SP_MANAGER_QUTT;
		}

	}
	return SP_MANAGER_NONE;
}

SP_MANAGER_EVENET handleManagerDueToMainEvent(SPGuiManager* src,
		SP_WIN_MESSAGE event) {
	if (src == NULL ) {
		return SP_MANAGER_QUTT;
	}
//	printf("line 129 event=%d\n",event);fflush(stdout);
	if (event == WINDOW_CHANGE_TO_SETTINGS) {
		src->lastWindow=SP_MAIN_WINDOW;
		destroyWindow(src->mainWin);
		src->mainWin=NULL;
		src->activeWin=SP_SETTINGS_WINDOW;
		src->settingsWin = createSettingsWindow();
		if (src->settingsWin == NULL ) {
			printf("Couldn't create settings window\n");
			return SP_MANAGER_QUTT;
		}

	}
	if (event == WINDOW_CHANGE_TO_LOAD) {

		src->lastWindow=SP_MAIN_WINDOW;
		destroyWindow(src->mainWin);
		src->mainWin=NULL;
		src->activeWin=SP_LOAD_WINDOW;
		src->loadWin = createLoadWindow();
		if (src->loadWin == NULL ) {
			printf("Couldn't create load window\n");
			return SP_MANAGER_QUTT;
		}

	}

	if (event == WINDOW_QUIT) {
//		printf("line 157\n");fflush(stdout);
		return SP_MANAGER_QUTT;
	}
	return SP_MANAGER_NONE;
}

//SP_MANAGER_EVENET handleManagerDueToGameEvent(SPGuiManager* src,
//		SP_GAME_EVENT event) {
//	if (event == SP_GAME_EVENT_NONE || src == NULL ) {
//		return SP_MANAGER_NONE;
//	}
//	if (event == SP_GAME_EVENT_X_WON) {
//		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Game over", "X won",
//				NULL );
//	} else if (event == SP_GAME_EVENT_O_WON) {
//		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Game over", "O won",
//				NULL );
//	} else if (event == SP_GAME_EVENT_TIE) {
//		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Game over",
//				"it's a tie", NULL );
//	}
//	spGameWindowDestroy(src->gameWin);
//	src->gameWin = NULL;
//	src->activeWin = SP_MAIN_WINDOW_ACTIVE;
//	spMainWindowShow(src->mainWin);
//	return SP_MANAGER_NONE;
//}

SP_MANAGER_EVENET spManagerHandleEvent(SPGuiManager* src, SDL_Event* event) {
	if (src == NULL || event == NULL ) {
		return SP_MANAGER_NONE;
	}
	if (src->activeWin == SP_MAIN_WINDOW) {
		SP_WIN_MESSAGE mainEvent = handleEvenetMainWindow(src->mainWin,event);
		return handleManagerDueToMainEvent(src, mainEvent);
	}
	else if (src->activeWin == SP_LOAD_WINDOW) {
		SP_WIN_MESSAGE loadEvent = handleEvenetLoadWindow(src->loadWin,event);

		return handleManagerDueToLoadEvent(src, loadEvent);
	}
	else if (src->activeWin == SP_SETTINGS_WINDOW) {
		SP_WIN_MESSAGE settingsEvent = handleEvenetSettingsWindow(src->settingsWin,event);
		return handleManagerDueToSettingsEvent(src, settingsEvent);
	}
	else if (src->activeWin == SP_GAME_WINDOW) {
		SP_WIN_MESSAGE gameEvent = handleEvenetGameWindow(src->gameWin,event);
		return handleManagerDueToGameEvent(src, gameEvent);
	}
//	else if (src->settingsWin != NULL) {
//		SP_WIN_MESSAGE settingsEvent = handleEvenetSettingsWindow(src->settingsWin,event);
//		return handleManagerDueToSettingsEvent(src, settingsEvent);
//	}
//	else{ //if (src->gameWin != NULL)
//		SP_WIN_MESSAGE gameEvent = handleEvenetgameWindow(src->gameWin,event);
//		return handleManagerDueToGameEvent(src, gameEvent);
//	}

	return SP_MANAGER_NONE;
}

void spWindowHide(SPWindow* src) {
	SPSimpleWindow* castWin= (SPSimpleWindow*) src->data;
	SDL_HideWindow(castWin->window);
}

void spWindowShow(SPWindow* src) {
	SPSimpleWindow* castWin= (SPSimpleWindow*) src->data;
	SDL_ShowWindow(castWin->window);
}
