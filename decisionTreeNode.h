#include <vector>
#include "chessBoard.h"
#include <utility>

class piece;
class pieceMove;

#ifndef ENDGAME_DECISIONTREE_H
#define ENDGAME_DECISIONTREE_H


class decisionTreeNode {

public:
    enum result{continuing, checkmate, stalemate};

    int layerDeep = 0;

    std::vector<decisionTreeNode*> children;

    decisionTreeNode* parent;

    bool isMate = false;

    pieceMove* move = nullptr;

    chessBoard board;

    decisionTreeNode(chessBoard givenBoard,  decisionTreeNode* givenParent = nullptr){
      board = givenBoard;
      parent = givenParent;
      if(parent != nullptr){
          layerDeep = parent->layerDeep + 1;
      }
    };

    void iterateOnce(bool playAsWhite);

    void iterateAll(int depth, bool playAsWhite, std::vector<decisionTreeNode*>* checkMates);





};


#endif //ENDGAME_DECISIONTREE_H
