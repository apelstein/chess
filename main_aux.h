
#ifndef MAIN_AUX_H_
#define MAIN_AUX_H_

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "SPMiniMax.h"
#include <SDL.h>
#include <SDL_video.h>



void SPFiarPlay(SPFiarGame* game);

void spUndoMoveHelper2(SPFiarGame* src,move* move1);

int spUndoMoveHelper1(SPFiarGame* src);

int spUndoMove(SPFiarGame* src);

void SPFiarMainCases(SPFiarGame* game, SPCommand* comando);

void resetGame(SPFiarGame* src);



SP_CHESS_GAME_MESSAGE saveGame (SPFiarGame* src, char * path) ;


int ValidMoveCommand(SPFiarGame* game,move* moovit);

void caseMove(SPFiarGame* game, SPCommand* commando);

int PlayMoveCase(SPFiarGame* game,move* moovit);

int CheckThePlayersMove(SPFiarGame* game,move* move1);

void printRequest(SPFiarGame* game);

char* NameIt(char srcPiece);

void computerStrategy(SPFiarGame* game);

#endif /* MAIN_AUX_H_ */
