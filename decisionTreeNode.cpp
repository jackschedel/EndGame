#include "decisionTreeNode.h"

#include "piece.h"
#include "pieceMove.h"

void decisionTreeNode::iterateOnce(bool playAsWhite) {

    int count = 0;

    auto PLmoves = board.genAllPseudoLegalMoves();

    for (int i = 0; i < PLmoves->size(); ++i) {

        chessBoard temp = board;


        if(temp.executeMove(&(*PLmoves)[i])) {
            auto tempNode = new decisionTreeNode(temp, this);

            tempNode->move = &(*PLmoves)[i];
            children.push_back(tempNode);
            count++;
        }

    }

}

void decisionTreeNode::iterateAll(int depth, bool playAsWhite, std::vector<decisionTreeNode*>* checkMates) {

    if(layerDeep > depth){
        return;
    }

    bool shouldContinue = true;

    if(playAsWhite && board.whiteToMove){
        if(board.isCheckmate()) {
            this->isMate = true;
            checkMates->push_back(this);
            return;
        }
    } else if (!playAsWhite && !board.whiteToMove){
        if(board.isCheckmate()) {
            this->isMate = true;
            checkMates->push_back(this);
            return;
        }

    }

    this->iterateOnce(playAsWhite);

    for (int i = 0; i < children.size(); ++i) {
        children[i]->iterateAll(depth, playAsWhite, checkMates);
    }

}



