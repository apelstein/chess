#ifndef CHESSGAME_H_
#define CHESSGAME_H_
#include <stdbool.h>
#include "ChessArrayList.h"
# include "ChessParser.h"



/**
 * SPFIARGame Summary:
 *
 * A container that represents a classic connect-4 game, a two players 6 by 7
 * board game (rows X columns). The container supports the following functions.
 *
 * spFiarGameCreate           - Creates a new game board
 * spFiarGameCopy             - Copies a game board
 * spFiarGameDestroy          - Frees all memory resources associated with a game
 * spFiarGameSetMove          - Sets a move on a game board
 * spFiarGameIsValidMove      - Checks if a move is valid
 * spFiarGameUndoPrevMove     - Undoes previous move made by the last player
 * spFiarGamePrintBoard       - Prints the current board
 * spFiarGameGetCurrentPlayer - Returns the current player
 *
 */

typedef struct SP_CHESS_game_t {
	char gameBoard[SP_CHESS_GAME_N_ROWS+1][SP_CHESS_GAME_N_ROWS+1];
	int gameMode;
	int userColor;
	int gameOver;
	int currentPlayer;
	int difficulty;
	int* castlingWhite; //0- king, 1-right r moved, 2- left r, 3- castleCommandR 4-castleCommandL
	int* castlingBlack; //0- King, 1-right R, 2- left R, 3- castleCommandR 4-castleCommandL
	SPArrayList* lista;
	int guiCheck;
} SPFiarGame;

/**
 * Type used for returning error codes from game functions
 */
typedef enum SP_CHESS_game_message_t {
	SP_CHESS_GAME_INVALID_MOVE,
	SP_CHESS_GAME_INVALID_ARGUMENT,
	SP_CHESS_GAME_NO_HISTORY,
	SP_CHESS_GAME_SUCCESS,
//You may add any message you like
} SP_CHESS_GAME_MESSAGE;

int boardScore (SPFiarGame* src);

int boardScoreCases(char piece);

SPFiarGame* spFiarRAWGameCreate(int historySize);

SPFiarGame* spFiarRAWGameCreateHelper(int historySize,int listaFlag);

SPFiarGame* spFiarGameCreateNoLista(int historySize);

SPFiarGame* spFiarGameCreate(int historySize);

void defaultGameSettings (SPFiarGame* game);

void spPrintLine();

void undoCastling(SPFiarGame* src , int lista,move* move1,char srcPiece, char destPiece );

void spPrintBoard(SPFiarGame* src, int request);

void initBoard(SPFiarGame* src);

void checkCastling(SPFiarGame* src,int numCastle, char rook, int color, int r_s, int r_d);

void undoRook(SPFiarGame* src, int lista,move* move1,char srcPiece, char destPiece);
/**
 * Creates a new game with a specified history size. The history size is a
 * parameter which specifies the number of previous moves to store. If the number
 * of moves played so far exceeds this parameter, then first moves stored will
 * be discarded in order for new moves to be stored.
 *
 * @historySize - The total number of moves to undo,
 *                a player can undo at most historySizeMoves turns.
 * @return
 * NULL if either a memory allocation failure occurs or historySize <= 0.
 * Otherwise, a new game instant is returned.
 */
SPFiarGame* spFiarGameCreateHelper(int historySize, int lista);

/**
 *	Creates a copy of a given game.
 *	The new copy has the same status as the src game.
 *
 *	@param src - the source game which will be copied
 *	@return
 *	NULL if either src is NULL or a memory allocation failure occurred.
 *	Otherwise, an new copy of the source game is returned.
 *
 */
int spFiarGameCopy(SPFiarGame* src, SPFiarGame* dest);

int spFiarGameCopyHelper(SPFiarGame* src, SPFiarGame* dest, int lista);

int spFiarGameCopyReset(SPFiarGame* src, SPFiarGame* dest);
/**
 * Frees all memory allocation associated with a given game. If src==NULL
 * the function does nothing.
 *
 * @param src - the source game
 */
void spFiarGameDestroy(SPFiarGame* src);

/**
 * Sets the next move in a given game by specifying column index. The
 * columns are 0-based and in the range [0,SP_CHESS_GAME_N_COLUMNS -1].
 *
 * @param src - The target game
 * @param col - The target column, the columns are 0-based
 * @return
 * SP_CHESS_GAME_INVALID_ARGUMENT - if src is NULL or col is out-of-range
 * SP_CHESS_GAME_INVALID_MOVE - if the given column is full.
 */
SP_CHESS_GAME_MESSAGE spFiarGameSetMove(SPFiarGame* src, move* move1, int flagCheck);

/**
 * Checks if a disk can be put in the specified column.
 *
 * @param src - The source game
 * @param col - The specified column
 * @return
 * true  - if the a disc can be put in the target column
 * false - otherwise.
 */
bool spFiarGameIsValidMove(SPFiarGame* src, int col);

/**
 * Removes a disc that was put in the previous move and changes the current
 * player's turn. If the user invoked this command more than historySize times
 * in a row then an error occurs.
 *
 * @param src - The source game
 * @return
 * SP_CHESS_GAME_INVALID_ARGUMENT - if src == NULL
 * SP_CHESS_GAME_NO_HISTORY       - if the user invoked this function more then
 *                                 historySize in a row.
 * SP_CHESS_GAME_SUCCESS          - on success. The last disc that was put on the
 *                                 board is removed and the current player is changed
 */
SP_CHESS_GAME_MESSAGE spFiarGameUndoPrevMove(SPFiarGame* src);

SP_CHESS_GAME_MESSAGE spFiarGameUndoNoLista(SPFiarGame* src, move* move1,char srcPiece, char destPiece);
/**
 * On success, the function prints the board game. If an error occurs, then the
 * function does nothing. The characters 'X' and 'O' are used to represent
 * the discs of player 1 and player 2, respectively.
 *
 * @param src - the target game
 * @return
 * SP_CHESS_GAME_INVALID_ARGUMENT - if src==NULL
 * SP_CHESS_GAME_SUCCESS - otherwise
 *
 */
SP_CHESS_GAME_MESSAGE spFiarGamePrintBoard(SPFiarGame* src);

/**
 * Returns the current player of the specified game.
 * @param src - the source game
 * @return
 * SP_CHESS_GAME_PLAYER_1_SYMBOL - if it's player one's turn
 * SP_CHESS_GAME_PLAYER_2_SYMBOL - if it's player two's turn
 * SP_CHESS_GAME_EMPTY_ENTRY     - otherwise
 */
char spFiarGameGetCurrentPlayer(SPFiarGame* src);

/**
* Checks if there's a winner in the specified game status. The function returns either
* SP_CHESS_GAME_PLAYER_1_SYMBOL or SP_CHESS_GAME_PLAYER_2_SYMBOL in case there's a winner, where
* the value returned is the symbol of the winner. If the game is over and there's a tie
* then the value SP_CHESS_GAME_TIE_SYMBOL is returned. in any other case the null characters
* is returned.
* @param src - the source game
* @return
* SP_CHESS_GAME_PLAYER_1_SYMBOL - if player 1 won
* SP_CHESS_GAME_PLAYER_2_SYMBOL - if player 2 won
* SP_CHESS_GAME_TIE_SYMBOL - If the game is over and there's a tie
* null character - otherwise
*/
char spFiarCheckWinner(SPFiarGame* src);

/**
 * Switches players between turns.
 * @param src - the source game
 */
void switchPlayer(SPFiarGame* src);

SP_CHESS_GAME_MESSAGE loadGame(char* path, SPFiarGame* game);

void spQuit(SPFiarGame* src);

#endif
