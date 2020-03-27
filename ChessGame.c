# include <stdio.h>
# include "ChessGame.h"

# include <stdlib.h>
# include <string.h>
# include <assert.h>

SPFiarGame* spFiarRAWGameCreate(int historySize){
	return spFiarRAWGameCreateHelper(historySize, 1);
}



SPFiarGame* spFiarRAWGameCreateHelper(int historySize, int listaFlag){
	if (historySize <= 0)
		return NULL;
	SPFiarGame* game = (SPFiarGame*) malloc(sizeof(SPFiarGame));
	if (game == NULL){
			printf("Error: spFiarGameCreate has failed\n");
			return NULL;
	}
	game->castlingWhite=(int *) calloc(5,sizeof(int));
	game->castlingBlack=(int *) calloc(5,sizeof(int));
	if(listaFlag){
		game->lista = spArrayListCreate(historySize);
		if (game->lista == NULL){
			spFiarGameDestroy(game);
			printf("Error: spFiarGameCreate has failed\n");fflush(stdout);
			return NULL;
		}
	}
	else game->lista=NULL;

	game->guiCheck=0;
	return game;
}

SPFiarGame* spFiarGameCreate(int historySize){
	return spFiarGameCreateHelper( historySize, 1);
}

SPFiarGame* spFiarGameCreateNoLista(int historySize){
	return spFiarGameCreateHelper( historySize, 0);
}

SPFiarGame* spFiarGameCreateHelper(int historySize, int lista){
	int start = 0;
	char input[SP_MAX_LINE_LENGTH];
	if (historySize <= 0)
		return NULL;

	SPFiarGame* game = (SPFiarGame*) malloc(sizeof(SPFiarGame));
	if (game == NULL){
			printf("Error: spFiarGameCreate has failed\n");fflush(stdout);
			return NULL;
	}
	game->castlingBlack=(int*) calloc(5,sizeof(int));
	game->castlingWhite=(int*) calloc(5,sizeof(int));

	game->lista = NULL;


		for (int i=1 ; i< SP_CHESS_GAME_N_ROWS+1 ; i++){
			for (int j = 1 ; j< SP_CHESS_GAME_N_ROWS+1 ; j++){
				game->gameBoard[i][j] = SP_CHESS_GAME_EMPTY_ENTRY;
			}
		}

	defaultGameSettings(game);
	initBoard(game);
	printf("Specify game setting or type 'start' to begin a game with the current setting:\n");	fflush( stdout );
	while (start == 0){
		fgets(input, sizeof(input),stdin);
		SPCommand* com1=spParserPraseLine(input,0);
		switch (com1->cmd){
		case  SP_INVALID_LINE:
			printf("Error: Invalid Command. Please Specify game settings\n");fflush(stdout);
			break;
		case SP_QUIT:
			spQuit(game);
			break;
		case SP_GAME_MODE:
			if (com1->arg == SP_CHESS_GAME_1_PLAYER_MODE){
				game->gameMode = com1->arg;
				printf("Game mode is set to 1 player\n");fflush(stdout);
			}
			else if (com1->arg == SP_CHESS_GAME_2_PLAYER_MODE){
				game->userColor = SP_CHESS_GAME_1PLAYER_SYMBOL;
				game->gameMode = com1->arg;
				printf("Game mode is set to 2 players\n");fflush(stdout);
			}
			else{
				printf("Wrong game mode\n");fflush(stdout);
			}
			break;
		case SP_DIFFICULTY:
			if (game->gameMode == SP_CHESS_GAME_1_PLAYER_MODE){
				if (com1->arg <5){
					game->difficulty = com1->arg;
//					printf("Difficulty level is set to %d\n",com1->arg);
				}
				else if (com1->arg ==5){
					printf("Expert level not supported, please choose a value between 1 to 4:\n");fflush(stdout);
				}
				else if (com1->validArg == 0){
					printf("Wrong difficulty level. The value should be between 1 to 5\n");fflush(stdout);
				}
			}
			else{
				printf("Error: Invalid Command. Please Specify game settings\n");fflush(stdout);
			}
			break;
		case SP_USER_COLOR:
			if (game->gameMode == SP_CHESS_GAME_1_PLAYER_MODE){
				if (com1->validArg == 0){
					printf("Wrong color. The value should be 0 (black) or 1 (white)\n");fflush(stdout);
				}
				else{
					if((com1->arg==1)||(com1->arg==0)){
						game->userColor = com1->arg;
//						printf("User color is set to %d\n", com1->arg);fflush(stdout);

					}
					else{
						printf("Wrong color. The value should be 0 (black) or 1 (white)\n");fflush(stdout);
					}
				}
			}
			else{
				printf("Error: Invalid Command. Please Specify game settings\n");fflush(stdout);
			}
			break;
		case SP_DEFAULT:
			defaultGameSettings(game);
			printf("Default settings were set\n");fflush(stdout);
			break;
		case SP_PRINT_SETTING:
			if (game->gameMode == SP_CHESS_GAME_2_PLAYER_MODE){
				printf("SETTINGS:\nGAME_MODE: 2\n");fflush(stdout);
			}
			else{
				if (game->userColor==0){
					printf("SETTINGS:\nGAME_MODE: 1\nDIFFICULTY_LVL: %d\nUSER_CLR: BLACK\n", game->difficulty);fflush(stdout);
				}
				else if (game->userColor==1){
					printf("SETTINGS:\nGAME_MODE: 1\nDIFFICULTY_LVL: %d\nUSER_CLR: WHITE\n", game->difficulty);fflush(stdout);
				}
				else{
					printf("Shouldn't have got here, wrong color was set\n");fflush(stdout);
				}
			}
			break;
		case SP_START:
			start = 1;
			break;
		case SP_LOAD:{
			SPFiarGame* newGame = spFiarRAWGameCreate(historySize);
			SP_CHESS_GAME_MESSAGE load_succeeded;
			load_succeeded = loadGame(com1->path, newGame);
			if (load_succeeded == SP_CHESS_GAME_SUCCESS){

				if((newGame->castlingWhite[0]!=0)&&(newGame->castlingWhite[0]!=1)){
					newGame->castlingBlack=(int*) calloc(5,sizeof(int));
					newGame->castlingWhite=(int*) calloc(5,sizeof(int));
				}
				spFiarGameCopy(newGame,game);
				spFiarGameDestroy(newGame);
			}
			break;
		}
		default:
			printf("Entered default case in spGameCreate\n");fflush(stdout);
			break;
		}
		destroyCom(com1);
	}
	if((game->castlingWhite[0]!=0)&&(game->castlingWhite[0]!=1)){
		game->castlingBlack=(int*) calloc(5,sizeof(int));
		game->castlingWhite=(int*) calloc(5,sizeof(int));
	}
	if(lista){
		if(game->lista==NULL){
			game->lista=spArrayListCreate(historySize);
		}
		if (game->lista == NULL){
			spFiarGameDestroy(game);
			printf("Error: spFiarGameCreate has failed\n");fflush(stdout);
			return NULL;
		}
	}

	game->gameOver=0;
	return game;
}



SP_CHESS_GAME_MESSAGE loadGame(char* path, SPFiarGame* game){
	FILE *ipf = NULL;

	ipf = fopen(path, "r");
	int row;
	char rowContent[SP_CHESS_GAME_N_ROWS + 1] = { '\0' };
	if (path == '\0'){  //maybe ++path?
		printf("Error: File doesn't exist or cannot be opened\n");fflush(stdout);
		return SP_CHESS_GAME_INVALID_ARGUMENT;
	}
	fscanf(ipf, XML_PARSER_HEADING);
	fscanf(ipf, GAME_XML_IGNORE_SPACES_FORMAT);
	fscanf(ipf, XML_GAME_HEAD);
	fscanf(ipf, GAME_XML_IGNORE_SPACES_FORMAT);
	fscanf(ipf, XML_PARSER_CURRENT_TURN, &game->currentPlayer);
	fscanf(ipf, GAME_XML_IGNORE_SPACES_FORMAT);
	fscanf(ipf, XML_PARSER_GAME_MODE, &game->gameMode);
	fscanf(ipf, GAME_XML_IGNORE_SPACES_FORMAT);
	if (game->gameMode == 1){

		fscanf(ipf, XML_PARSER_DIFFICULTY, &game->difficulty);
		fscanf(ipf, GAME_XML_IGNORE_SPACES_FORMAT);
		fscanf(ipf, XML_PARSER_USER_COLOR, &game->userColor);
		fscanf(ipf, GAME_XML_IGNORE_SPACES_FORMAT);
	}
	fscanf(ipf,XML_PARSER_BOARD);
	fscanf(ipf, GAME_XML_IGNORE_SPACES_FORMAT);
	for (int i = 0; i <SP_CHESS_GAME_N_ROWS; i++) {
		fscanf(ipf, XML_PARSER_ROW, &row, rowContent, &row);
		fscanf(ipf, GAME_XML_IGNORE_SPACES_FORMAT);
		for (int j = 1; j <= SP_CHESS_GAME_N_ROWS; j++) {
			game->gameBoard[SP_CHESS_GAME_N_ROWS -i ][j] = rowContent[j-1];
		}
	}
	fscanf(ipf, GAME_XML_IGNORE_SPACES_FORMAT);
	fscanf(ipf,XML_PARSER_BOARD_CLOSE);
	fscanf(ipf, GAME_XML_IGNORE_SPACES_FORMAT);
	fscanf(ipf,XML_GENERAL);
	fscanf(ipf, GAME_XML_IGNORE_SPACES_FORMAT);
	fscanf(ipf,XML_CASTLING_WHITE,&game->castlingWhite[0],&game->castlingWhite[1],&game->castlingWhite[2],&game->castlingWhite[3],&game->castlingWhite[4]);
	fscanf(ipf, GAME_XML_IGNORE_SPACES_FORMAT);
	fscanf(ipf,XML_CASTLING_BLACK,&game->castlingBlack[0],&game->castlingBlack[1],&game->castlingBlack[2],&game->castlingBlack[3],&game->castlingBlack[4]);
	fscanf(ipf, GAME_XML_IGNORE_SPACES_FORMAT);
	fscanf(ipf,XML_GUI_CHECK,&game->guiCheck);
	fscanf(ipf, GAME_XML_IGNORE_SPACES_FORMAT);
	fscanf(ipf,XML_GENERAL_CLOSE);
	if((game->castlingWhite[0]!=0)&&(game->castlingWhite[0]!=1)){
		game->castlingWhite=(int*) calloc(5,sizeof(int));
		game->castlingBlack=(int*) calloc(5,sizeof(int));
	}
	fscanf(ipf, GAME_XML_IGNORE_SPACES_FORMAT);
	fscanf(ipf, XML_PARSER_FINISH);
	fclose(ipf);
	return SP_CHESS_GAME_SUCCESS;

}


void defaultGameSettings (SPFiarGame* game){
	game->gameMode = SP_CHESS_GAME_1_PLAYER_MODE;
	game->currentPlayer = SP_CHESS_GAME_1PLAYER_SYMBOL;
	game->difficulty = 2;
	game->userColor = SP_CHESS_GAME_WHITE;
	game->gameOver = 0;
}

int spFiarGameCopyReset(SPFiarGame* src, SPFiarGame* dest){
	return spFiarGameCopyHelper(src,dest,0);
}

int spFiarGameCopy(SPFiarGame* src, SPFiarGame* dest){
	return spFiarGameCopyHelper(src,dest,1);
}

int spFiarGameCopyHelper(SPFiarGame* src, SPFiarGame* dest, int lista){
	if((src == NULL)||(dest==NULL)){
		printf("Error: spFiarGameCopy has failed");
		return 0;
	}
	dest->currentPlayer = src->currentPlayer;
	dest->difficulty = src -> difficulty;
	dest->gameMode = src->gameMode;
	dest->userColor = src->userColor;
	dest->gameOver = src->gameOver;
	for(int k=0;k<5;k++){
		dest->castlingBlack[k]=src->castlingBlack[k];
		dest->castlingWhite[k]=src->castlingWhite[k];
	}
//	if(dest->lista!=NULL) spArrayListDestroy(dest->lista);
	if(lista){
		dest->lista = spArrayListCopy(src->lista);
	}
	else{
		spArrayListCopyVoid(src->lista, dest->lista);
	}
	if (dest->lista == NULL){
		spFiarGameDestroy(dest);
		spFiarGameDestroy(src);
		return 0;
	}

	else{
		for (int i = 1 ; i < SP_CHESS_GAME_N_ROWS+1 ; i++){
			for (int j = 1 ; j < SP_CHESS_GAME_N_ROWS+1 ; j++){
				dest->gameBoard[i][j] = BOARD[i][j];
			}
		}
		return 1;
	}
}

void spFiarGameDestroy(SPFiarGame* src){
	if (src==NULL){
		return;
	}
	spArrayListDestroy(src->lista);

	free(src->castlingBlack);
	free(src->castlingWhite);
	free(src);
}

void checkCastling(SPFiarGame* src,int numCastle, char rook, int color, int r_s, int r_d){
	if(rook=='r'){
		if(src->castlingWhite[numCastle]==1){
			BOARD[color][r_s]=emptyChar;
			BOARD[color][r_d]=rook;
			src->castlingWhite[4]=-1;
			src->castlingWhite[3]=-1;
		}
	}
	else{
		if(src->castlingBlack[numCastle]==1){
			BOARD[color][r_s]=emptyChar;
			BOARD[color][r_d]=rook;
			src->castlingBlack[4]=-1;
			src->castlingBlack[3]=-1;
		}
	}
}

SP_CHESS_GAME_MESSAGE spFiarGameSetMove(SPFiarGame* src, move* move1, int flagCheck){
	int x, y, i, j;
	char curr_piece, next_piece;
	action* act;
	coord *r_r=createCoord(1,8), *r_l=createCoord(1,1), *c_k=createCoord(1,5);
	if (src == NULL)
		return SP_CHESS_GAME_INVALID_ARGUMENT;
	x = move1->curr_coord->x;
	y = move1->curr_coord->y;
	i = move1->next_coord->x;
	j = move1->next_coord->y;
	curr_piece = BOARD[x][y];
	next_piece = BOARD[i][j];
	// change the board
	BOARD[x][y] = SP_CHESS_GAME_EMPTY_ENTRY;
	BOARD[i][j] = curr_piece;
	// add the action to the ArrayList

	if(curr_piece=='r'){

		if(coordEquals(r_r,move1->curr_coord)==1){
			src->castlingWhite[1]=1;
		}
		else if(coordEquals(r_l,move1->curr_coord)==1){
			src->castlingWhite[2]=1;
		}
		else if(coordEquals(r_r,move1->next_coord)==1){
			src->castlingWhite[3]=-1;
		}
		else if(coordEquals(r_l,move1->next_coord)==1){
			src->castlingWhite[4]=-1;
		}

	}
	else if(curr_piece=='R'){
		r_r->x=8; r_r->y=8; r_l->x=8;r_l->y=1;
		if(coordEquals(r_r,move1->curr_coord)==1){
			src->castlingBlack[1]=1;
		}
		else if(coordEquals(r_l,move1->curr_coord)==1){
			src->castlingBlack[2]=1;
		}
		else if(coordEquals(r_r,move1->next_coord)==1){
			src->castlingBlack[3]=-1;
		}
		else if(coordEquals(r_l,move1->next_coord)==1){
			src->castlingBlack[4]=-1;
		}
	}
	else if(curr_piece=='k'){
		r_r->x=1; r_r->y=7; r_l->x=1;r_l->y=3;
		if(coordEquals(c_k,move1->curr_coord)==1){
			if(!coordEquals(r_r,move1->next_coord)){
				src->castlingWhite[0]=1;
			}
			if(!coordEquals(r_l,move1->next_coord)){
				src->castlingWhite[0]=1;
			}
			if(coordEquals(c_k,move1->next_coord)){
				src->castlingWhite[3]=-1;
				src->castlingWhite[4]=-1;
			}
			if(coordEquals(c_k,move1->curr_coord)&&coordEquals(r_r,move1->next_coord)){
				src->castlingWhite[3]=1;
//				printf("line 298 castlingwhite3=1\n");fflush(stdout);
			}
			if(coordEquals(c_k,move1->curr_coord)&&coordEquals(r_l,move1->next_coord)){
				src->castlingWhite[4]=1;
			}
		}
	}
	else if(curr_piece=='K'){
		r_r->x=8; r_r->y=7; r_l->x=8;r_l->y=3; c_k->x=8;
		if(coordEquals(c_k,move1->curr_coord)==1){
			if(!coordEquals(r_r,move1->next_coord)){
				src->castlingBlack[0]=1;
			}

			if(!coordEquals(r_l,move1->next_coord)){
				src->castlingBlack[0]=1;
			}
			if(coordEquals(c_k,move1->next_coord)){
				src->castlingBlack[3]=-1;
				src->castlingBlack[4]=-1;
			}
			if(coordEquals(c_k,move1->curr_coord)&&coordEquals(r_r,move1->next_coord)){
				src->castlingBlack[3]=1;
			}
			if(coordEquals(c_k,move1->curr_coord)&&coordEquals(r_l,move1->next_coord)){
				src->castlingBlack[4]=1;
			}
		}
	}
	checkCastling(src,3,'r',1,8,6);
	checkCastling(src,4,'r',1,1,4);
	checkCastling(src,3,'R',8,8,6);
	checkCastling(src,4,'R',8,1,4);
	destroyCoord(r_r);destroyCoord(r_l);destroyCoord(c_k);
	if(!flagCheck){
		act = createAction(curr_piece, next_piece, move1);
		if(spArrayListAddLast(src->lista, act)==SP_ARRAY_LIST_FULL){
			spArrayListRemoveFirst(src->lista);
			spArrayListAddLast(src->lista, act);

		}
		destroyAction(act);
	}
	switchPlayer(src);

	return SP_CHESS_GAME_SUCCESS;
}

bool spFiarGameIsValidMove(SPFiarGame* src, int col){
	if (src == NULL || col < 0 || col > 6)
		return false;
	if (BOARD[SP_CHESS_GAME_N_ROWS-1][col] != SP_CHESS_GAME_EMPTY_ENTRY)
		return false;
	return true;
}

SP_CHESS_GAME_MESSAGE spFiarGameUndoNoLista(SPFiarGame* src, move* move1,char srcPiece, char destPiece){
		int x, y, i, j;

		if (src == NULL)
			return SP_CHESS_GAME_INVALID_ARGUMENT;
		x = move1->curr_coord->x;
		y = move1->curr_coord->y;
		i = move1->next_coord->x;
		j = move1->next_coord->y;

		//retrieve board
		BOARD[i][j] = destPiece;
		BOARD[x][y] = srcPiece;
		// undo castling
		if((srcPiece=='k')||(srcPiece=='K')) undoCastling(src,0,move1,srcPiece,destPiece);
		if((srcPiece=='r')||(srcPiece=='R')) undoRook(src,0,move1,srcPiece,destPiece);

		switchPlayer(src);
		return SP_CHESS_GAME_SUCCESS;
}

void undoCastling(SPFiarGame* src , int lista,move* move1,char srcPiece, char destPiece){
	action* lastAction;
	int flag=0;
	if(lista) {
		lastAction =spArrayListGetLast(src->lista);
	}
	else{
		flag=1;
		lastAction=createAction(srcPiece,destPiece,move1);
	}
	int color=1;
	char rook='r';

	if(lastAction->curr_piece=='K'){
		rook='R';
		color=8;
	}
	coord* coord_k=createCoord(color,5), *coord_r=createCoord(color,7), *coord_l=createCoord(color,3);
	if(coordEquals(coord_k,lastAction->moovit->curr_coord)==1){
		if(coordEquals(coord_r,lastAction->moovit->next_coord)==1){
			BOARD[color][6]=emptyChar;
			BOARD[color][8]=rook;
			if(color==1){
				src->castlingWhite[0]=0;
				src->castlingWhite[1]=0;
				src->castlingWhite[3]=0;
				src->castlingWhite[4]=0;
			}
			else{
				src->castlingBlack[0]=0;
				src->castlingBlack[1]=0;
				src->castlingBlack[3]=0;
				src->castlingBlack[4]=0;
			}
		}
		else if(coordEquals(coord_l,lastAction->moovit->next_coord)==1){
			BOARD[color][4]=emptyChar;
			BOARD[color][1]=rook;
			if(color==1){
				src->castlingWhite[0]=0;
				src->castlingWhite[2]=0;
				src->castlingWhite[3]=0;
				src->castlingWhite[4]=0;
			}
			else{
				src->castlingBlack[0]=0;
				src->castlingBlack[2]=0;
				src->castlingBlack[3]=0;
				src->castlingBlack[4]=0;
			}
		}
		else{
			if(color==1){
				src->castlingWhite[0]=0;
			}
			else{
				src->castlingBlack[0]=0;
			}
		}
	}
	destroyCoord(coord_k); destroyCoord(coord_l);destroyCoord(coord_r);
	if(flag) destroyAction(lastAction);

}

void undoRook(SPFiarGame* src, int lista,move* move1,char srcPiece, char destPiece){
	action* cast;
	int flag=0;
	if(lista) {
		cast =spArrayListGetLast(src->lista);
	}
	else{
		flag=1;
		cast=createAction(srcPiece,destPiece,move1);
	}
	char rook='r';
	int color=1;
	coord *r_r, *r_l;
	if(cast->curr_piece=='R'){
		rook='R';
		color=8;
	}
	r_r=createCoord(color,8); r_l=createCoord(color,1);
	if((coordEquals(r_r,cast->moovit->curr_coord)==1)&&(cast->curr_piece==rook)){
		if(color==1){
			src->castlingWhite[1]=0;
		}
		else{
			src->castlingBlack[1]=0;
		}
	}
	if((coordEquals(r_l,cast->moovit->curr_coord)==1)&&(cast->curr_piece==rook)){
		if(color==1){
			src->castlingWhite[2]=0;
		}
		else{
			src->castlingBlack[2]=0;
		}
	}
	destroyCoord(r_r);destroyCoord(r_l);
	if(flag) destroyAction(cast);

}

SP_CHESS_GAME_MESSAGE spFiarGameUndoPrevMove(SPFiarGame* src){
	int x, y, i, j;
	char curr_piece, next_piece;
	if (src == NULL)
		return SP_CHESS_GAME_INVALID_ARGUMENT;
	if(spArrayListIsEmpty(src->lista))
		return SP_CHESS_GAME_NO_HISTORY;
	x = (spArrayListGetLast(src->lista))->moovit->curr_coord->x;
	y = spArrayListGetLast(src->lista)->moovit->curr_coord->y;
	i = spArrayListGetLast(src->lista)->moovit->next_coord->x;
	j = spArrayListGetLast(src->lista)->moovit->next_coord->y;
	curr_piece = spArrayListGetLast(src->lista)->curr_piece;
	next_piece = spArrayListGetLast(src->lista)->next_piece;
	//retrieve board

	BOARD[i][j] = next_piece;
	BOARD[x][y] = curr_piece;

	// undo castling
	if((curr_piece=='k')||(curr_piece=='K')) undoCastling(src,1,NULL,'a','a');
	if((curr_piece=='r')||(curr_piece=='R')) undoRook(src,1,NULL,'a','a');
	spArrayListRemoveLast(src->lista);
	switchPlayer(src);
	return SP_CHESS_GAME_SUCCESS;
}

void spPrintLine(){
	printf("  -----------------\n");fflush(stdout);
	printf("   A B C D E F G H\n");fflush(stdout);
}

void spPrintBoard(SPFiarGame* src, int request){
	int i, j;
	char* player="black";
	for (j = SP_CHESS_GAME_N_ROWS; j >= 1; j--)
	{
		printf((j < 9 ? "%d| " : "%d| "), j);fflush(stdout);
		for (i = 1; i < SP_CHESS_GAME_N_ROWS+1; i++){
			printf("%c ", BOARD[j][i]);fflush(stdout);
		}
		printf("|\n");fflush(stdout);
	}
	spPrintLine();
	if(request){
		if(src->currentPlayer) player="white";
		printf("%s player - enter your move:\n",player);fflush(stdout);
	}
}

void initBoard(SPFiarGame* src){
	int i, l, k;
	for (k = 1; k <= SP_CHESS_GAME_N_ROWS; k++){
		for (l = 1; l <= SP_CHESS_GAME_N_ROWS; l++){
			BOARD[l][k] = SP_CHESS_GAME_EMPTY_ENTRY;
		}
	}
	for (i = 0; i < SP_CHESS_GAME_N_ROWS; i++){
		BOARD[2][i+1] = 'm';
		BOARD[7][i+1] = 'M';
	}
	BOARD[1][1] = BOARD[1][8] = 'r';
	BOARD[1][2] = BOARD[1][7] = 'n';
	BOARD[1][3] = BOARD[1][6] = 'b';
	BOARD[1][4] = 'q';
	BOARD[1][5] = 'k';

	BOARD[8][1] = BOARD[8][8] = 'R';
	BOARD[8][2] = BOARD[8][7] = 'N';
	BOARD[8][3] = BOARD[8][6] = 'B';
	BOARD[8][4] = 'Q';
	BOARD[8][5] = 'K';
}



char spFiarGameGetCurrentPlayer(SPFiarGame* src){
	// 2 player mode
	if (src->currentPlayer ==  SP_CHESS_GAME_2PLAYERS_PLAYER_1_SYMBOL)
			return SP_CHESS_GAME_2PLAYERS_PLAYER_1_SYMBOL;
	else if (src->currentPlayer ==  SP_CHESS_GAME_2PLAYERS_PLAYER_2_SYMBOL)
		return SP_CHESS_GAME_2PLAYERS_PLAYER_2_SYMBOL;
	// 1 player mode
	else if (src->currentPlayer ==  SP_CHESS_GAME_1PLAYER_SYMBOL)
			return SP_CHESS_GAME_1PLAYER_SYMBOL;
	else if (src->currentPlayer ==  SP_FAIR_GAME_COMPUTER_SYMBOL)
		return SP_FAIR_GAME_COMPUTER_SYMBOL;

	return SP_CHESS_GAME_EMPTY_ENTRY;
}

void switchPlayer(SPFiarGame* src){
	// 2 player mode
	if (spFiarGameGetCurrentPlayer(src) == SP_CHESS_GAME_2PLAYERS_PLAYER_1_SYMBOL)
		src->currentPlayer = SP_CHESS_GAME_2PLAYERS_PLAYER_2_SYMBOL;
	else if (spFiarGameGetCurrentPlayer(src) == SP_CHESS_GAME_2PLAYERS_PLAYER_2_SYMBOL)
		src->currentPlayer = SP_CHESS_GAME_2PLAYERS_PLAYER_1_SYMBOL;
	// 1 player mode
	else if (spFiarGameGetCurrentPlayer(src) == SP_CHESS_GAME_1PLAYER_SYMBOL)
		src->currentPlayer = SP_FAIR_GAME_COMPUTER_SYMBOL;
	else if (spFiarGameGetCurrentPlayer(src) == SP_FAIR_GAME_COMPUTER_SYMBOL)
		src->currentPlayer = SP_CHESS_GAME_1PLAYER_SYMBOL;
}

int boardScore (SPFiarGame* src){
	int score = 0;
	for (int i = 1; i < SP_CHESS_GAME_N_ROWS+1; i++) {
		for (int j = 1; j < SP_CHESS_GAME_N_ROWS+1; j++) {
			score += boardScoreCases(BOARD[i][j]);
		}
	}
	return score;
}

int boardScoreCases(char piece){
	switch (piece){
	case 'm':
			return 1;
			break;
	case 'M':
		return -1;
		break;
	case 'r':
			return 5;
			break;
	case 'R':
		return -5;
		break;
	case 'n':
			return 3;
			break;
	case  'N':
		return -3;
		break;
	case 'b':
		return 3;
		break;
	case 'B':
		return -3;
		break;
	case 'q':
		return 9;
		break;
	case 'Q':
		return -9;
		break;
	case 'k':
		return 100;
		break;
	case 'K':
		return -100;
		break;
	default:
		return 0;
		break;
	}
	return 0;
}

void spQuit(SPFiarGame* src){
	spFiarGameDestroy(src);
	printf("Exiting...\n");
	exit(1);
}




