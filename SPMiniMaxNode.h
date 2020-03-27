#ifndef SPMINIMAXNODE_H_
#define SPMINIMAXNODE_H_
#include <stdbool.h>
#include "play.h"

typedef struct sp_fiar_minimaxNode {
	SPFiarGame* game;
	int score;
} SPFiarMiniMaxNode;

/**
 * creates internal node in the minimax tree
 * @param currentGame - the source game
 * @return
 * a new internal node with the following fields: game - the node's gameboard, children - the 7 (optional) children of the node, score - the score of the gameboard
 */
SPFiarMiniMaxNode* createInternalNode(SPFiarGame* currentGame);

/**
 * computes a specific cell score (1 or -1)
 * @param p layer - represents the player's symbol in the cell
 * @return
 * 1 if the symbol in the cell is the player's symbol
 * -1 if the symbol in the cell is the other player's symbol
 * 0 otherwise
 */
int scoringCell (char player);
/**
 * helper function for the nodeScore function
 * computes the score among all the horizontal options in the gameboard.
 * @param
 * src - the source game
 * histogram - a histogram that 	contains how many times each score between -4 and 4 appeared.
 */
void scoreHorizontal(SPFiarGame* src, int histogram[]);
/**
 * helper function for the nodeScore function
 * computes the score among all the verical options in the gameboard.
 * @param
 * src - the source game
 * histogram - a histogram that 	contains how many times each score between -4 and 4 appeared.
 */
void scoreVertical(SPFiarGame* src, int histogram[]);
/**
 * helper function for the nodeScore function
 * computes the score among all the right and down diagonal options in the gameboard.
 * @param
 * src - the source game
 * histogram - a histogram that 	contains how many times each score between -4 and 4 appeared.
 */
void scoreRightAndDown(SPFiarGame* src, int histogram[]);
/**
 * helper function for the nodeScore function
 * computes the score among all the right and up diagonal options in the gameboard.
 * @param
 * src - the source game
 * histogram - a histogram that 	contains how many times each score between -4 and 4 appeared.
 */
void scoreRightAndUp(SPFiarGame* src, int histogram[]);
/**
 * computes a node's score.
 * @param src - the source game
 */
int nodeScore(SPFiarMiniMaxNode* src);
/**
 * Frees all memory resources associated with the source minimax-node. If the
 * source node is NULL, then the function does nothing.
 * @param src - the source node.
 */
void destroyNode(SPFiarMiniMaxNode* node);

#endif
