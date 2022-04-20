#include <vector>
#include "chessBoard.h"

class piece;
class pieceMove;

#ifndef ENDGAME_DECISIONTREE_H
#define ENDGAME_DECISIONTREE_H


class decisionTreeNode {

public:

    std::vector<decisionTreeNode*> children;

    decisionTreeNode* parent;

    chessBoard board;

    decisionTreeNode(chessBoard* givenBoard,  decisionTreeNode* givenParent = nullptr){
      board = *givenBoard;
      parent = givenParent;
    };

    void iterateOnce();




};


#endif //ENDGAME_DECISIONTREE_H
