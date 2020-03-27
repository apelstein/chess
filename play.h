#ifndef PLAY_H_
#define PLAY_H_
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "ChessGame.h"

int checkhelper(SPFiarGame* game, int player);

int isMyKingThreatned(SPFiarGame* game);

int ICheckyou(SPFiarGame* game);

int notSelfCheck(SPFiarGame* game, coord* srcCoord, coord* destCoord, char srcPiece);

int checkValidCastling(int dir,SPFiarGame* game, coord* srcCoord, char piece,int checkforcheck);

coordElem* ValidDestCoordKing(SPFiarGame* game, coord* srcCoord, char piece,int checkforcheck);

coordElem* ValidDestCoordStopMeIfYouCan(SPFiarGame* game, coord* srcCoord, char piece, int x_dir, int y_dir,int checkforcheck);

coordElem* ValidDestCoordKinght(SPFiarGame* game, coord* srcCoord, char piece,int checkforcheck);

coordElem* ValidDestCoordBishop(SPFiarGame* game, coord* srcCoord, char piece,int checkforcheck);

coordElem* ValidDestCoordQueen(SPFiarGame* game, coord* srcCoord, char piece,int checkforcheck);

coordElem* KnightCheck(SPFiarGame* game, coord* src, coord* dest, char piece,  int i, int j,int checkforcheck);

coordElem* ValidDestCoordPrawn(SPFiarGame* game, coord* srcCoord, char piece,int checkforcheck);

coordElem* ValidDestCoordPrawnHelper(SPFiarGame* game, coord* srcCoord, char piece, int direction,int checkforcheck);

coordElem* ValidDestCoordRook(SPFiarGame* game, coord* srcCoord, char piece,int checkforcheck);

coordElem* ValidDestCoordBRHelper(SPFiarGame* game, coord* srcCoord, char piece,int * x_dir, int* y_dir,int checkforcheck);

coordElem* PossibleMoves(SPFiarGame* game, coord* srcCoord, char srcPiece, int checkforcheck);

int PrawnIsEating(SPFiarGame* game, char piece, coord* dest);

int isEmptyChar(SPFiarGame* game, coord* co);

coord* FindTheKing(SPFiarGame* game, int player);

coordElem* AllPossibleMoves(SPFiarGame* game,int player, int checkForChecks);

int didYouTouchMyPiece(SPFiarGame* game, coord* co);

char getPieceFromCoord(SPFiarGame* game, coord* src);

int IAmTouchingMyPiece(SPFiarGame* game, coord* co);

//entering this func before a player plays
int nextPlayerHasMoves(SPFiarGame* game);

int isAKnifeInTheBack(SPFiarGame* game, char piece, coord* dest);

int isSmallCharacter(char c);

int isBigCharacter(char c);


#endif /* PLAY_H_ */
