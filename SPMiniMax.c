# include <stdio.h>
# include <stdlib.h>
# include "SPMiniMax.h"


int sp_MMSM_Helper(SPFiarGame* root, unsigned int maxDepth,int maximizing,  int alpha, int beta){
	move*  tempMove;
	int bestScore;

	coord* s_co, *d_co;

	if(ICheckyou(root)){
		if(!nextPlayerHasMoves(root)){
			if(root->currentPlayer==1) return (boardScore(root)-100);
			else return  (boardScore(root)+100);
		}
	}
	else{
		if(!nextPlayerHasMoves(root)){
			return boardScore(root);
		}
	}
	if(maxDepth==0){
		return boardScore(root);
	}

	else {			//(maxDepth>1)
		s_co= InvalidCoord();
		d_co=InvalidCoord();
		tempMove=createMove(s_co,d_co);
		if(maximizing){
			coordElem* movesList, *pointerToStart;
				bestScore=MIN;
//				printf("line 39 before the  AllPossibleMOves in Maximizing\n");fflush(stdout);
				movesList=pointerToStart=AllPossibleMoves(root, root->currentPlayer,1);
//				printf("line 41 the allPoss moves: \n");fflush(stdout);
//				PrintTheList(movesList);
				while(movesList!=NULL){
						moveComparatorFrom2Coord(movesList->sourceCoord,movesList->destinationCoord, tempMove);
						SPFiarMiniMaxNode* currentChild=createInternalNode(root);

						spFiarGameSetMove(currentChild->game,tempMove,0);
						currentChild->score=sp_MMSM_Helper(currentChild->game, maxDepth-1, currentChild->game->currentPlayer,alpha,beta );
						bestScore=FINDTHEX(bestScore,currentChild->score);
						destroyNode(currentChild);
						alpha=FINDTHEX(alpha,bestScore);
						movesList=movesList->next;
						if(beta<=alpha)
							break;

				}
				destroyCEList(pointerToStart);
				destroyMove(tempMove);
				destroyCoord(s_co);
				destroyCoord(d_co);
				return bestScore;
			}

			else{
				coordElem* movesList, *pointerToStart;
				bestScore=MAX;
//				printf("line 64 before the  AllPossibleMOves in Minimizing\n");fflush(stdout);
				movesList=pointerToStart=AllPossibleMoves(root, root->currentPlayer,1);
//				printf("line 66 the allPoss moves: \n");fflush(stdout);
//				PrintTheList(movesList);
				while(movesList!=NULL){
						moveComparatorFrom2Coord(movesList->sourceCoord,movesList->destinationCoord, tempMove);
						SPFiarMiniMaxNode* currentChild=createInternalNode(root);
						spFiarGameSetMove(currentChild->game,tempMove,0);
						currentChild->score=sp_MMSM_Helper(currentChild->game, maxDepth-1, currentChild->game->currentPlayer,alpha,beta );
						bestScore=FINDTHEN(bestScore,currentChild->score);
						destroyNode(currentChild);
						beta=FINDTHEN(alpha,bestScore);
						movesList=movesList->next;
						if(beta<=alpha)
							break;
				}
				destroyCEList(pointerToStart);
				destroyMove(tempMove);
				destroyCoord(s_co);
				destroyCoord(d_co);
				return bestScore;

			}
	}
}


move* spMinimaxSuggestMove(SPFiarGame* currentGame, unsigned int maxDepth){
	move* bestMove, *tempMove;
	int bestScore;
	coordElem* movesList, *pointerToStart;
	  //, * root;
//	int maximizing=0;
	coord* i_co=InvalidCoord();
	tempMove=createMove(i_co,i_co);
	bestMove=createMove(i_co,i_co);

	if(currentGame->currentPlayer) bestScore=MIN;
	else bestScore=MAX;
	if (currentGame == NULL || maxDepth <= 0)
		return NULL;
//	root=createInternalNode(currentGame);
//	if (root == NULL ){
//		spQuit(currentGame);
//	}
//	printf("line 98 before the 1st AllPossibleMOves\n");fflush(stdout);
	movesList=pointerToStart=AllPossibleMoves(currentGame,currentGame->currentPlayer,1);
//	printf("line 106 after the allPoss moves \n");fflush(stdout);
//	PrintTheList(movesList);
	while(movesList!=NULL){
		moveComparatorFrom2Coord(movesList->sourceCoord,movesList->destinationCoord, tempMove);
		SPFiarMiniMaxNode* currentChild=createInternalNode(currentGame);
		spFiarGameSetMove(currentChild->game,tempMove,0);
		currentChild->score=sp_MMSM_Helper(currentChild->game, maxDepth-1, currentChild->game->currentPlayer,MIN,MAX );
		if(currentGame->currentPlayer){
			if(bestScore<(currentChild->score)) {
				bestScore=currentChild->score;
				moveComparator(tempMove,bestMove);
			}

		}
		else{
			if(bestScore>(currentChild->score)){
				bestScore=currentChild->score;
				moveComparator(tempMove,bestMove);
			}

		}
//		printf("line 128 the move: \n");fflush(stdout);
//		PrintTheMove(bestMove);
		destroyNode(currentChild);
		movesList=movesList->next;


	}

//	printf("line 135\n");fflush(stdout);
	destroyCEList(pointerToStart);
	destroyMove(tempMove);
	destroyCoord(i_co);
//	destroyNode(root);
	return bestMove;
}
