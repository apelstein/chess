#ifndef CHESSPARSER_H_
#define CHESSPARSER_H_
#include "Costa.h"
#include "ChessMoves.h"
#include <stdbool.h>

//a new type that is used to encapsulate a parsed line
typedef struct command_t {
	SP_COMMAND cmd;
	int arg;
	bool validArg;
	char* path;
	move* moovit;
} SPCommand;

/**
 * Checks if a specified string represents a valid integer. It is recommended
 * to use this function prior to calling the standard library function atoi.
 *
 * @return
 * true if the string represents a valid integer, and false otherwise.
 */
bool spParserIsInt(const char* str);

SPCommand* createCommand();

/**
 * Parses a specified line. If the line is a command which has an integer
 * argument then the argument is parsed and is saved in the field arg and the
 * field validArg is set to true. In any other case then 'validArg' is set to
 * false and the value 'arg' is undefined
 * @parmas:
 * 	 gameState- indicates which state in the game are we.
 * @return
 * A parsed line such that:
 *   cmd - contains the command type, if the line is invalid then this field is
 *         set to INVALID_LINE
 *   validArg - is set to true if the command is add_disc and the integer argument
 *              is valid
 *   arg      - the integer argument in case validArg is set to true
 */
void destroyCom(SPCommand* com);

SPCommand* spParserPraseLine(const char* str, int gameState);

SPCommand* spHelperPPLSetting(const char* str);

SPCommand* spHelperPPLGame(const char* str);

SPCommand* spHelperPPLMove(const char* str);

coord* getCoordFromToken2(const char* str);

unsigned int getYCoordFromStr(const char* str);

bool isValidCoord(coord* coordinates);





#endif /* CHESSPARSER_H_ */
