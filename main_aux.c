#include "main_aux.h"




int ValidMoveCommand(SPFiarGame* game,move* moovit ){

	if (!IAmTouchingMyPiece(game,moovit->curr_coord)) return 0;
	if(isAKnifeInTheBack(game,
			getPieceFromCoord(game,moovit->curr_coord),
			moovit->next_coord))
		return 0;
	return 1;
}

void printRequest(SPFiarGame* game){
	char* player;
	if(game->currentPlayer) player="white";
	else player="black";
	printf("%s player - enter your move:\n",player);fflush(stdout);

}

void caseMove(SPFiarGame* game, SPCommand* commando){


	if((!commando->validArg)||(commando->moovit==NULL)){
		printf("Invalid position on the board\n"); fflush(stdout);
		printRequest(game);
	}

	else if(!IAmTouchingMyPiece(game,commando->moovit->curr_coord)){
		printf("The specified position does not contain your piece\n"); fflush(stdout);
		printRequest(game);	}

	else if(ValidMoveCommand(game,commando->moovit)){
		if(PlayMoveCase(game,commando->moovit)==0){
			printf("Illegal move\n");fflush(stdout);
			printRequest(game);
		}

	}
	else{
		printf("Error: Invalid Command\n");fflush(stdout);
	}
}

int CheckThePlayersMove(SPFiarGame* game,move* move1){
	coordElem* ce=PossibleMoves(game,
			move1->curr_coord,
			getPieceFromCoord(game,move1->curr_coord),
			1);		//////////	////////here we change the arg of checkfocheck
	if(isCoordInList(ce,move1->next_coord)){
		destroyCEList(ce);
		return 1;
	}
	else {
		destroyCEList(ce);

		return 0;
	}
}

char* NameIt(char srcPiece){
	if((srcPiece=='q')||(srcPiece=='Q'))
		return "queen";
	else if((srcPiece=='k')||(srcPiece=='K'))
		return "king";
	else if((srcPiece=='r')||(srcPiece=='R'))
		return "rook";
	else if((srcPiece=='b')||(srcPiece=='B'))
		return "bishop";
	else if((srcPiece=='n')||(srcPiece=='N'))
		return "knight";
	else if((srcPiece=='m')||(srcPiece=='M'))
		return "pawn";
	else return "_";

}



void computerStrategy(SPFiarGame* game){
	move* move1;
	char srcP;
	char* piece_name;
//	printf("line 870 before the minimax\n");fflush(stdout);
	move1=spMinimaxSuggestMove(game,game->difficulty);
//	printf("line 872 after the minimax\n");fflush(stdout);
//	printf("line 873, the move.srcC= ");fflush(stdout);PrintTheCoord(move1->curr_coord);
	srcP=getPieceFromCoord(game,move1->curr_coord);
	spFiarGameSetMove(game,move1,0);
	piece_name=NameIt(srcP);
	printf("Computer: move %s at <%d,%c> to <%d,%c>\n",
			piece_name,move1->curr_coord->x,move1->curr_coord->y+64,
			move1->next_coord->x,move1->next_coord->y+64);
	if(ICheckyou(game)){
		if(!nextPlayerHasMoves(game)){
			game->gameOver=1;
		}
		else{
			if(game->guiCheck==1){
				SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Check!",
						"Check!", NULL );
			}
			printf("Check!\n");fflush(stdout);
			game->gameOver=0;

		}

	}
	else{
		if(!nextPlayerHasMoves(game)){
			printf("The game ends in a tie\n");fflush(stdout);
			game->gameOver=-1;
		}
		else{
			game->gameOver=0;

		}
	}
	destroyMove(move1);
}

int PlayMoveCase(SPFiarGame* game,move* moovit){
	int flagCheck=0, flagRvlHasMoves=0;
	move* move1;
	//coordElem* ce;
	char* color="white";
	move1=moovit;
	if(CheckThePlayersMove(game, move1)){
		spFiarGameSetMove(game,move1,0);
		flagCheck=ICheckyou(game);
//		printf("flagCheck=%d\n",flagCheck);fflush(stdout);
		flagRvlHasMoves=nextPlayerHasMoves(game);
//		printf("flagRVLhasMoves=%d\n",flagRvlHasMoves);fflush(stdout);
		if(flagCheck){
//			printf("line 768 after setMove\n");fflush(stdout);
			if(!flagRvlHasMoves){
				game->gameOver=1;
			}
			else{
				if(game->currentPlayer==0){
					color="black";
					if(game->guiCheck==1){
						SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Check!",
								"Black King is threatened", NULL );
					}
				}
				else{
					SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Check!",
							"White King is threatened", NULL );
				}
				printf("Check: %s King is threatened\n",color);

				game->gameOver=0;
//				printf("the board before comp. startegy\n");fflush(stdout);spPrintBoard(game);
				if(game->gameMode==1) computerStrategy(game);
			}

		}
		else{
//			printf("line 784 after setMove\n");fflush(stdout);
			if(!flagRvlHasMoves){
				printf("The game is tied\n");fflush(stdout);
				game->gameOver=-1;
			}
			else{
				game->gameOver=0;
//				printf("the board before comp. startegy\n");fflush(stdout);spPrintBoard(game,1);
				if(game->gameMode==1) computerStrategy(game);
			}
		}
		if(game->gameOver==0) spPrintBoard(game,1);
		return 1;
	}

	else{

		return 0;
	}
}

void SPFiarPlay(SPFiarGame* game){
	char* winnerColor="white";
	char str[SP_MAX_LINE_LENGTH];

	while(game->gameOver == 0){


		fgets(str, sizeof(str), stdin);
		if(strcmp(str," ")==0 || strcmp(str,"\n")==0 || *str==EOF) {
			printf("Error: Invalid Command. Please Specify game settings\n");fflush(stdout);
		}
		else{
			SPCommand* comando= spParserPraseLine(str,1);

			SPFiarMainCases(game, comando);
				//destroy commando
			destroyCom(comando);
		}

	}
	if(game->currentPlayer) winnerColor="black";
	if(game->gameOver==1){ printf("Checkmate! %s player wins the game\n",winnerColor);fflush(stdout);}

}

void spUndoMoveHelper2(SPFiarGame* src,move* move1){
	char *color="black";
	int i,j,x,y;
	i = move1->next_coord->x;
	j = move1->next_coord->y;
	x = move1->curr_coord->x;
	y = move1->curr_coord->y;
	if (src->currentPlayer == SP_CHESS_GAME_WHITE)
		color = "white";
	printf("Undo move for player %s : <%d,%c> -> <%d,%c>\n",color,i,j+64,x,y+64);
}

int spUndoMoveHelper1(SPFiarGame* src){
	SP_CHESS_GAME_MESSAGE m;
	move* move1;
	coord* i_co;
	if (spArrayListIsEmpty(src->lista)){
		printf("Empty history, move cannot be undone\n"); fflush(stdout);
		return 0;
	}
	else{
		i_co=InvalidCoord();
		move1 = createMove(i_co,i_co);
		destroyCoord(i_co);
		moveComparator(spArrayListGetLast(src->lista)->moovit, move1);
		m=spFiarGameUndoPrevMove(src);
		if (m==SP_CHESS_GAME_INVALID_ARGUMENT){
			printf("UndoMove received a NULL game\n"); fflush(stdout);
			destroyMove(move1);
			return 0;
		}
		else{
			spUndoMoveHelper2(src,move1);
			destroyMove(move1);
			return 1;
		}
	}
}

int spUndoMove(SPFiarGame* src){
	if (src->gameMode == SP_CHESS_GAME_2_PLAYER_MODE){
		printf("Undo command not available in 2 players mode\n");fflush(stdout);
		return 0;
	}
	else{ //1 player mode
		int undo_succeeded;
		undo_succeeded=spUndoMoveHelper1(src);
		if(undo_succeeded==1){
			spUndoMoveHelper1(src);
			spPrintBoard(src,1);

			return 1;
		}
		else return 0;
	}
}

void SPFiarMainCases(SPFiarGame* game, SPCommand* comando){
	switch (comando->cmd){
	case SP_UNDO_MOVE:
		spUndoMove(game);
		break;
	case SP_MOVE:
		caseMove(game,comando);
		break;
	case SP_SAVE:
		saveGame(game, comando->path);
		break;
	case SP_QUIT:
		spQuit(game);
		break;
	case SP_RESET:
		resetGame(game);
		break;
	case SP_INVALID_LINE:
		printf("Error: Invalid Command\n");fflush(stdout);
		break;
//			case SP_GET_MOVES:
//				shit
//				break;
	default:
		printf("Error: Invalid Command. Please Specify game settings\n");fflush(stdout);
		break;
	}
}

void resetGame(SPFiarGame* src){
	SPFiarGame* newGame;
	printf("Restarting...\n");
	newGame=spFiarGameCreate(undoListSize);
	if(spFiarGameCopyReset(newGame,src)){
		spPrintBoard(src,1);
		spFiarGameDestroy(newGame);

	}
	else{
		printf("Error: func. resetGame in main_aux.c\n"); fflush(stdout);
	}


}


SP_CHESS_GAME_MESSAGE saveGame (SPFiarGame* src, char * path) {
	FILE *ipf = NULL;
	if 	(src == NULL){
		return SP_CHESS_GAME_INVALID_ARGUMENT;
	}
	char rowContent[SP_CHESS_GAME_N_ROWS + 1] = { '\0' };
	if (path == '\0'){  //maybe ++path?
		printf("File cannot be created or modified\n");fflush(stdout);
	return SP_CHESS_GAME_INVALID_ARGUMENT;
	}
	else{ // path != '/0'
		ipf = fopen(path, "w");
		if (ipf == NULL){
			printf("File cannot be created or modified\n");fflush(stdout);
			return SP_CHESS_GAME_INVALID_ARGUMENT;
		}
		else{ //ipf != NULL
			fprintf(ipf, XML_PARSER_HEADING);fprintf(ipf,DOWN_LINE);
			fprintf(ipf,XML_GAME_HEAD);fprintf(ipf,DOWN_LINE);
			fprintf(ipf,TABB); fprintf(ipf, XML_PARSER_CURRENT_TURN, src->currentPlayer);fprintf(ipf,DOWN_LINE);
			fprintf(ipf,TABB);fprintf(ipf, XML_PARSER_GAME_MODE, src->gameMode);fprintf(ipf,DOWN_LINE);
			if (src->gameMode == 1) {
				fprintf(ipf,TABB);fprintf(ipf, XML_PARSER_DIFFICULTY, src->difficulty);fprintf(ipf,DOWN_LINE);
				fprintf(ipf,TABB);fprintf(ipf, XML_PARSER_USER_COLOR, src->userColor);fprintf(ipf,DOWN_LINE);
			}
			fprintf(ipf, XML_PARSER_BOARD);
			for (int i = SP_CHESS_GAME_N_ROWS; i >= 1; i--){
				for (int j = 1; j < SP_CHESS_GAME_N_ROWS+1; j++) {
					rowContent[j-1] = BOARD[i][j];
				}
				fprintf(ipf,TABB);fprintf(ipf,TABB);fprintf(ipf, XML_PARSER_ROW, i, rowContent, i);fprintf(ipf,DOWN_LINE);
			}
			fprintf(ipf,TABB);fprintf(ipf,XML_PARSER_BOARD_CLOSE);fprintf(ipf,DOWN_LINE);
			fprintf(ipf,TABB);fprintf(ipf,XML_GENERAL);fprintf(ipf,DOWN_LINE);
			fprintf(ipf,TABB);fprintf(ipf,TABB);fprintf(ipf, XML_CASTLING_WHITE,src->castlingWhite[0],src->castlingWhite[1],src->castlingWhite[2],src->castlingWhite[3],src->castlingWhite[4]);
			fprintf(ipf,DOWN_LINE);
			fprintf(ipf,TABB);fprintf(ipf,TABB);fprintf(ipf, XML_CASTLING_BLACK,src->castlingBlack[0],src->castlingBlack[1],src->castlingBlack[2],src->castlingBlack[3],src->castlingBlack[4]);
			fprintf(ipf,DOWN_LINE);
			fprintf(ipf,TABB);fprintf(ipf,TABB);fprintf(ipf,XML_GUI_CHECK,src->guiCheck);
			fprintf(ipf,TABB);fprintf(ipf,XML_GENERAL_CLOSE);fprintf(ipf,DOWN_LINE);
			fprintf(ipf, XML_PARSER_FINISH);
			fclose(ipf);
			return SP_CHESS_GAME_SUCCESS;
		}
	}
}


