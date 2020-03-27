#ifndef COSTA_H_
#define COSTA_H_



#define undoListSize 6
#define SP_MAX_LINE_LENGTH 1024

//Definitions of GameBoard
#define BOARD src->gameBoard
#define SP_CHESS_GAME_N_ROWS 8
#define SP_CHESS_GAME_TIE_SYMBOL '-'
#define SP_CHESS_GAME_EMPTY_ENTRY '_'
#define emptyChar '_'
#define SP_CHESS_GAME_HISTORY_SIZE 6
#define SP_CHESS_GAME_1PLAYER_SYMBOL 1
#define SP_FAIR_GAME_COMPUTER_SYMBOL 0
#define SP_CHESS_GAME_2PLAYERS_PLAYER_1_SYMBOL 1
#define SP_CHESS_GAME_2PLAYERS_PLAYER_2_SYMBOL 0
#define SP_CHESS_GAME_WHITE 1
#define SP_CHESS_GAME_BLACK 0
#define SP_CHESS_GAME_1_PLAYER_MODE 1
#define SP_CHESS_GAME_2_PLAYER_MODE 2
#define SP_MAX_LINE_LENGTH 1024
#define FINDTHEX(x, y) (((x) > (y)) ? (x) : (y))   //find the max
#define FINDTHEN(x, y) (((x) < (y)) ? (x) : (y)) // find the min
# define MIN -1000000000
# define MAX 1000000000
//Defenitions for main_aux
#define XML_PARSER_ROW "<row_%d>%8s</row_%d>"
#define XML_PARSER_GAME_MODE "<game_mode>%d</game_mode>"
#define XML_PARSER_HEADING "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
#define DOWN_LINE "\n"
#define XML_GAME_HEAD "<game>"
#define TABB "\t"
#define XML_PARSER_USER_COLOR "<user_color>%d</user_color>"
#define XML_PARSER_CURRENT_TURN "<current_turn>%d</current_turn>"
#define XML_PARSER_DIFFICULTY "<difficulty>%d</difficulty>"
#define XML_PARSER_BOARD "<board>"
#define XML_PARSER_BOARD_CLOSE "</board>"
#define XML_CASTLING_WHITE "<castling_white>%d%d%d%d%d</castling_white>"
#define XML_GENERAL "<general>"
#define XML_GUI_CHECK "<guiCheck>%d</guiCheck>"
#define XML_CASTLING_BLACK "<castling_black>%d%d%d%d%d</castling_black>"
#define XML_GENERAL_CLOSE "</general>"
#define XML_PARSER_FINISH "</game>"
///
#define GAME_XML_HEADING_FORMAT "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
#define GAME_XML_GAME_HEADING "<game>"
#define GAME_XML_CURRENT_TURN_FORMAT "<current_turn>%d</current_turn>"
#define GAME_XML_MODE_FORMAT "<game_mode>%d</game_mode>"
#define GAME_XML_DIFFCULTY_FORMAT "<difficulty>%d</difficulty>"
#define GAME_XML_USER_COLOR_FORMAT "<user_color>%d</user_color>"
#define GAME_XML_BOARD_HEADING_FORMAT "<board>"
#define GAME_XML_BOARD_ROW_FORMAT "<row_%d>%8s</row_%d>"
#define GAME_XML_USER_WRAP_UP_FORMAT "</board></game>"
#define GAME_XML_IGNORE_SPACES_FORMAT "%*[ \r\n\t]"

//a type used to represent a command
typedef enum {
	SP_UNDO_MOVE,
	SP_QUIT,
	SP_RESET,
	SP_GAME_MODE,
	SP_DIFFICULTY,
	SP_USER_COLOR,
	SP_LOAD,
	SP_DEFAULT,
	SP_PRINT_SETTING,
	SP_START,
	SP_MOVE,
	SP_GET_MOVES,
	SP_SAVE,
	SP_INVALID_LINE
} SP_COMMAND;

/**
 * A type used for errors
 */
typedef enum  {
	SP_ARRAY_LIST_SUCCESS,
	SP_ARRAY_LIST_INVALID_ARGUMENT,
	SP_ARRAY_LIST_FULL,
	SP_ARRAY_LIST_EMPTY
} SP_ARRAY_LIST_MESSAGE;


#endif
