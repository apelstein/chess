#ifndef SPCHESSGUIMANAGER_H_
#define SPCHESSGUIMANAGER_H_
#include "SPSimpleMainWindow.h"

typedef enum{
	SP_MAIN_WINDOW,
	SP_LOAD_WINDOW,
	SP_SETTINGS_WINDOW,
	SP_GAME_WINDOW
}LAST_WINDOW;

typedef enum{
	SP_MANAGER_QUTT,
	SP_MANAGER_NONE,
}SP_MANAGER_EVENET;

typedef struct {
	SPWindow* gameWin;
	SPWindow* loadWin;
	SPWindow* settingsWin;
	SPWindow* mainWin;
	LAST_WINDOW lastWindow;
	LAST_WINDOW activeWin;

} SPGuiManager;

SPGuiManager* spManagerCreate();

void spManagerDestroy(SPGuiManager* src);

void spManagerDraw(SPGuiManager* src);
SP_MANAGER_EVENET handleManagerDueToGameEvent(SPGuiManager* src,
		SP_WIN_MESSAGE event);
SP_MANAGER_EVENET handleManagerDueToMainEvent(SPGuiManager* src,
		SP_WIN_MESSAGE event);
SP_MANAGER_EVENET handleManagerDueToLoadEvent(SPGuiManager* src,
		SP_WIN_MESSAGE event);
SP_MANAGER_EVENET handleManagerDueToSettingsEvent(SPGuiManager* src,
		SP_WIN_MESSAGE event);

SP_MANAGER_EVENET spManagerHandleEvent(SPGuiManager* src, SDL_Event* event) ;

void spWindowShow(SPWindow* src);
void spWindowHide(SPWindow* src);
void settingsFlagsDecider(SP_WIN_MESSAGE event,int *settingsFlags);
#endif
