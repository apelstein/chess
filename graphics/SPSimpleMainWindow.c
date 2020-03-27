#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SPSimpleMainWindow.h"


//Helper function to create buttons in the simple window;

int xmlFileIsEmpty(char* path){
	FILE *fptr;
	unsigned long len;  int flag=1;
	if ( !( fptr = fopen( path, "r" ))){
	    printf( "File could not be opened to retrieve your data from it.\n" );
	}
	else {
	    fseek(fptr, 0, SEEK_END);
	    len = (unsigned long)ftell(fptr);
	    if (len > 0) {  //check if the file is empty or not.
	        flag=  0;

	    }
	    fclose( fptr );
	}
	return flag;
}

void createBackground (SPSimpleWindow* window, char* image){
	SDL_Surface* loadingSurface = SDL_LoadBMP(image); //We use the surface as a temp var;
	SDL_Texture* buttonTexture = SDL_CreateTextureFromSurface(window->windowRenderer,
			loadingSurface);
	window->background = buttonTexture;
	SDL_FreeSurface(loadingSurface);

}

Widget** createGameWindowWidgets(SDL_Renderer* renderer, int numOfWidgets,SPFiarGame* currentGame){
	if (renderer == NULL ) {

			return NULL ;
		}
	SDL_Rect rects[7]={{ .x = 0, .y = 0, .h = 600, .w = 800 },
			{ .x = 29, .y = 29, .h = 57, .w = 221 },
			{ .x = 29, .y = 104, .h = 57, .w = 221 },
			{ .x = 29, .y = 177, .h = 57, .w = 221 },
			{ .x = 29, .y = 250, .h = 57, .w = 221 },
			{ .x = 29, .y = 425, .h = 57, .w = 221 },
			{ .x = 29, .y = 502, .h = 57, .w = 221 }
	};//
	char p;
	char *tempImage;
	SDL_Rect tempRect={ .x = 221, .y = 537, .h = 62, .w = 62 }, *tempRect2;
	SDL_Rect* tr=&tempRect;
	char* bg_image="./graphics/images/game/game_window_bg.bmp";
	char * imagesWhite[7]={bg_image,"./graphics/images/game/green.bmp",
			"./graphics/images/game/green.bmp",
			"./graphics/images/game/green.bmp",
				"./graphics/images/game/undo_white.bmp",
				"./graphics/images/game/green.bmp",
				"./graphics/images/game/green.bmp"};
	char * imagesRed[7]={bg_image,"./graphics/images/game/green.bmp",
			"./graphics/images/game/green.bmp",
			"./graphics/images/game/green.bmp",
				"./graphics/images/game/undo_red.bmp",
				"./graphics/images/game/green.bmp",
				"./graphics/images/game/green.bmp"};
	char * pieces[12]={"./graphics/images/game/white_pawn_greenback.bmp",
			"./graphics/images/game/white_knight_greenback.bmp",
			"./graphics/images/game/white_bishop_greenback.bmp",
			"./graphics/images/game/white_rook_greenback.bmp",
			"./graphics/images/game/white_queen_greenback.bmp",
			"./graphics/images/game/white_king_greenback.bmp",
			"./graphics/images/game/black_pawn_greenback.bmp",
			"./graphics/images/game/black_knight_greenback.bmp",
			"./graphics/images/game/black_bishop_greenback.bmp",
			"./graphics/images/game/black_rook_greenback.bmp",
			"./graphics/images/game/black_queen_greenback.bmp",
			"./graphics/images/game/black_king_greenback.bmp"
};
	int i=0;
		Widget** widgets = malloc(sizeof(Widget*) * numOfWidgets);
		if (widgets == NULL ) {
			return NULL ;
		}
//		printf("line 83 \n");fflush(stdout);
//		createBackground(s_window,bg_image);
		for(;i<7;i++){
			widgets[i]=createDoubleButton(renderer,&rects[i],imagesWhite[i],imagesRed[i]);
//			printf("line 76 button [%d] was created\n",i);fflush(stdout);

		}


		for(int k=1;k<=SP_CHESS_GAME_N_ROWS;k++){
			for(int l=1;l<=SP_CHESS_GAME_N_ROWS;l++){

					p=currentGame->gameBoard[k][l];
					if(p!=emptyChar){
						tempRect.x+=( l*62);
						tempRect.y -= (k*62);
						tr=&tempRect;
						tempRect2=spCopyRect(tr);
						switch (p){
							case 'm':
									tempImage=pieces[0];
									break;
							case 'M':
								tempImage=pieces[6];
								break;
							case 'r':
								tempImage=pieces[3];
									break;
							case 'R':
								tempImage=pieces[9];
								break;
							case 'n':
								tempImage=pieces[1];
									break;
							case  'N':
								tempImage=pieces[7];
								break;
							case 'b':
								tempImage=pieces[2];
								break;
							case 'B':
								tempImage=pieces[8];
								break;
							case 'q':
								tempImage=pieces[4];
								break;
							case 'Q':
								tempImage=pieces[10];
								break;
							case 'k':
								tempImage=pieces[5];
								break;
							case 'K':
								tempImage=pieces[11];
								break;
						}
//							rectCpy = spCopyRect(&tempRect);

							widgets[i]=createPieceButton(renderer,tempRect2,tempImage);
//							printf("line 128 button [%d] was created\n",i);fflush(stdout);

							tempRect.x-=( l*62);
							tempRect.y += (k*62);
							i+=1;
					}


			}
		}

		for(int j=i;j<39;j++){
			widgets[j] = NULL;

		}
		return widgets;

}

Widget** createLoadWindowWidgets(SDL_Renderer* renderer, int numOfWidgets){
	if (renderer == NULL ) {

			return NULL ;
		}
	SDL_Rect rects[7]={{ .x = 250, .y = 500, .h = 80, .w = 180 },
			{ .x = 50, .y = 500, .h = 80, .w = 180 },
			{ .x = 75, .y = 50, .h = 50, .w = 200 },
			{ .x = 75, .y = 125, .h = 50, .w = 200 },
			{ .x = 75, .y = 200, .h = 50, .w = 200 },
			{ .x = 75, .y = 275, .h = 50, .w = 200 },
			{ .x = 75, .y = 350, .h = 50, .w = 200 }
	};

	char * imagesWhite[7]={"./graphics/images/load/back.bmp",
				"./graphics/images/load/load_white.bmp",
				"./graphics/images/load/GameSlot1_white.bmp",
				"./graphics/images/load/GameSlot2_white.bmp",
				"./graphics/images/load/GameSlot3_white.bmp",
				"./graphics/images/load/GameSlot4_white.bmp",
				"./graphics/images/load/GameSlot5_white.bmp"};
	char * imagesRed[7]={"./graphics/images/load/back.bmp",
				"./graphics/images/load/load_red.bmp",
				"./graphics/images/load/GameSlot1_red.bmp",
				"./graphics/images/load/GameSlot2_red.bmp",
				"./graphics/images/load/GameSlot3_red.bmp",
				"./graphics/images/load/GameSlot4_red.bmp",
				"./graphics/images/load/GameSlot5_red.bmp"};

		Widget** widgets = malloc(sizeof(Widget*) * numOfWidgets);
		if (widgets == NULL ) {
			return NULL ;
		}
		for(int i=0;i<numOfWidgets;i++){
			widgets[i]=createDoubleButton(renderer,&rects[i],imagesWhite[i],imagesRed[i]);
		}
		for(int j=0;j<numOfWidgets;j++){
			if (widgets[j] == NULL ) {
				for(int k=0;k<7;k++)
					destroyWidget(widgets[k]); //NULL SAFE
				free(widgets);
				return NULL ;
			}
		}
		return widgets;

}

Widget** createSettingsWindowWidgets(SDL_Renderer* renderer, int numOfWidgets){
	if (renderer == NULL ) {
			return NULL ;
		}

	SDL_Rect rects[13] = {{ .x = 0, .y = 0, .h = 600, .w = 800 },//background 0
			{ .x = 26, .y = 448, .h = 50, .w = 200 },//start 1
			{ .x = 26, .y = 522, .h = 50, .w = 200 },//back 2
			{ .x = 182, .y = 103, .h = 50, .w = 200 },//one player 3
			{ .x = 436, .y = 103, .h = 50, .w = 200 },//two players 4
			{ .x = 311, .y = 181, .h = 50, .w = 140 },//difficulty 5
			{ .x = 77, .y = 245, .h = 50, .w = 130 },//noob 6
			{ .x = 240, .y = 245, .h = 50, .w = 130 },//easy 7
			{ .x = 398, .y = 245, .h = 50, .w = 130 },//moderate 8
			{ .x = 590, .y = 245, .h = 50, .w = 130 },//hard 9
			{ .x = 337, .y = 308, .h = 50, .w = 100 },//color 10
			{ .x = 133, .y = 366, .h = 50, .w = 200 },//white 11
			{ .x = 455, .y = 366, .h = 50, .w = 200 }//black 12
	};
	char *bg_image = "./graphics/images/settings/settings_background.bmp";
	char * imagesRed[13]={bg_image,"./graphics/images/settings/start_red.bmp",
			"./graphics/images/settings/back_red.bmp",
			"./graphics/images/settings/one_player_red.bmp",
			"./graphics/images/settings/two_players_red.bmp",
			"./graphics/images/settings/difficulty_title.bmp",
			"./graphics/images/settings/noob_red.bmp",
			"./graphics/images/settings/easy_red.bmp",
			"./graphics/images/settings/moderate_red.bmp",
			"./graphics/images/settings/hard_red.bmp",
			"./graphics/images/settings/color_title.bmp",
			"./graphics/images/settings/color_white_red.bmp",
			"./graphics/images/settings/color_black_red.bmp",
	};

	char * imagesWhite[13]={bg_image,"./graphics/images/settings/start_red.bmp",
			"./graphics/images/settings/back_red.bmp",
			"./graphics/images/settings/one_player_white.bmp",
			"./graphics/images/settings/two_players_white.bmp",
			"./graphics/images/settings/difficulty_title.bmp",
			"./graphics/images/settings/noob_white.bmp",
			"./graphics/images/settings/easy_white.bmp",
			"./graphics/images/settings/moderate_white.bmp",
			"./graphics/images/settings/hard_white.bmp",
			"./graphics/images/settings/color_title.bmp",
			"./graphics/images/settings/color_white_white.bmp",
			"./graphics/images/settings/color_black_white.bmp",
	};

//	char * imagesTriple[13]={bg_image,"./graphics/images/settings/start_red.bmp",
//			"./graphics/images/settings/back_red.bmp",
//			"./graphics/images/settings/one_player_white.bmp",
//			"./graphics/images/settings/two_players_white.bmp",
//			"./graphics/images/settings/difficulty_title_white.bmp",
//			"./graphics/images/settings/easy_white_plain.bmp",//
//			"./graphics/images/settings/easy_white_plain.bmp",//
//			"./graphics/images/settings/easy_white_plain.bmp",//
//			"./graphics/images/settings/easy_white_plain.bmp",//
//			"./graphics/images/settings/color_title_white.bmp",
//			"./graphics/images/settings/color_white_white_plain.bmp",//
//			"./graphics/images/settings/color_white_white_plain.bmp",//
//	};



		Widget** widgets = malloc(sizeof(Widget*) * numOfWidgets);
		if (widgets == NULL ) {
			return NULL ;
		}
		for(int i=0;i<numOfWidgets;i++){
			if ((i==3) || (i==7) || (i==11))//one player
				widgets[i]=createDoubleButton(renderer,&rects[i],imagesRed[i],imagesWhite[i]);
			else //noob, moderate, hard, black
				widgets[i]=createDoubleButton(renderer,&rects[i],imagesWhite[i],imagesRed[i]);

		}
		for(int j=0;j<numOfWidgets;j++){
			if (widgets[j] == NULL ) {
				for(int k=0;k<13;k++)
					destroyWidget(widgets[k]); //NULL SAFE
				free(widgets);
				return NULL ;
			}
		}
		return widgets;

}


Widget** createMainWindowWidgets(SDL_Renderer* renderer) {
	if (renderer == NULL ) {

		return NULL ;
	}
	SDL_Rect rects[3]={{ .x = 200, .y = 100, .h = 54, .w = 208 },
			{ .x = 200, .y = 175, .h = 53, .w = 208 },
			{ .x = 200, .y = 350, .h = 54, .w = 207 }

	};
	char* images[3]={"./graphics/images/main/new_game.bmp",
			"./graphics/images/main/load_game.bmp",
			"./graphics/images/main/quit.bmp"
	};
	Widget** widgets = malloc(sizeof(Widget*) * 3);
	if (widgets == NULL ) {

		return NULL ;
	}

	for(int i=0;i<3;i++){
		widgets[i]=createSimpleButton(renderer,&rects[i],images[i]);
	}
	for(int j=0;j<3;j++){
		if (widgets[j] == NULL ) {
			destroyWidget(widgets[0]); //NULL SAFE
			destroyWidget(widgets[1]); //NULL SAFE
			destroyWidget(widgets[2]); //NULL SAFE
			free(widgets);
			return NULL ;
		}
	}
	return widgets;
}



Widget** createSimpleWindowWidgets(SDL_Renderer* renderer) {
	if (renderer == NULL ) {
		return NULL ;
	}
	Widget** widgets = malloc(sizeof(Widget*) * 2);
	if (widgets == NULL ) {
		return NULL ;
	}
	SDL_Rect startR = { .x = 75, .y = 100, .h = 100, .w = 250 };
	SDL_Rect exitR = { .x = 75, .y = 250, .h = 100, .w = 250 };
	widgets[0] = createSimpleButton(renderer, &startR, "./start.bmp");
	widgets[1] = createSimpleButton(renderer, &exitR, "./exit.bmp");
	if (widgets[0] == NULL || widgets[1] == NULL ) {
		destroyWidget(widgets[0]); //NULL SAFE
		destroyWidget(widgets[1]); //NULL SAFE
		free(widgets);
		return NULL ;
	}
	return widgets;
}
SPWindow* createMainWindow(){
	return createSimpleWindow(MAIN_WIN,3);
}

SPWindow* createLoadWindow(){
	char * savedGames[5]={"./graphics/savedGames/GameSlot1.xml",
			"./graphics/savedGames/GameSlot2.xml",
			"./graphics/savedGames/GameSlot3.xml",
			"./graphics/savedGames/GameSlot4.xml",
			"./graphics/savedGames/GameSlot5.xml"
	};
	int i=0;
	for(;i<5;i++){
		if(xmlFileIsEmpty(savedGames[i])){
			break;
		}
	}
	return createSimpleWindow(LOAD_WIN,i+2);
}

SPWindow* createSettingsWindow(){
	SPWindow* res;
	res= createSimpleWindow(SETTINGS_WIN, 13);
	return res;
}

SPWindow* createGameWindow(SP_WIN_MESSAGE slot, int* settingsFlags){
	int numWidg=7;
	int index= (int) slot;
	int doTheFirstMove=0;
	SPWindow* res;
	SPSimpleWindow* castData;

	char * savedGames[6]={"./graphics/savedGames/GameSlot1.xml",
			"./graphics/savedGames/GameSlot2.xml",
			"./graphics/savedGames/GameSlot3.xml",
			"./graphics/savedGames/GameSlot4.xml",
			"./graphics/savedGames/GameSlot5.xml",
			"./graphics/savedGames/generic_game.xml"
	};
	SPFiarGame* newGame;

	newGame = spFiarRAWGameCreate(undoListSize);
	SP_CHESS_GAME_MESSAGE load_succeeded;
	if(index<=6){
		if(xmlFileIsEmpty(savedGames[index-2])){
			printf("line 295 the file is empty\n");fflush(stdout);
		}
//		printf("line 298 before the loading\n");fflush(stdout);
		load_succeeded = loadGame(savedGames[index-2], newGame);
//		printf("line 300 after the loading\n");fflush(stdout);
		if(newGame->gameMode==2){
			newGame->difficulty=0;
			newGame->userColor=1;
		}
	}
	else{
		// here comes the new game instead of load game
		// we need to put here fields to insert to the
		//config. of the new game that we will send to
		// createRawGame
		load_succeeded = loadGame(savedGames[5], newGame);
		newGame->gameMode=settingsFlags[0];
		newGame->currentPlayer=1;
		newGame->userColor=settingsFlags[1];
		newGame->difficulty=settingsFlags[2];
		doTheFirstMove=1;

	}
	if (load_succeeded == SP_CHESS_GAME_SUCCESS){
		newGame->gameOver=0;
		newGame->guiCheck=1;
//		for(int i=1;i<=SP_CHESS_GAME_N_ROWS;i++){
//			for(int j=1;j<=SP_CHESS_GAME_N_ROWS;j++){
//				if(newGame->gameBoard[i][j]!=emptyChar){
//					numWidg+=1;
//				}
//
//			}
//		}
		numWidg=39;
//		printf("line 321 numofwidg=%d ? 39\n",numWidg);fflush(stdout);

	}
	 res=createSimpleWindow(GAME_WIN,numWidg);
	 res->theGame=newGame;
	 castData=(SPSimpleWindow*) (res->data);
//	 printf("line 331 no problemos before the widgets\n");fflush(stdout);
	 res->didYouSave=1;
	 if ((res->theGame->userColor == SP_CHESS_GAME_BLACK)&&doTheFirstMove){//if we chose black the computer has to start
		 computerStrategy(res->theGame);
		 res->theGame->lista=spArrayListCreate(undoListSize);
	 }
	 castData->widgets=createGameWindowWidgets(castData->windowRenderer,numWidg,res->theGame);
	 res->data=(void*) castData;
	 res->theAction=createAction(emptyChar,emptyChar,createMove(InvalidCoord(),InvalidCoord()));
	 return res;
}




SPWindow* createSimpleWindow(NUM_WIN num, int numOfWidgets) {
	SPWindow* res = malloc(sizeof(SPWindow));
	SPSimpleWindow* data = malloc(sizeof(SPSimpleWindow));
	SDL_Window* window = SDL_CreateWindow("Chess", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1,
			SDL_RENDERER_ACCELERATED);
	Widget** widgets;
	if(num==MAIN_WIN) widgets= createMainWindowWidgets(renderer);
	else if(num==LOAD_WIN) widgets= createLoadWindowWidgets(renderer,numOfWidgets);
	else if(num==SETTINGS_WIN) widgets= createSettingsWindowWidgets(renderer,numOfWidgets);
//	else if(num==GAME_WIN) widgets= createGameWindowWidgets(renderer);
	if (res == NULL || data == NULL || window == NULL || renderer == NULL
			|| widgets == NULL ) {

		free(res);
		free(data);
		free(widgets);
		//We first destroy the renderer
		SDL_DestroyRenderer(renderer); //NULL safe
		SDL_DestroyWindow(window); //NULL safe
		return NULL ;
	}
	if(num!=GAME_WIN){
		data->widgets = widgets;
	}
	data->numOfWidgets = numOfWidgets;
	data->buttonsFlags=(int*) calloc(data->numOfWidgets,sizeof(int));
	if(num==SETTINGS_WIN){
		//0,  						1   	,2					,3						,4					,5				,6		  ,7				,8				,9		,10		 ,11		,12
		//background, start, back, one player, two players, difficulty, noob, easy, moderate, hard, color, white, black
		data->buttonsFlags[3]=1;
		data->buttonsFlags[7]=1;
		data->buttonsFlags[11]=1;
	}
	data->window = window;
	data->windowRenderer = renderer;
	data->background = NULL;
	res->data = (void*) data;
	res->destroyWindow = destroySimpleWindow;
	res->drawWindow = drawSimpleWindow;

	if(num==MAIN_WIN){
		res->handleEventWindow= handleEvenetMainWindow;
		res->theAction = NULL;
		res->theGame = NULL;
	}
	else if(num==LOAD_WIN){
		res->theAction = NULL;
		res->theGame = NULL;
		res->handleEventWindow= handleEvenetLoadWindow;
	}
	else if(num==SETTINGS_WIN){
		res->handleEventWindow= handleEvenetSettingsWindow;
		res->theAction = NULL;
		res->theGame = NULL;
	}
//	else if(num==GAME_WIN) res->handleEventWindow= handleEvenetMainWindow;

	return res;
}
void destroySimpleWindow(SPWindow* src) {
	if (src == NULL ) {
		return;
	}
	SPSimpleWindow* data = (SPSimpleWindow*) src->data;
	int i = 0;
	for (; i < data->numOfWidgets; i++) {
		destroyWidget(data->widgets[i]);//
	}
	free(data->widgets);
	if (data->background != NULL)
		SDL_DestroyTexture(data->background);
	SDL_DestroyRenderer(data->windowRenderer);
	SDL_DestroyWindow(data->window);
	free(data);
	free(src);
}
void drawSimpleWindow(SPWindow* src) {
	if (src == NULL ) {
		return;
	}
	SPSimpleWindow* data = (SPSimpleWindow*) src->data;
	//Draw window
	SDL_SetRenderDrawColor(data->windowRenderer, 255, 255, 255, 255);
	SDL_RenderClear(data->windowRenderer);
	int i = 0;
	for (; i < data->numOfWidgets; i++) {
		if(data->widgets[i]!=NULL)
		(data->widgets[i])->drawWidget(data->widgets[i]);
	}
	SDL_RenderPresent(data->windowRenderer);
}

//int handleEvenetSimpleWindow(SPWindow* src, SDL_Event* event){
//	if(src == NULL || event==NULL){
//		return 5;
//	}
//	SPSimpleWindow* data = (SPSimpleWindow*)src->data;
//	int i =0;
//	for(;i<data->numOfWidgets;i++){
//		if(data->widgets[i]->handleEvent(data->widgets[i],event)
//				==
//						WINDOW_QUIT)
//			return 5;
//	}
//	return 1;
//}

char *  getPicLoc(char type){
	switch (type)
	{

	case emptyChar:
		return NULL;
	case 'M':
		return "./graphics/images/game/black_pawn_greenback.bmp";
	case 'N':
		return "./graphics/images/game/black_knight_greenback.bmp";
	case 'B':
		return "./graphics/images/game/black_bishop_greenback.bmp";
	case 'R':
		return "./graphics/images/game/black_rook_greenback.bmp";
	case 'Q':
		return "./graphics/images/game/black_queen_greenback.bmp";
	case 'K':
		return "./graphics/images/game/black_king_greenback.bmp";
	case 'm':
		return "./graphics/images/game/white_pawn_greenback.bmp";
	case 'n':
		return "./graphics/images/game/white_knight_greenback.bmp";
	case 'b':
		return "./graphics/images/game/white_bishop_greenback.bmp";
	case 'r':
		return "./graphics/images/game/white_rook_greenback.bmp";
	case 'q':
		return "./graphics/images/game/white_queen_greenback.bmp";
	case 'k':
		return "./graphics/images/game/white_king_greenback.bmp";
	default:
		return NULL;
	}
}

int copyFromFileToFile(char* sourceFile, char* destFile){
	FILE *file;
	FILE *write;
	char line [ 256 ]; /* or other suitable maximum line size */
	char linec [256]; // copy of line
	file = fopen ( sourceFile, "r" );
	write = fopen (destFile, "w" );
    if ( file != NULL ){
    	while ( fgets ( line, sizeof line, file ) != NULL ) /* read a line */{
//    		fputs ( line, stdout ); /* write the line */
    		strcpy(linec, line);
    		fprintf (write ,"%s", linec);
    		// fprintf (write , "\n");         // No need to give \n
    	}
    	fclose (write);
    	fclose ( file );
    	return 1;
    }
    else{
    	return 0; /* why didn't the file open? */
    }

}


int handleSave(SPWindow* src){
	int copyFlag;
	SP_CHESS_GAME_MESSAGE msg;
	char * savedGames[5]={"./graphics/savedGames/GameSlot1.xml",
			"./graphics/savedGames/GameSlot2.xml",
			"./graphics/savedGames/GameSlot3.xml",
			"./graphics/savedGames/GameSlot4.xml",
			"./graphics/savedGames/GameSlot5.xml"
	};

	for(int i=3;i>=0;i--){
		if(!xmlFileIsEmpty(savedGames[i])){
			copyFlag=copyFromFileToFile(savedGames[i],savedGames[i+1]);
			if(!copyFlag){
				return 0;
			}

		}
	}
	msg=saveGame(src->theGame,savedGames[0]);
	if(msg==SP_CHESS_GAME_SUCCESS) return 1;
	else return 0;


}

SP_WIN_MESSAGE ExitMainHandle(SPWindow* src,char* title, char* question,SP_WIN_MESSAGE msg ){
	int answer;
	if(!(src->didYouSave)){
		answer=PopTheQuestion(title,question);
		switch(answer){
		case 0:
			return WINDOW_NONE;
			break;
		case 1:
			return msg;
			break;
		case 2:
			handleSave(src);
			return msg;
			break;
		}
		return WINDOW_NONE;
	}
	else return msg;
}

void initiateAction(SPWindow* src){
	action* castAction= (action*) (src->theAction);
	castAction->curr_piece=emptyChar;
	castAction->next_piece=emptyChar;
	castAction->moovit->curr_coord->x=0;
	castAction->moovit->curr_coord->y=0;
	castAction->moovit->next_coord->x=0;
	castAction->moovit->next_coord->y=0;
}

void destroyWidgetsGood(SPSimpleWindow* data){
	for(int y=0;y<data->numOfWidgets;y++){
		if(data->widgets[y]!=NULL){
			data->widgets[y]->destroyWidget(data->widgets[y]);

		}
		data->widgets[y]=NULL;
	}
}

SP_WIN_MESSAGE handleEvenetGameWindow(SPWindow* src, SDL_Event* event){
	if (src == NULL || event == NULL) {
		return WINDOW_QUIT;
	}
	initiateAction(src);
	SP_WIN_MESSAGE theHandleResult;
	SPFiarGame* tempGame=spFiarRAWGameCreate(undoListSize);
	int button_down=0;
	if(event->type==SDL_MOUSEBUTTONDOWN) button_down=1;
	SPSimpleWindow* data = (SPSimpleWindow*)src->data;
	int canDoUndo=0;
	if(src->theGame->gameMode==2){
		canDoUndo=0;
	}
	else{
		if(spArrayListIsEmpty(src->theGame->lista)) changeDoubleButton(data->widgets[4],0);
		else {
			changeDoubleButton(data->widgets[4],1);
//			printf("line 680 before change: candoundo=%d\n",canDoUndo);fflush(stdout);
			canDoUndo=1;
		}
	}

	int i = 0;
	//runn the basic buttons until i<7
	coord* coor=createCoord(0,0);
	i=0;
	coor->y = (event->button.x - 283+62) / 62;
	coor->x = (475 - event->button.y + 62+62) / 62;
	for (; i < data->numOfWidgets; i++) {
		if(data->widgets[i]!=NULL){
		SP_BUTTON eventResult = data->widgets[i]->handleEvent(data->widgets[i], event);
			if (eventResult == BUTTON_PUSHED) { //button pushed
				if(i<7){
					switch(i){
					case 1: //reset
						loadGame("./graphics/savedGames/generic_game.xml",tempGame);
						tempGame->gameMode=src->theGame->gameMode;
						tempGame->userColor=src->theGame->userColor;
						tempGame->difficulty=src->theGame->difficulty;
						tempGame->currentPlayer=1;
						if(spFiarGameCopyReset(tempGame,src->theGame)){
							if (src->theGame->userColor == SP_CHESS_GAME_BLACK){//if we chose black the computer has to start
								computerStrategy(src->theGame);
								src->theGame->lista=spArrayListCreate(undoListSize);
							}
							spPrintBoard(src->theGame,1);
							spFiarGameDestroy(tempGame);

						}
						else{
							printf("Error: func. resetGame in main_aux.c\n"); fflush(stdout);
						}
						destroyWidgetsGood(data);

						data->numOfWidgets=39;
						data->widgets=createGameWindowWidgets(data->windowRenderer,data->numOfWidgets,src->theGame);

						spPrintBoard(src->theGame,1);
						drawSimpleWindow(src);
						return WINDOW_NONE;
						break;
					case 2: //save
						src->didYouSave=1;
						handleSave(src);
						return WINDOW_NONE;
						break;
					case 3: //load
						return WINDOW_CHANGE_TO_LOAD;
						break;
					case 4: //undo
						if(canDoUndo){
							spUndoMove(src->theGame);
							destroyWidgetsGood(data);
							data->numOfWidgets=39;
							data->widgets=createGameWindowWidgets(data->windowRenderer,data->numOfWidgets,src->theGame);

							drawSimpleWindow(src);
							return WINDOW_NONE;
						}

						break;
					case 5: //back to main menu
						return ExitMainHandle(src,"Back to main menu",
								"Do you want to save before back to main menu?",
								WINDOW_CHANGE_TO_MAIN);
						break;
					case 6: //exit
						return ExitMainHandle(src,"Exit",
								"Do you want to save before exiting?",
								WINDOW_QUIT);						break;
					}
				}
				else{
					if(button_down==1){ //button down
						//printf("line 633 button pushed i=%d\n",i);fflush(stdout);
						if(isValidCoord(coor)){
//							printf("coord is valid\n");fflush(stdout);
//							PrintTheCoord(coor);
//							printf("\n");fflush(stdout);
							src->theAction->moovit->curr_coord = coor;
							src->theAction->curr_piece=getPieceFromCoord(src->theGame,coor);
//							printf("lin 778 the curr piece is %c\n",src->theAction->curr_piece);fflush(stdout);
							theHandleResult= handleMoveEventGameWindow(src, i);
							if(theHandleResult==WINDOW_NONE) src->didYouSave=0;
							return theHandleResult;
						}
					}

				}
			}
		}
	}
	return WINDOW_NONE;
}

SP_WIN_MESSAGE handleMoveEventGameWindow(SPWindow* src, int widgetID) {
	if (src == NULL) {
		return WINDOW_QUIT;
	}
	SPSimpleWindow* data = (SPSimpleWindow*)src->data;
	coord * coor;
	coor=createCoord(0,0);
	SDL_Event  eventFromDrag;
	SDL_Event * eventFromDragPoint = &eventFromDrag;
	SDL_Rect baseR;
	char * picLoc;
	while (eventFromDragPoint->type != SDL_MOUSEBUTTONUP){
		coor->y = (eventFromDragPoint->button.x - 283+62) / 62;
		coor->x = (475 - eventFromDragPoint->button.y + 62+62) / 62;
		SDL_WaitEvent(&eventFromDrag);
		eventFromDragPoint = &eventFromDrag;
		picLoc = getPicLoc(src->theAction->curr_piece);
		baseR.x = eventFromDragPoint->button.x - 62 / 2;
		baseR.y= eventFromDragPoint->button.y - 62 / 2;
		baseR.h = 62;
		baseR.w = 62 ;
		data->widgets[widgetID]->destroyWidget(data->widgets[widgetID]);
		data->widgets[widgetID] = createPieceButton(data->windowRenderer, &baseR, picLoc);
		src->drawWindow(src);
	}
	src->theAction->moovit->next_coord= coor;

	if(isValidCoord(src->theAction->moovit->curr_coord)){
		if(caseMoveGUI(src->theGame,src->theAction->moovit)){
			data->numOfWidgets=39;
			destroyWidgetsGood(data);
			data->widgets=createGameWindowWidgets(data->windowRenderer,39,src->theGame);
			drawSimpleWindow(src);
			//printf("line 682 after createwidgets\n");fflush(stdout);
			if(src->theGame->gameOver==1){
				if(src->theGame->gameMode==2){
					if(src->theGame->currentPlayer) return WINDOW_GAME_PLAYER2_WIN;
					else return WINDOW_GAME_PLAYER1_WIN;
				}
				else{
					if(src->theGame->currentPlayer){
						return WINDOW_GAME_PLAYER2_WIN;
					}
					else{
						return WINDOW_GAME_PLAYER1_WIN;
					}
				}
			}
			else if(src->theGame->gameOver==0){
				return WINDOW_NONE;
			}
			else{
				return WINDOW_GAME_TIE;

			}
			return WINDOW_NONE;
		}
		else{
			destroyWidgetsGood(data);
			data->numOfWidgets=39;
			data->widgets=createGameWindowWidgets(data->windowRenderer,data->numOfWidgets,src->theGame);
			drawSimpleWindow(src);
			return WINDOW_INVALID;
		}

	}
	else return WINDOW_INVALID;

}

int caseMoveGUI(SPFiarGame* game, move* moovit){

	if(moovit==NULL){
		return 0;
	}

	else if(!IAmTouchingMyPiece(game,moovit->curr_coord)){
		printf("The specified position does not contain your piece\n"); fflush(stdout);
		return 0;
	}

	else if(ValidMoveCommand(game,moovit)){
		return PlayMoveCase(game,moovit);

	}
	else{
		printf("Error: Invalid Command\n");fflush(stdout);
		return 0;
	}
}


SP_WIN_MESSAGE handleEvenetLoadWindow(SPWindow* src, SDL_Event* event){
	if(event->type==SDL_MOUSEBUTTONUP){
		if(src == NULL || event==NULL){
				return WINDOW_INVALID;
			}
			SPSimpleWindow* data = (SPSimpleWindow*)src->data;
			SP_WIN_MESSAGE msg;
			int i =0;
			for(;i<data->numOfWidgets;++i){
				if(i<2){

					if(data->widgets[i]->handleEvent(data->widgets[i],event)
									== BUTTON_PUSHED){
//						data->widgets[7]->
						data->buttonsFlags[i]=1;
						//printf("line 461: widgets[%d] was pushed",i);fflush(stdout);
						break;
					}

					else {
					//	printf("line 471 in the else\n");fflush(stdout);
						data->buttonsFlags[i]=0;
					//	printf("line 473 in the else\n");fflush(stdout);

					}
				}
				else{
					if(data->widgets[i]->handleEvent(data->widgets[i],event)
									== BUTTON_PUSHED){
					//	printf("line 470: widgets[%d] was pushed",i);fflush(stdout);
						data->buttonsFlags[i]=1;
					}
					else{
						data->buttonsFlags[i]=0;
					}
				}

			}

			//0,  ,1   ,2,3,4,5,6
			//back,load,1,2,3,4,5
			//back
			if(data->buttonsFlags[0]==1){

				return WINDOW_CHANGE_TO_LAST;
			}
			//load
			if(data->buttonsFlags[1]==1){

				for(int k=2;k<7;k++){
					if(data->buttonsFlags[k]==1){
						msg= (SP_WIN_MESSAGE) k;
						return msg;
					}
				}
				return WINDOW_NONE;
			}
			//slot
			else{
				for(int l=2;l<data->numOfWidgets;l++){
					if(data->buttonsFlags[l]==1){
						changeDoubleButton(data->widgets[1],1);
						changeDoubleButton(data->widgets[l],1);
						for(int j=2;j<data->numOfWidgets;j++){
							if(j!=l){
								data->buttonsFlags[j]=0;
								changeDoubleButton(data->widgets[j],0);
							}
						}
						return WINDOW_NONE;
					}
				}

			}
			return WINDOW_NONE;

	}
	else{
		return WINDOW_NONE;
	}

}

SP_WIN_MESSAGE handleEvenetSettingsWindow(SPWindow* src, SDL_Event* event){
	if(event->type==SDL_MOUSEBUTTONUP){
		if(src == NULL || event==NULL){
				return WINDOW_INVALID;
		}
		SPSimpleWindow* data = (SPSimpleWindow*)src->data;
		int i =1; //not including background
		for(;i<data->numOfWidgets;++i){
		//0,  					1   	,2					,3		      ,4					,5			,6		  ,7			,8				,9		,10	 ,11	   ,12
		//background, start, back, one player, two players, difficulty, noob, easy, moderate, hard, color, white, black
			if(data->widgets[i]!=NULL){
				if(data->widgets[i]->handleEvent(data->widgets[i],event)
													== BUTTON_PUSHED){
					if((i==1) || (i==2)){ //clicked on start or back
							data->buttonsFlags[i]=1;
							break;
					}
					else if (i==3){
						data->buttonsFlags[i]=1;		//turn one player to red
						data->buttonsFlags[i+1]=0; //turn two players to white
						printf("line 784: buttonFlags = [%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d]\n",
								data->buttonsFlags[0],data->buttonsFlags[1],data->buttonsFlags[2],data->buttonsFlags[3],data->buttonsFlags[4],data->buttonsFlags[5],
								data->buttonsFlags[6],data->buttonsFlags[7],data->buttonsFlags[8],
								data->buttonsFlags[9],data->buttonsFlags[10],data->buttonsFlags[11],
								data->buttonsFlags[12]);fflush(stdout);
										//break??
					}
					else if (i==4){
						data->buttonsFlags[i]=1;
						data->buttonsFlags[i-1]=0;
						printf("line 784: buttonFlags = [%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d]\n",
								data->buttonsFlags[0],data->buttonsFlags[1],data->buttonsFlags[2],data->buttonsFlags[3],data->buttonsFlags[4],data->buttonsFlags[5],
								data->buttonsFlags[6],data->buttonsFlags[7],data->buttonsFlags[8],
								data->buttonsFlags[9],data->buttonsFlags[10],data->buttonsFlags[11],
								data->buttonsFlags[12]);fflush(stdout);
					}
					else if ((i >=6) && (i<=9)){ //clicked on one of the difficulties
						for (int j=6 ; j<=9 ; j++){
							if (j==i){
								data->buttonsFlags[j]=1;
							}
							else{
								data->buttonsFlags[j]=0;
							}
						}
						//break??
					}
					else if (i==11){
						data->buttonsFlags[i]=1;		//turn color white to red
						data->buttonsFlags[i+1]=0; //turn color black to white
						//break??
					}
					else if (i==12){
						data->buttonsFlags[i]=1;
						data->buttonsFlags[i-1]=0;
					}

				} //end of if button [i] was pushed

			} //end of if widget != null

		}  // end of for loop that collects the handle simple button event

		//0,  						1   	,2					,3						,4					,5				,6		  ,7				,8				,9		,10		 ,11		,12
		//background, start, back, one player, two players, difficulty, noob, easy, moderate, hard, color, white, black
		//printf("line 824: the buttonsflags: \n");fflush(stdout);
//		printf("line 784: buttonFlags = [%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d]\n",
//				data->buttonsFlags[0],data->buttonsFlags[1],data->buttonsFlags[2],data->buttonsFlags[3],data->buttonsFlags[4],data->buttonsFlags[5],
//				data->buttonsFlags[6],data->buttonsFlags[7],data->buttonsFlags[8],
//				data->buttonsFlags[9],data->buttonsFlags[10],data->buttonsFlags[11],
//				data->buttonsFlags[12]);fflush(stdout);
		//start was pushed
		if(data->buttonsFlags[1]==1){
			if(data->buttonsFlags[3]==1){ //One Player
				if(data->buttonsFlags[11]==1){ //white color
					if(data->buttonsFlags[6]==1) return WINDOW_SETTINGS_1_PLAYER_NOOB_WHITE;
					else if(data->buttonsFlags[7]==1) return WINDOW_SETTINGS_1_PLAYER_EASY_WHITE;
					else if(data->buttonsFlags[8]==1) return WINDOW_SETTINGS_1_PLAYER_MODERATE_WHITE;
					else return WINDOW_SETTINGS_1_PLAYER_HARD_WHITE;
				}
				else{ //black color
					if(data->buttonsFlags[6]==1) return WINDOW_SETTINGS_1_PLAYER_NOOB_BLACK;
					else if(data->buttonsFlags[7]==1) return WINDOW_SETTINGS_1_PLAYER_EASY_BLACK;
					else if(data->buttonsFlags[8]==1) return WINDOW_SETTINGS_1_PLAYER_MODERATE_BLACK;
					else return WINDOW_SETTINGS_1_PLAYER_HARD_BLACK;
				}
			}
			else{ //2 players mode;
				return WINDOW_SETTINGS_2_PLAYER;
			}

		}

		//back was pushed
		if(data->buttonsFlags[2]==1){

			return WINDOW_CHANGE_TO_MAIN;
		}



		if(data->buttonsFlags[3]==1){
				changeDoubleButton(data->widgets[3],0);
				changeDoubleButton(data->widgets[4],0);
			for(int w=0;w<5;w++){
				if(data->widgets[w]!=NULL){
					data->widgets[w]->destroyWidget(data->widgets[w]);
					data->widgets[w]=NULL; ////asd
				}

			}
			data->widgets=createSettingsWindowWidgets(data->windowRenderer,13);
			src->drawWindow(src);
			//return WINDOW_NONE;
		}
		//clicked on two player - first check
		if(data->buttonsFlags[4]==1){
				changeDoubleButton(data->widgets[3],1);
				changeDoubleButton(data->widgets[4],1);
//				for(int l=5;l<data->numOfWidgets;l++){
//					printf("line 853: L is %d\n", l);fflush(stdout);
//					if((l=9) ||(l=8) ||(l=7) ||(l==5) || (l==10)) //difficulty or color titles
//						changeDoubleButton(data->widgets[l],1);
//					else if((l=6) ||(l=11) ||(l=12))//easy moderate hard white black
//						changeDoubleButton(data->widgets[l],2);
//					}
			for(int t=5;t<data->numOfWidgets;t++){
				if(data->widgets[t]!=NULL){
					data->widgets[t]->destroyWidget(data->widgets[t]);
					data->widgets[t]=NULL;
				}

			}
			src->drawWindow(src);
//			printf("line 868 after draw window\n");fflush(stdout);
			//return WINDOW_NONE;
		}

		else{
			if(data->buttonsFlags[11]==1){
				changeDoubleButton(data->widgets[11],0);
				changeDoubleButton(data->widgets[12],0);
			}
			if(data->buttonsFlags[12]==1){
				changeDoubleButton(data->widgets[11],1);
				changeDoubleButton(data->widgets[12],1);
			}
			if(data->buttonsFlags[6]==1){
				changeDoubleButton(data->widgets[6],1);
				changeDoubleButton(data->widgets[7],1);
				changeDoubleButton(data->widgets[8],0);
				changeDoubleButton(data->widgets[9],0);
			}
			if(data->buttonsFlags[7]==1){
				changeDoubleButton(data->widgets[6],0);
				changeDoubleButton(data->widgets[7],0);
				changeDoubleButton(data->widgets[8],0);
				changeDoubleButton(data->widgets[9],0);
			}
			if(data->buttonsFlags[8]==1){
				changeDoubleButton(data->widgets[6],0);
				changeDoubleButton(data->widgets[7],1);
				changeDoubleButton(data->widgets[8],1);
				changeDoubleButton(data->widgets[9],0);
			}
			if(data->buttonsFlags[9]==1){
				changeDoubleButton(data->widgets[6],0);
				changeDoubleButton(data->widgets[7],1);
				changeDoubleButton(data->widgets[8],0);
				changeDoubleButton(data->widgets[9],1);
			}
			//return WINDOW_NONE;


		}

		return WINDOW_NONE;

	} //close the event type b.up
	else{
			return WINDOW_NONE;
	}
}



SP_WIN_MESSAGE handleEvenetMainWindow(SPWindow* src, SDL_Event* event){
	if(src == NULL || event==NULL){
		return WINDOW_INVALID;
	}
	SPSimpleWindow* data = (SPSimpleWindow*)src->data;
	int i =0;
	for(;i<data->numOfWidgets;i++){
		if(data->widgets[i]->handleEvent(data->widgets[i],event)
				== BUTTON_PUSHED)
			data->buttonsFlags[i]=1;

	}
	//newGame
	if(data->buttonsFlags[0]==1){
		return WINDOW_CHANGE_TO_SETTINGS;
	}
//	//loadGame
//	else
		if(data->buttonsFlags[1]==1){
		return WINDOW_CHANGE_TO_LOAD;
	}
	//game
	else if(data->buttonsFlags[2]==1){
		return WINDOW_QUIT;
	}
	else return WINDOW_NONE;

}
