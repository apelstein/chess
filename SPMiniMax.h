#ifndef SPMINIMAX_H_
#define SPMINIMAX_H_
#include "SPMiniMaxNode.h"


/**
 * Given a game state, this function evaluates the best move according to
 * the current player. The function initiates a MiniMax algorithm up to a
 * specified length given by maxDepth. The current game state doesn't change
 * by this function including the history of previous moves.
 *
 * @param currentGame - The current game state
 * @param maxDepth - The maximum depth of the miniMax algorithm
 * @return
 * -1 if either currentGame is NULL or maxDepth <= 0.
 * On success the function returns a number between [0,SP_FIAR_GAME_N_COLUMNS -1]
 * which is the best move for the current player.
 */
move* spMinimaxSuggestMove(SPFiarGame* currentGame,	unsigned int maxDepth);

/**
 * helper function for the SPminimaxsuggestmove function
 * this function yields recursively the minimax tree, and performs the calculations of the tree depths.
 * MMSM stands for Mini Max Suggest Move.
 * @param
 * root - the node on which the calculations are performed.
 * maxdepth - The maximum depth of the miniMax algorithm.
 * turn - indicates whose turn is it.
 * depthOfTree - a global pointer that holds the maxdepth.
 * @return
 * the maximum/minimum score of a node's children if the recursion isn't in the last call
 * the index of the column the best move for the current player if  the recursion is in the last call.
 */
int sp_MMSM_Helper(SPFiarGame* root, unsigned int maxDepth,int maximizing,  int alpha, int beta);


#endif
