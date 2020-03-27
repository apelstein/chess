#ifndef SPSIMPLEMAINWINDOW_H_
#define SPSIMPLEMAINWINDOW_H_
#include "SPWindow.h"
#include "BoxMessage.h"


typedef enum sp_num_win{
	MAIN_WIN,
	SETTINGS_WIN,
	LOAD_WIN,
	GAME_WIN
}NUM_WIN;

typedef struct sp_simplewindow_t  SPSimpleWindow;
struct sp_simplewindow_t {
	SDL_Window* window;
	SDL_Renderer* windowRenderer;
	//All widgets in our window
	Widget** widgets;
	int numOfWidgets;
	int* buttonsFlags;
	SDL_Texture* background;
};
SPWindow* createMainWindow();
SPWindow* createLoadWindow();
SPWindow* createSettingsWindow();
SPWindow* createGameWindow(SP_WIN_MESSAGE slot, int* settingsFlags);
Widget** createGameWindowWidgets(SDL_Renderer* renderer, int numOfWidgets,SPFiarGame* currentGame);
Widget** createLoadWindowWidgets(SDL_Renderer* renderer, int numOfWidgets);
Widget** createMainWindowWidgets(SDL_Renderer* renderer);
Widget** createSimpleWindowWidgets(SDL_Renderer* renderer);
SPWindow* createSimpleWindow(NUM_WIN num, int numOfwidgets);
void destroySimpleWindow(SPWindow* src);
void drawSimpleWindow(SPWindow* src);
//int handleEvenetSimpleWindow(SPWindow* src, SDL_Event* event);
SP_WIN_MESSAGE handleEvenetMainWindow(SPWindow* src, SDL_Event* event);
SP_WIN_MESSAGE handleEvenetLoadWindow(SPWindow* src, SDL_Event* event);
SP_WIN_MESSAGE handleEvenetGameWindow(SPWindow* src, SDL_Event* event);
SP_WIN_MESSAGE handleEvenetSettingsWindow(SPWindow* src, SDL_Event* event);
int xmlFileIsEmpty(char* path);
char *  getPicLoc(char type);
void createBackground (SPSimpleWindow* window, char* image);
SP_WIN_MESSAGE handleEvenetGameWindow(SPWindow* src, SDL_Event* event);
SP_WIN_MESSAGE handleMoveEventGameWindow(SPWindow* src, int widgetID);
int caseMoveGUI(SPFiarGame* game, move* moovit);
int handleSave(SPWindow* src);
int copyFromFileToFile(char* sourceFile, char* destFile);
SP_WIN_MESSAGE ExitMainHandle(SPWindow* src,char* title, char* question,SP_WIN_MESSAGE msg );
void initiateAction(SPWindow* src);
void destroyWidgetsGood(SPSimpleWindow* data);
#endif
