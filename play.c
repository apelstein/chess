#include "play.h"

int checkhelper(SPFiarGame* game, int player){
	coordElem* MyRivalsList;
	int op=(player+1)%2, flag;
	coord* MyKingsCo=FindTheKing(game, player);
	//printf("Line 599, the king is: %c , the kings coords: \n",getPieceFromCoord(game,MyKingsCo));fflush(stdout);
	//PrintTheCoord(MyKingsCo);
	MyRivalsList= AllPossibleMoves(game,op,0);
	//printf("\nthe allPess. moves list is: \n");fflush(stdout);
	flag=isCoordInList(MyRivalsList,MyKingsCo);
//	printf("line 613 is the kings coord in the list: %d\n",flag);fflush(stdout);
	destroyCEList(MyRivalsList);
	destroyCoord(MyKingsCo);
	return flag;
}

//will happen after setMove- I mean that currentPlayer already has been changed//
int isMyKingThreatned(SPFiarGame* game){

	return checkhelper(game,(game->currentPlayer+1)%2);

}
int ICheckyou(SPFiarGame* game){

	return checkhelper(game,game->currentPlayer);

}

coordElem* AllPossibleMoves(SPFiarGame* game,int player, int checkForChecks){
	coordElem* result, *current, *temp;
	coord* co, *s_co,*d_co;
	s_co=InvalidCoord();
	d_co=InvalidCoord();
	current= result= createElem(s_co,d_co);
	for(int i=1; i<=SP_CHESS_GAME_N_ROWS;i++){
		for(int j=1;j<=SP_CHESS_GAME_N_ROWS;j++){
			if(game->gameBoard[i][j]!=emptyChar){
				// checking if this is our player.
				if((player && (isSmallCharacter(game->gameBoard[i][j])))
				||
				((!player)&&(isBigCharacter(game->gameBoard[i][j])))){
					co= createCoord(i,j);
					temp=PossibleMoves(game, co ,getPieceFromCoord(game, co),checkForChecks);
//					printf("Line 632 print the list after one iter of possmoves\n");fflush(stdout);
//					PrintTheList(temp);
					if(temp!=NULL){
						current->next= temp;
						current= findLastElem(current);
					}
					destroyCoord(co);
				}
			}
		}
	}
//	destroyCoord(co);
//	destroyCoord(s_co);
//	destroyCoord(d_co);
	current=result->next;
	PruningTheFirst(result);
	return current;

}

int notSelfCheck(SPFiarGame* game, coord* srcCoord, coord* destCoord, char srcPiece){
	int flag=0;
	char dest_piece=getPieceFromCoord(game,destCoord);
	move* move1= createMove(srcCoord,destCoord);
	spFiarGameSetMove(game,move1,1);
	flag=!(isMyKingThreatned(game));
	spFiarGameUndoNoLista(game,move1,srcPiece,dest_piece);
	destroyMove(move1);
	return flag;

}

int PrawnIsEating(SPFiarGame* game, char piece, coord* dest){
	if((isAKnifeInTheBack(game, piece, dest)==0)&& (getPieceFromCoord(game, dest)!=emptyChar))
		return 1;
	return 0;
}

int IAmTouchingMyPiece(SPFiarGame* game, coord* co){
	if((game->currentPlayer==0) && isBigCharacter(getPieceFromCoord(game,co)))
		return 1;
	if((game->currentPlayer==1) && isSmallCharacter(getPieceFromCoord(game,co)))
		return 1;
	return 0;

}

int didYouTouchMyPiece(SPFiarGame* game, coord* co){
	if((game->currentPlayer==0) && isBigCharacter(getPieceFromCoord(game,co)))
		return 0;
	if((game->currentPlayer==1) && isSmallCharacter(getPieceFromCoord(game,co)))
		return 0;
	return 1;
}

int isEmptyChar(SPFiarGame* game, coord* co){
	if(getPieceFromCoord(game,co)==emptyChar) return 1;
	return 0;
}

coordElem* PossibleMoves(SPFiarGame* game, coord* srcCoord, char srcPiece,int checkforcheck){
	coordElem* ce;
	if((srcPiece=='q')||(srcPiece=='Q'))
		ce=ValidDestCoordQueen(game,srcCoord,srcPiece,checkforcheck);
	else if((srcPiece=='k')||(srcPiece=='K'))
		ce=ValidDestCoordKing(game,srcCoord,srcPiece,checkforcheck);
	else if((srcPiece=='r')||(srcPiece=='R'))
			ce=ValidDestCoordRook(game,srcCoord,srcPiece,checkforcheck);
	else if((srcPiece=='b')||(srcPiece=='B'))
			ce=ValidDestCoordBishop(game,srcCoord,srcPiece,checkforcheck);
	else if((srcPiece=='n')||(srcPiece=='N'))
			ce=ValidDestCoordKinght(game,srcCoord,srcPiece,checkforcheck);
	else if((srcPiece=='m')||(srcPiece=='M')){
			ce=ValidDestCoordPrawn(game,srcCoord,srcPiece,checkforcheck);
	}
	else ce=createElemFrom2Ints(srcCoord, 0,0);

	return ce;
}

coord* FindTheKing(SPFiarGame* game, int player){
	coord* result;
	char king='k';
	if(!player) king='K';
	for(int i=1; i<=SP_CHESS_GAME_N_ROWS;i++){
		for(int j=1;j<=SP_CHESS_GAME_N_ROWS;j++){
			if(game->gameBoard[i][j]==king){
				result=createCoord(i,j);
			}
		}
	}
	return result;

}

int nextPlayerHasMoves(SPFiarGame* game){
	coordElem* ce=AllPossibleMoves(game,game->currentPlayer,1);//changed here yo 0
	if(ce==NULL){
		destroyCEList(ce);
		return 0;
	}
	else {
		destroyCEList(ce);
		return 1;
	}
}

coordElem* ValidDestCoordKinght(SPFiarGame* game, coord* srcCoord, char piece,int checkforcheck){
	coordElem* temp, *current, *result;
	coord *dest;
	//int i,j;
	dest=copyCoord(srcCoord);
	temp=current=result=createElemFromCopiedCoord(srcCoord, dest);
	//1 step
	temp=KnightCheck(game,srcCoord, dest,piece,2,-1,checkforcheck);
	if(temp!=NULL){
		current->next=temp;
		current=current->next;
	}
	//2 step
	temp=KnightCheck(game,srcCoord,dest,piece,-1,-1,checkforcheck);
	if(temp!=NULL){
		current->next=temp;
		current=current->next;
	}
	//3 step
	temp=KnightCheck(game,srcCoord,dest,piece,-2,0,checkforcheck);
	if(temp!=NULL){
		current->next=temp;
		current=current->next;
	}
	//4 step
	temp=KnightCheck(game,srcCoord,dest,piece,-1,1,checkforcheck);
	if(temp!=NULL){
		current->next=temp;
		current=current->next;
	}
	//5 step
	temp=KnightCheck(game,srcCoord,dest,piece,0,2,checkforcheck);
	if(temp!=NULL){
		current->next=temp;
		current=current->next;
	}
	//6 step
	temp=KnightCheck(game,srcCoord,dest,piece,1,1,checkforcheck);
	if(temp!=NULL){
		current->next=temp;
		current=current->next;
	}
	//7 step
	temp=KnightCheck(game,srcCoord,dest,piece,2,0,checkforcheck);
	if(temp!=NULL){
		current->next=temp;
		current=current->next;
	}
	//8 step
	temp=KnightCheck(game,srcCoord,dest,piece,1,-1,checkforcheck);
	if(temp!=NULL){
		current->next=temp;
		current=current->next;
	}

	destroyCoord(dest);
	current=result->next;
	PruningTheFirst(result);

	return current;

}

coordElem* KnightCheck(SPFiarGame* game,coord* src, coord* dest, char piece,  int i, int j,int checkforcheck){

	decreaseKey(dest,i,j);

	if(isValidCoord(dest)){
		if(!isAKnifeInTheBack(game,piece,dest)){
			if(checkforcheck){
				if(notSelfCheck(game,src,dest,piece)){
					return createElemFromCopiedCoord(src, dest);

				}
			}
			else{
				return createElemFromCopiedCoord(src, dest);

			}

		}
	}
	return NULL;
}



char getPieceFromCoord(SPFiarGame* game, coord* src){
	if(isValidCoord(src))
		return game->gameBoard[src->x][src->y];
	else{
		printf("bad arguments for getPieceFromCoord func. mainAux.c\n");fflush(stdout);
		return 'F';
	}
}






coordElem* ValidDestCoordStopMeIfYouCan(SPFiarGame* game, coord* srcCoord, char piece, int x_dir, int y_dir,int checkforcheck){
	coordElem* current, *result;
	int flagNSC;
	coord* dest;
	dest=copyCoord(srcCoord);
	current=result=createElemFromCopiedCoord(srcCoord,dest);
	decreaseKey(dest,x_dir,y_dir);
	while(isValidCoord(dest)){
//		printf("line 233,the srcCoord, the validCoord: ");fflush(stdout);PrintTheCoord(srcCoord);PrintTheCoord(dest);printf("\n");fflush(stdout);
		if(!isAKnifeInTheBack(game,piece,dest)){
//			printf("LINE 234 knife in the back is ok\n");fflush(stdout);
//			printf("line 236 checkForCheck =%d\n",checkforcheck);fflush(stdout);
			if(checkforcheck){
//				printf("line 237 start calculating the notselfcheck\n");fflush(stdout);
				flagNSC=notSelfCheck(game,srcCoord,dest,piece);
//				printf("LINE 239 flagNSC=%d.\n",flagNSC);fflush(stdout);
				if(flagNSC){
					current->next=createElemFromCopiedCoord(srcCoord,dest);
					current=current->next;
					if(getPieceFromCoord(game,dest)!=emptyChar)
						break;
					decreaseKey(dest,x_dir,y_dir);
				}
				else{
					break;
				}
			}
			else{
				//printf("LINE 242 we suppose to be here if-else checkforcheck\n");fflush(stdout);
				current->next=createElemFromCopiedCoord(srcCoord,dest);
				current=current->next;
				if(getPieceFromCoord(game,dest)!=emptyChar)
					break;
				decreaseKey(dest,x_dir,y_dir);
			}

		}
		else {
			break;
		}



	}
	destroyCoord(dest);
	//printf("LINE 259 finished the while loop\n");fflush(stdout);
	current= result->next;
//	printf("Line 265, printing the last element\n");fflush(stdout);
//	PrintThecoordfromElement(findLastElem(current));
	PruningTheFirst(result);
//	PrintTheList(current);
	return current;
}

coordElem* ValidDestCoordBishop(SPFiarGame* game, coord* srcCoord, char piece,int checkforcheck){
	int x_dir[4];
	int y_dir[4];
	x_dir[0]=x_dir[1]=1; x_dir[2]=x_dir[3]=-1;
	y_dir[0]=y_dir[2]=1; y_dir[1]=y_dir[3]=-1;
	return ValidDestCoordBRHelper(game, srcCoord,piece,x_dir, y_dir,checkforcheck);
}

coordElem* ValidDestCoordRook(SPFiarGame* game, coord* srcCoord, char piece,int checkforcheck){
	int x_dir[4];
	int y_dir[4];
	x_dir[0]=1; x_dir[1]=0; x_dir[2]=-1; x_dir[3]=0;
	y_dir[0]=0; y_dir[1]=1; y_dir[2]=0; y_dir[3]=-1;
	return ValidDestCoordBRHelper(game, srcCoord,piece,x_dir, y_dir, checkforcheck);
}

coordElem* ValidDestCoordQueen(SPFiarGame* game, coord* srcCoord, char piece,int checkforcheck){
	coordElem* result, *current,*temp;
	current=result=createElemFromCopiedCoord(srcCoord,srcCoord);
	//printf("Line 273 enter the vdqueen\n");fflush(stdout);
	temp=ValidDestCoordBishop(game,srcCoord,piece,checkforcheck);
	if(temp!=NULL){
		current->next=temp;
		current=findLastElem(current);
	}
	//printf("Line 279, after the bishop\nthe list is: \n");fflush(stdout);
//	PrintTheList(result->next);
	temp=ValidDestCoordRook(game, srcCoord,piece, checkforcheck);
	if(temp!=NULL){
		current->next=temp;
		current=findLastElem(current);
	}
	//printf("Line 298, after the rook\nthe list is: \n");fflush(stdout);

	current=result->next;
	//PrintTheList(current);
	PruningTheFirst(result);
	return current;

}

coordElem* ValidDestCoordBRHelper(SPFiarGame* game, coord* srcCoord, char piece,int * x_dir, int* y_dir,int checkforcheck){
	coordElem* result, *current,*temp;
	result=createElem(InvalidCoord(),InvalidCoord());
	temp=current=result;
	//printf("Line 299, entered the BRhelper\n");fflush(stdout);
	for(int i=0;i<4;i++){
		//printf("Line 301, loop no. %d\n",i);fflush(stdout);
		//printf("Line 302, x[%d],y[%d]=%d,%d.\n",i,i,x_dir[i],y_dir[i]);fflush(stdout);
		temp=ValidDestCoordStopMeIfYouCan(game,srcCoord,piece,x_dir[i],y_dir[i], checkforcheck);
		//printf("line 316 out from stopme and back to helper\n");fflush(stdout);
		current->next=temp;
		if(temp!=NULL)	{
			current=findLastElem(current);
		}
	//	printf("the list after loop no. %d", i);fflush(stdout);
//		PrintTheList(result->next);

	}

	current=result->next;
	PruningTheFirst(result);
//	printf("Line 312 before return in BRhelper");fflush(stdout);
	return current;
}

int checkValidCastling(int dir,SPFiarGame* game, coord* srcCoord, char piece,int checkforcheck){
	coord* dest=copyCoord(srcCoord);
	unsigned int x_k=1;
	char king=piece;
	char rook='r';
	if(piece=='K'){
		x_k=8;
		rook='R';

	}

	decreaseKey(dest,0,dir);
	if((srcCoord->x==x_k)&&(srcCoord->y==5)&&(piece==king)){
		if(dir==2){
			if(		(game->gameBoard[x_k][6]==emptyChar)&&
					(game->gameBoard[x_k][7]==emptyChar)&&
					(game->gameBoard[x_k][8]==rook)){
				if(checkforcheck){
					if(notSelfCheck(game,srcCoord,dest,piece)){
						destroyCoord(dest);
						return 1;
					}

				}
				else{
					destroyCoord(dest);
					return 1;
				}
			}
		}
		else{

			if(		(game->gameBoard[x_k][4]==emptyChar)&&
					(game->gameBoard[x_k][3]==emptyChar)&&
					(game->gameBoard[x_k][2]==emptyChar)&&
					(game->gameBoard[x_k][1]==rook)){
				if(checkforcheck){
					if(notSelfCheck(game,srcCoord,dest,piece)){
						destroyCoord(dest);
						return 1;
					}

				}
				else{
					destroyCoord(dest);
					return 1;
				}
			}
		}


	}
	destroyCoord(dest);
	return 0;

}

coordElem* ValidDestCoordKing(SPFiarGame* game, coord* srcCoord, char piece,int checkforcheck){
	coordElem* result, *current;
	coord *dest;
	//int i,j;
	dest=copyCoord(srcCoord);
	current=result=createElemFromCopiedCoord(srcCoord,dest);
	for(int i=-1;i<=1;i++){
		for(int j=-1;j<=1;j++){
			decreaseKey(dest,i,j);
			if(!((i==0)&&(j==0))){
				if(isValidCoord(dest)){
					if(!isAKnifeInTheBack(game,piece,dest)){
						if(checkforcheck){
							if(notSelfCheck(game,srcCoord,dest,piece)){
								current->next=createElemFromCopiedCoord(srcCoord, dest);
								current=current->next;
							}

						}
						else{
							current->next=createElemFromCopiedCoord(srcCoord, dest);
							current=current->next;
						}

					}
				}
			}
			decreaseKey(dest,-i,-j);
		}
	}
	//check white and right
	if((piece=='k')&&(game->castlingWhite[0]==0)&&(game->castlingWhite[1]==0)&&(game->castlingWhite[3]!=-1)){

		if(checkValidCastling(2,game,srcCoord,piece,checkforcheck)){
			coord* co1=createCoord(1,7);
			current->next=createElemFromCopiedCoord(srcCoord,co1 );
			destroyCoord(co1);
			current=current->next;
		}

	}

	//check white and Left
	if((piece=='k')&&(game->castlingWhite[0]==0)&&(game->castlingWhite[2]==0)&&(game->castlingWhite[4]!=-1)){
		if(checkValidCastling(-2,game,srcCoord,piece,checkforcheck)){
			coord* co2=createCoord(1,3);
			current->next=createElemFromCopiedCoord(srcCoord, co2);
			destroyCoord(co2);
			current=current->next;
		}

	}

	//black and right
	if((piece=='K')&&(game->castlingBlack[0]==0)&&(game->castlingBlack[1]==0)&&(game->castlingBlack[3]!=-1)){
		if(checkValidCastling(2,game,srcCoord,piece,checkforcheck)){
			coord* co3=createCoord(1,3);
			current->next=createElemFromCopiedCoord(srcCoord, co3);
			destroyCoord(co3);
			current=current->next;
		}

	}
	//check white and Left
	if((piece=='K')&&(game->castlingBlack[0]==0)&&(game->castlingBlack[2]==0)&&(game->castlingBlack[4]!=-1)){
		if(checkValidCastling(-2,game,srcCoord,piece,checkforcheck)){
			coord* co4=createCoord(8,3);
			current->next=createElemFromCopiedCoord(srcCoord, co4);
			destroyCoord(co4);
			current=current->next;
		}

	}
	destroyCoord(dest);
	current=result->next;
	PruningTheFirst(result);

	return current;
}

int isAKnifeInTheBack(SPFiarGame* game, char srcPiece, coord* dest){
	char destPiece;
	destPiece=getPieceFromCoord(game,dest);
	if(isSmallCharacter(srcPiece) && isSmallCharacter(destPiece))
		return 1;
	else if(isBigCharacter(srcPiece)&& isBigCharacter(destPiece))
		return 1;
	else return 0;
}

int isSmallCharacter(char c){
	if((c>96)&&(c<123)) return 1;
	else return 0;
}

int isBigCharacter(char c){
	if((c>64)&&(c<91)) return 1;
	else return 0;
}

coordElem* ValidDestCoordPrawn(SPFiarGame* game, coord* srcCoord, char piece,int checkforcheck){
	//white is up, black is down

	if(piece=='m') return ValidDestCoordPrawnHelper(game,srcCoord,piece,1,checkforcheck);
	else return ValidDestCoordPrawnHelper(game,srcCoord,piece,-1,checkforcheck);
}

coordElem* ValidDestCoordPrawnHelper(SPFiarGame* game, coord* srcCoord, char piece, int direction,int checkforcheck){
	coord* dest;
	coordElem* current, *result;
	dest=copyCoord(srcCoord);
	current=result=createElemFromCopiedCoord(srcCoord,dest);
	int firstForwardIsEmpty=1;
	//1 step forward/
	decreaseKey(dest,direction,0);

	if(isValidCoord(dest)){
		if(isEmptyChar(game,dest)){
			if(checkforcheck){
				if(notSelfCheck(game,srcCoord,dest,piece)){
					current->next=createElemFromCopiedCoord(srcCoord, dest);
					current=current->next;

				}
			}
			else{
				current->next=createElemFromCopiedCoord(srcCoord, dest);
				current=current->next;
			}


		}
		else{
			firstForwardIsEmpty=0;
		}
	}

	// eating right and forward
	decreaseKey(dest,0, direction);
	if(isValidCoord(dest)){
		if(PrawnIsEating(game,piece,dest)){

			if(checkforcheck){
				if(notSelfCheck(game,srcCoord,dest,piece)){
					current->next=createElemFromCopiedCoord(srcCoord, dest);
					current=current->next;
				}
			}
			else{
				current->next=createElemFromCopiedCoord(srcCoord, dest);
				current=current->next;

			}
		}
	}


	// eating left and forward
	decreaseKey(dest,0, (-2*direction));
	if(isValidCoord(dest)){
			if(PrawnIsEating(game,piece,dest)){

				if(checkforcheck){
					if(notSelfCheck(game,srcCoord,dest,piece)){
						current->next=createElemFromCopiedCoord(srcCoord, dest);
						current=current->next;
					}
				}
				else{
					current->next=createElemFromCopiedCoord(srcCoord, dest);
					current=current->next;
				}
			}
	}

	if(firstForwardIsEmpty){
		//returning back to 1 step forward
		decreaseKey(dest,0,direction);
		// 2 steps forward
		if(((direction==1)&&(srcCoord->x==2))||((direction==-1)&&(srcCoord->x==7))){
			decreaseKey(dest,direction,0);
			if(isEmptyChar(game,dest)){
				if(checkforcheck){
					if(notSelfCheck(game,srcCoord,dest,piece)){
						current->next=createElemFromCopiedCoord(srcCoord, dest);
						current=current->next;
					}
				}
				else{
					current->next=createElemFromCopiedCoord(srcCoord, dest);
					current=current->next;
				}

			}
		}
	}

	destroyCoord(dest);
	current=result->next;
	PruningTheFirst(result);

	return current;
}


