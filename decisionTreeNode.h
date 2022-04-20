#include <vector>
#include "chessBoard.h"

class piece;
class pieceMove;

#ifndef ENDGAME_DECISIONTREE_H
#define ENDGAME_DECISIONTREE_H


class decisionTreeNode {

public:
    enum result{continuing, checkmate, stalemate};


    std::vector<decisionTreeNode*> children;

    decisionTreeNode* parent;

    chessBoard board;

    decisionTreeNode(chessBoard givenBoard,  decisionTreeNode* givenParent = nullptr){
      board = givenBoard;
      parent = givenParent;
    };

    decisionTreeNode* iterateOnce();

    decisionTreeNode* iterateAll();

    decisionTreeNode* iterateAllAll();




};


#endif //ENDGAME_DECISIONTREE_H
