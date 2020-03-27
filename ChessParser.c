# include <stdio.h>
# include "ChessParser.h"
# include <stdlib.h>
# include <string.h>
# include <ctype.h>
# include <assert.h>


void destroyCom(SPCommand* com){
	if(com==NULL){
		return;
	}
//	if(com->moovit!=NULL)
		destroyMove(com->moovit);
	if(com->path!=NULL)
		free(com->path);
	free(com);
	return ;
}


bool spParserIsInt(const char* str){
	for(unsigned int i=0; i<strlen(str)-1; ++i){
		if(!isdigit(str[i]))
			return false;
	}
	return true;
}

SPCommand* createCommand(){
	SPCommand* com=(SPCommand*)malloc(sizeof(SPCommand));
	coord* i_co=createCoord(0,0);
	com->moovit=createMove(i_co,i_co);
	destroyCoord(i_co);
	com->path=(char*)calloc(SP_MAX_LINE_LENGTH,sizeof(char));
	return com;
}

SPCommand* spHelperPPLSetting(const char* str){
	char c[SP_MAX_LINE_LENGTH];
	strcpy(c, str);
	const char *token;
	SPCommand* com=createCommand() ;
	token = strtok(c, " \t\r\n"); //copying only the command
	if (strcmp(token,"game_mode" ) == 0){
		com->cmd = SP_GAME_MODE;
		token = strtok(NULL, " \t\r\n");
		if(spParserIsInt(token)){
			com->arg= atoi(token);
			if ((com->arg==1) | (com->arg ==2)) com->validArg=true;
		}
		else if(com->validArg!=true) com->validArg=false;
	}
	else if (strcmp(token,"difficulty" ) == 0){
		com->cmd = SP_DIFFICULTY;
		token = strtok(NULL, " \t\r\n");
		if(spParserIsInt(token)){
			com->arg= atoi(token);
			if ((com->arg>0) && (com->arg <6)) com->validArg=true;
		}
		else if(com->validArg!=true) com->validArg=false;
	}
	else if (strcmp(token,"user_color" ) == 0){// the check if we are in vs.computer mode is not here.
		com->cmd = SP_USER_COLOR;
		token = strtok(NULL, " \t\r\n");
		if(spParserIsInt(token)){
			com->arg= atoi(token);
			if ((com->arg==1) || (com->arg ==0)) com->validArg=true;
		}
		else if(com->validArg!=true) com->validArg=false;
	}
	else if (strcmp(token,"load" ) == 0){
		com->cmd = SP_LOAD;
		token = strtok(NULL, " \t\r\n");
		if(token==NULL) com->cmd= SP_INVALID_LINE; // here we need to decide if we put invalid line or invalid argument.
		else {
			strcpy(com->path,token);
		}
		// we will need to check if the file exists in other function in the Chessgame module.
	}
	else if (strcmp(token,"default" ) == 0) com->cmd = SP_DEFAULT;
	else if (strcmp(token,"print_setting")== 0) com->cmd = SP_PRINT_SETTING;
	else if (strcmp(token,"quit" ) == 0) 	com->cmd = SP_QUIT;
	else if (strcmp(token,"start" ) == 0)	com->cmd = SP_START;
	else com->cmd=SP_INVALID_LINE;
	if((token = strtok(NULL, " \t\r\n"))!=NULL) com->cmd=SP_INVALID_LINE;
	return com;
}

SPCommand* spHelperPPLGame(const char* str){
	char c[SP_MAX_LINE_LENGTH];
	strcpy(c, str);
	const char *token;
	SPCommand* com=createCommand();
	token = strtok(c, " \t\r\n"); //copying only the command
	if 	(strcmp(token,"move" ) == 0){
		SPCommand* com2=spHelperPPLMove(str);

		destroyCom(com);
		return com2;
	}
	else if (strcmp(token,"get_moves" ) == 0)	com->cmd = SP_GET_MOVES;
	else if (strcmp(token,"save" ) == 0){
		com->cmd = SP_SAVE;
		token = strtok(NULL, " \t\r\n");
		if(token==NULL) com->cmd= SP_INVALID_LINE; // here we need to decide if we put invalid line or invalid argument.
		else {
			strcpy(com->path,token);
		}
	}
	else if (strcmp(token,"undo" ) == 0)	com->cmd = SP_UNDO_MOVE;
	else if (strcmp(token,"quit" ) == 0)		com->cmd = SP_QUIT;
	else if (strcmp(token,"reset" ) == 0)		com->cmd = SP_RESET;
	else	com->cmd=SP_INVALID_LINE;
	if((token = strtok(NULL, " \t\r\n"))!=NULL) com->cmd=SP_INVALID_LINE;
	return com;
}

SPCommand* spHelperPPLMove(const char* str){
	char c[SP_MAX_LINE_LENGTH];
	strcpy(c, str);
	const char *token;
	coord* temp1,*temp2;
	SPCommand* com=createCommand();
	token = strtok(c, " \t\r\n"); //copying only the command
	com->cmd=SP_MOVE;
	token = strtok(NULL, " \t\r\n");
	temp1=com->moovit->curr_coord;

	com->moovit->curr_coord=getCoordFromToken2(token);
	destroyCoord(temp1);
	if(isValidCoord(com->moovit->curr_coord)){
		token = strtok(NULL, " \t\r\n");
		if(strcmp(token, "to")==0){
			token = strtok(NULL, " \t\r\n");
			temp2=com->moovit->next_coord;
			com->moovit->next_coord=getCoordFromToken2(token);
			destroyCoord(temp2);
			if(isValidCoord(com->moovit->next_coord)){
				token = strtok(NULL, " \t\r\n");
				if(token==NULL){

					com->validArg=true;

					return com;
				}

			}
		}
	}
//	destroyMove(com->moovit);
//	com->moovit=NULL;
	com->validArg=false;
	return com;
}

bool isValidCoord(coord* coordinates){
	if(((coordinates->x)>0)&&((coordinates->y)>0)&&((coordinates->x)<9)&&((coordinates->y)<9))
		return true;
	else return false;
}

unsigned int getYCoordFromStr(const char* str){
	unsigned int y;
	if(strcmp(str,"A")==0) y=1;
	else if(strcmp(str,"B")==0) y=2;
	else if(strcmp(str,"C")==0) y=3;
	else if(strcmp(str,"D")==0) y=4;
	else if(strcmp(str,"E")==0) y=5;
	else if(strcmp(str,"F")==0) y=6;
	else if(strcmp(str,"G")==0) y=7;
	else if(strcmp(str,"H")==0) y=8;
	else y=0;
	return y;
}

SPCommand* spParserPraseLine(const char* str, int gameState){
	if(gameState) return spHelperPPLGame(str);
	else return spHelperPPLSetting(str);
}

coord* getCoordFromToken2(const char* str){
	coord* coordinates;
	char c[6];
	unsigned int i,j;
	coordinates= (coord*)malloc(sizeof(coord));
	strcpy(c,str);
	if(c[0]=='<'){
		i=c[1]-48;
		if((i>0)&&(i<9)){
			if(c[2]==','){
				j=c[3]-64;
				if((j>0)&&(j<9)){
					if(c[4]=='>'){
						if(c[5]=='\0'){
							coordinates->x=i;
							coordinates->y=j;
							return coordinates;
						}
					}
				}

			}
		}
	}
	coordinates->x=0;
	coordinates->y=0;
	return coordinates;
}



//int main(){
//	SPCommand com;
//	coord* co;
//	co=(coord*)malloc(sizeof(coord));
//	co=getCoordFromToken2("<3,C>");
//	printf("<%d,%d>\n", co->x,co->y);
//	com=spParserPraseLine("save abc",1);
////	printf("1. %d\n",com.cmd);
////	printf("2. %s\n", com.path);
//	com=spParserPraseLine("move <2,E> to <3,C>",1);
//	printf("1. com.cmd=%d\n",com.cmd);
//	printf("2. com.moovit:\n");
//	printf("3. source: <%d,%d>\n dest: <%d,%d>\n",com.moovit->curr_coord->x,com.moovit->curr_coord->y,com.moovit->next_coord->x,com.moovit->next_coord->y);
//	printf("4. com.validArg=%d",com.validArg);
//}



