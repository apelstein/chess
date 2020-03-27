# include <stdio.h>
# include "ChessArrayList.h"
# include <stdlib.h>
# include <string.h>
# include <assert.h>

SPArrayList* spArrayListCreate(int maxSize){
	SPArrayList* list = (SPArrayList*) malloc(sizeof(SPArrayList));
	move* move1;
	coord* srcC, *destC;
	srcC=createCoord(0,0);
	destC=createCoord(0,0);
	move1=createMove(srcC,destC);
	if (maxSize <= 0)
		return NULL;
	else if (list==NULL){
		printf("Error: spArrayListCreate has failed");
		return NULL;
	}
	list->maxSize = maxSize;
	list->elements=(action**)malloc(maxSize*sizeof(action));
	if (list->elements == NULL)
		printf("Error: spArrayListCreate has failed");
	for (int i = 0 ; i<maxSize ; i++){
		(list->elements)[i] = createAction('\0', '\0', move1);
		if (list->elements[i] == NULL)
			printf("Error: spArrayListCreate has failed");
	}
	destroyCoord(srcC);
	destroyCoord(destC);
	destroyMove(move1);
	list->actualSize=0;
	return list;
}

void spArrayListCopyVoid(SPArrayList* src, SPArrayList* list){
	int flag1;
	list->actualSize = src->actualSize;
	list->maxSize = src->maxSize;
	for(int i=0; i<(src->actualSize);++i){
		flag1 = actionComparator(((src->elements)[i]), ((list->elements)[i]));
		if (flag1 == 0)
			printf("Could not copy actions in spArrayListCopy\n");fflush(stdout);
	}
}

SPArrayList* spArrayListCopy(SPArrayList* src){
	int flag1;
	SPArrayList* list = spArrayListCreate(undoListSize);
	if (src == NULL || list == NULL ){
		printf("Error: spArrayListCopy has failed\n");
		return NULL;
	}
	list->actualSize = src->actualSize;
	list->maxSize = src->maxSize;
	for(int i=0; i<(src->actualSize);++i){
		flag1 = actionComparator(((src->elements)[i]), ((list->elements)[i]));
		if (flag1 == 0)
			printf("Could not copy actions in spArrayListCopy\n");fflush(stdout);
	}
	return list;
}

void spArrayListDestroy(SPArrayList* src){
	if (src==NULL){
		return;
	}
	for (int i = 0 ; i < src->maxSize ; i++){
		destroyAction(src->elements[i]);
	}
	free(src->elements);
	free(src);
}

SP_ARRAY_LIST_MESSAGE spArrayListClear(SPArrayList* src){
	if(src==NULL)
		return SP_ARRAY_LIST_INVALID_ARGUMENT;
	spArrayListDestroy(src);
	src = spArrayListCreate(undoListSize);
	if (src == NULL)
		return SP_ARRAY_LIST_INVALID_ARGUMENT;
	return SP_ARRAY_LIST_SUCCESS;
}

SP_ARRAY_LIST_MESSAGE spArrayListAddAt(SPArrayList* src, action* elem, int index){
	if (src == NULL)
		return SP_ARRAY_LIST_INVALID_ARGUMENT;
	if (src->actualSize == src->maxSize)
		return SP_ARRAY_LIST_FULL;
	if (index > src->actualSize || index < 0)
		return SP_ARRAY_LIST_INVALID_ARGUMENT;

	for(int i=(src->actualSize); i>index;--i){
		actionComparator(((src->elements)[i-1]), ((src->elements)[i]));
	}
	actionComparator(elem, ((src->elements)[index]));
	src->actualSize++;
	return SP_ARRAY_LIST_SUCCESS;

}

SP_ARRAY_LIST_MESSAGE spArrayListAddFirst(SPArrayList* src, action* elem){
	return spArrayListAddAt(src,elem,0);
}

SP_ARRAY_LIST_MESSAGE spArrayListAddLast(SPArrayList* src, action* elem){
	if (src == NULL)
			return SP_ARRAY_LIST_INVALID_ARGUMENT;
	return spArrayListAddAt(src,elem,src->actualSize);
}

SP_ARRAY_LIST_MESSAGE spArrayListRemoveAt(SPArrayList* src, int index){
	if (src == NULL)
		return SP_ARRAY_LIST_INVALID_ARGUMENT;
	if (index > src->actualSize || index < 0)
		return SP_ARRAY_LIST_INVALID_ARGUMENT;
	if(src->actualSize==0)
		return SP_ARRAY_LIST_EMPTY;

	for(int i=index;i<(src->actualSize)-1;++i){
		actionComparator(((src->elements)[i+1]), ((src->elements)[i]));
	}
	src->actualSize=src->actualSize-1;
	return SP_ARRAY_LIST_SUCCESS;
}

SP_ARRAY_LIST_MESSAGE spArrayListRemoveFirst(SPArrayList* src){
	return spArrayListRemoveAt(src,0);
}

SP_ARRAY_LIST_MESSAGE spArrayListRemoveLast(SPArrayList* src){
	if (src == NULL)
		return SP_ARRAY_LIST_INVALID_ARGUMENT;
	if(src->actualSize==0)
		return SP_ARRAY_LIST_EMPTY;
	int index=(src->actualSize)-1;
	return spArrayListRemoveAt(src,index);
}

action* spArrayListGetAt(SPArrayList* src, int index){
	return ((src->elements)[index]);
}

action* spArrayListGetFirst(SPArrayList* src){
	return (src->elements[0]);
}

action* spArrayListGetLast(SPArrayList* src){
	return (src->elements[(src->actualSize)-1]);
}

int spArrayListMaxCapacity(SPArrayList* src){
	return src->maxSize;
}

int spArrayListSize(SPArrayList* src){
	return src->actualSize;
}

bool spArrayListIsFull(SPArrayList* src){
	if (src == NULL)
		return false;
	if (src->actualSize < src->maxSize)
		return false;
	return true;
}

bool spArrayListIsEmpty(SPArrayList* src){
	if (src == NULL)
		return false;
	if (src->actualSize>0)
		return false;
	return true;
}
