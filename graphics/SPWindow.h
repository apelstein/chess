#ifndef SPWINDOW_H_
#define SPWINDOW_H_

#include "../main_aux.h"

typedef enum sp_win_message_t {
	WINDOW_CHANGE_TO_MAIN,
	WINDOW_CHANGE_TO_SETTINGS,
	WINDOW_CHANGE_TO_LOAD_SLOT_1,
	WINDOW_CHANGE_TO_LOAD_SLOT_2,
	WINDOW_CHANGE_TO_LOAD_SLOT_3,
	WINDOW_CHANGE_TO_LOAD_SLOT_4,
	WINDOW_CHANGE_TO_LOAD_SLOT_5,
	WINDOW_CHANGE_TO_LOAD,
	WINDOW_CHANGE_TO_NEW_GAME,
	WINDOW_CHANGE_TO_LAST,
	WINDOW_SETTINGS_1_PLAYER_NOOB_WHITE,
	WINDOW_SETTINGS_1_PLAYER_EASY_WHITE,
	WINDOW_SETTINGS_1_PLAYER_MODERATE_WHITE,
	WINDOW_SETTINGS_1_PLAYER_HARD_WHITE,
	WINDOW_SETTINGS_1_PLAYER_NOOB_BLACK,
	WINDOW_SETTINGS_1_PLAYER_EASY_BLACK,
	WINDOW_SETTINGS_1_PLAYER_MODERATE_BLACK,
	WINDOW_SETTINGS_1_PLAYER_HARD_BLACK,
	WINDOW_SETTINGS_2_PLAYER,
	WINDOW_GAME_COMPUTER_WIN,
	WINDOW_GAME_PLAYER1_WIN,
	WINDOW_GAME_PLAYER2_WIN,
	WINDOW_GAME_TIE,
	WINDOW_GAME_NEW,

	WINDOW_QUIT,
	WINDOW_INVALID,
	WINDOW_NONE


} SP_WIN_MESSAGE;

typedef struct spwindow_t SPWindow;
struct spwindow_t {
	void* data;
	int didYouSave;
	action* theAction;
	SPFiarGame* theGame;
	void (*drawWindow)(SPWindow* );
	SP_WIN_MESSAGE (*handleEventWindow)(SPWindow* , SDL_Event* );
	void (*destroyWindow)(SPWindow* );
	//You can add more common functions Like exit/hide etc...
};

//NULL safe FUNCTION
void destroyWindow(SPWindow* src);

#endif
