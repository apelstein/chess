# include <stdio.h>
# include "SPMiniMaxNode.h"
# include <stdlib.h>
# include <string.h>
# include <assert.h>
# define MIN -1000000000
# define MAX 1000000000


SPFiarMiniMaxNode* createInternalNode(SPFiarGame* currentGame){
	SPFiarMiniMaxNode* node= (SPFiarMiniMaxNode*) malloc(sizeof(SPFiarMiniMaxNode));

	if (node == NULL){
		printf("Error: createInternalNode has failed");
		return NULL;
	}
	node->game=(SPFiarGame*) malloc(sizeof(SPFiarGame));
	mallocError(node->game,"Error: malloc has failed func createInternalNode");
	node->game->lista=NULL;
	node->game->castlingBlack=(int *)calloc(5,sizeof(int));
	node->game->castlingWhite=(int *)calloc(5,sizeof(int));
	spFiarGameCopy(currentGame,node->game);
	return node;
}

void destroyNode(SPFiarMiniMaxNode* node){
	if(node==NULL){
		return;
	}
	spFiarGameDestroy(node->game);
	free(node);
}
