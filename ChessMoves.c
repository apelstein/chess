# include <stdio.h>
# include "ChessMoves.h"
# include <stdlib.h>
# include <assert.h>

int coordEquals(coord* coord1, coord* coord2){
	if ((coord1->x != coord2->x) || (coord1->y != coord2->y))
		return 0;
	return 1;
}

coord* createCoord(int x, int y){
	coord* coordinate = (coord*) malloc(sizeof(coord));
	 if (coordinate==NULL){
			printf("Error: createCoord has failed");
			return NULL;
		}
	coordinate->x = x;
	coordinate->y = y;
	return coordinate;
}

move* createMove(coord* curr_coord, coord* next_coord){
	int flag1;
	int flag2;
	move* move1 = (move*) malloc(sizeof(move));
	if (move1==NULL){
			printf("Error: createMove has failed");
			return NULL;
		}
	move1->curr_coord= createCoord(0,0);
	if (move1->curr_coord==NULL){
			printf("Error: createMove has failed");
			destroyMove(move1);
			return NULL;
		}
	move1->next_coord= createCoord(0,0);
	if (move1->next_coord==NULL){
			printf("Error: createMove has failed");
			destroyMove(move1);
			return NULL;
		}

	 flag1 = coordComparator(curr_coord, move1->curr_coord);

	 flag2 = coordComparator(next_coord, move1->next_coord);
	 if (flag1==0){
		 printf("line 48\n");fflush(stdout);
		 destroyMove(move1);
		 return NULL;
	 }

	 if (flag2==0){
		 printf("line 48\n");fflush(stdout);
		 destroyMove(move1);
		 return NULL;
	 }

	return move1;
}

action* createAction(char curr_piece, char next_piece, move* moovit){
	int flag1;
	action* act = (action*) malloc(sizeof(action));
	 if (act==NULL){
			printf("Error: createAction has failed");
			return NULL;
		}
	act->curr_piece = curr_piece;
	act->next_piece = next_piece;
	act->moovit=(move*)malloc(sizeof(move));
	if (act->moovit == NULL){
			printf("Error: createAction has failed");
			return NULL;
	}
	act->moovit->curr_coord=(coord*)malloc(sizeof(coord));
	if (act->moovit->curr_coord == NULL){
			printf("Error: createAction has failed");
			return NULL;
	}
	act->moovit->next_coord=(coord*)malloc(sizeof(coord));
	if (act->moovit->next_coord == NULL){
			printf("Error: createAction has failed");
			return NULL;
	}
	flag1 = moveComparator(moovit, act->moovit);
	 if (flag1==0)
		 return NULL;
	return act;
}
int destroyCoord(coord* src){
	if (src == NULL)
		return 0;
	free(src);
	return 1;
}

int destroyMove(move* src){
	int flag1;
	int flag2;
	if (src == NULL)
		return 0;
	flag1 = destroyCoord(src->curr_coord);

	flag2 = destroyCoord(src->next_coord);
	free(src);
	if (flag2==0)
		 return 0;
	 if (flag1==0)
		 return 0;

	return 1;
}

int destroyAction (action* src){
	int flag1;
	if (src == 0)
		return 0;
	flag1 = destroyMove(src->moovit);
	 if (flag1==0)
		 return 0;
	free(src);
	return 1;
}

int actionComparator (action* src, action* target){
	int flag1;
	if ((src == NULL) || (target == NULL))
		return 0;
	target->curr_piece = src->curr_piece;
	target->next_piece = src->next_piece;
	flag1 = moveComparator(src->moovit,target->moovit);
	 if (flag1==0)
		 return 0;
	return 1;
}

int moveComparator(move* src, move* target){
	int flag1;
	int flag2;
	if ((src == NULL) || (target == NULL))
		return 0;
	flag1 = coordComparator(src->curr_coord,target->curr_coord);

	flag2 = coordComparator(src->next_coord,target->next_coord);
	 if (flag1==0)
		 return 0;
	if (flag2==0)
		 return 0;
	return 1;
}

coord* copyCoord(coord* src){

	int i,j;
	if(src==NULL) return NULL;
	i=src->x;
	j=src->y;
	return createCoord(i,j);
}

int coordComparator(coord* src, coord* target){
	if ((src == NULL) || (target == NULL))
		return 0;
	target->x = src->x;
	target->y = src->y;
	return 1;
}

int moveComparatorFrom2Coord(coord* src ,coord* dest, move* targetMove){
	int flag1, flag2;
	flag1=coordComparator(src,targetMove->curr_coord);

	flag2= coordComparator(dest, targetMove->next_coord);
	if (flag1==0)
			 return 0;
	if (flag2==0)
			 return 0;
	return 1;
}

coordElem* createElem(coord* srcCoordinates, coord* destCoordinates){
	coordElem* src;
	if((srcCoordinates==NULL)||(destCoordinates==NULL)){
		printf("ERROR: NULL arguments\n");
		return NULL;
	}
	src=(coordElem*) malloc(sizeof(coordElem));
	if(mallocError(src,"src")==0) return NULL;
	src->sourceCoord=srcCoordinates;
	src->destinationCoord=destCoordinates;
	src->next=NULL;
	return src;
}

int mallocError(void* pointer, char* msg){
	if(pointer==NULL){
		printf("ERROR: %s malloc went wrong!\n",msg);
		return 0;
	}
	else return 1;
}

void destroyCEList(coordElem* src){
	coordElem* temp;
	if(src!=NULL){
		temp=src->next;
		freeOneCE(src);
		destroyCEList(temp);


	}

}

void freeOneCE(coordElem* src){
	destroyCoord(src->sourceCoord);
	destroyCoord(src->destinationCoord);
	src->next=NULL;
	free(src);
}

void PrintTheList(coordElem* ce){
	if(ce!=NULL){
		PrintThecoordfromElement(ce);
		PrintTheList(ce->next);


	}
}

void PrintThecoordfromElement(coordElem* ce){
	if(ce==NULL) {printf("NULL list\n");fflush(stdout);}
	else{
		printf("srcCoord: ");fflush(stdout);
		PrintTheCoord(ce->sourceCoord);
		printf("destCoord: ");fflush(stdout);
		PrintTheCoord(ce->destinationCoord);
		printf("\n");fflush(stdout);

	}
}

void PrintTheCoord(coord* crd){
	printf("<%d,%d> ", crd->x,crd->y);fflush(stdout);
}

void PrintTheMove(move* m){
	printf("the move: \n");fflush(stdout);
	printf("the srcC= ");fflush(stdout);PrintTheCoord(m->curr_coord);
	printf("the dstC= ");fflush(stdout);PrintTheCoord(m->next_coord);
	printf("\n");fflush(stdout);
}

coordElem* createElemFrom2Ints(coord* srcCoordinates, int x,int y){
	return createElem(copyCoord(srcCoordinates), createCoord(x,y));
}

coordElem* createElemFromCopiedCoord(coord* srcCoordinates, coord* destCoordinates){
	coord* s_co, *d_co;
	s_co=copyCoord(srcCoordinates);
	d_co=copyCoord(destCoordinates);
	return createElem(s_co,d_co);
}

coordElem* addElements(coordElem* src, coordElem* new){
	coordElem* last;
	if((src==NULL) || (new==NULL)) {
		printf("ERROR: NULL arguments\n");
		return NULL;
	}
	last=(coordElem*)malloc(sizeof(coordElem));
	if(mallocError(last,"last")==0) return NULL;
	last=findLastElem(src);
	last->next=new;
	return src;

}

coordElem* findLastElem(coordElem* src){
	coordElem* current;
	if((src==NULL)) {
		printf("ERROR: NULL arguments\n");
		return NULL;
	}
	current=src;
	while(current->next!=NULL) {
		current=current->next;
	}
	return current;
}

void PruningTheFirst(coordElem* ce){
	destroyCoord(ce->sourceCoord);
	destroyCoord(ce->destinationCoord);
	ce->next=NULL;
	free(ce);
}

int isCoordInList(coordElem* src, coord* point){

	if((point==NULL)) {
		printf("ERROR: NULL arguments func: isCoordinList func.\n");fflush(stdout);
		return 0;
	}

	if(src==NULL) return 0;

	while((src)!=NULL){
		if(coordEquals(src->destinationCoord,point)) return 1;
		src=src->next;
	}
	return 0;

}

void decreaseKey(coord* src, int x_addition, int y_addition){
	if(src==NULL){
		printf("NULL coords for decreaseKey func.\n");fflush(stdout);
		return;
	}
//	printf("before dkey: %d,%d\n",src->x,src->y);
	src->x+=x_addition;
	src->y+=y_addition;
//	printf("after dkey: %d,%d\n",src->x,src->y);
}



coord* InvalidCoord(){
	return createCoord(0,0);
}
