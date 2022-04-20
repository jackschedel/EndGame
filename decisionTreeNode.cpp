#include "decisionTreeNode.h"

#include "piece.h"
#include "pieceMove.h"

decisionTreeNode* decisionTreeNode::iterateOnce() {

    auto PLmoves = board.genAllPseudoLegalMoves();

    for (int i = 0; i < PLmoves->size(); ++i) {

        chessBoard temp = board;


        if(temp.executeMove(&(*PLmoves)[i])) {
            auto tempNode = new decisionTreeNode(temp, this);
            children.push_back(tempNode);
        }

    }

    enum piece::color currMove = piece::black;

    if(board.whiteToMove){
        currMove = piece::white;
    }

    if(PLmoves->empty() && board.isInCheck(currMove)) {
        return parent;

    }

    return nullptr;

}

decisionTreeNode* decisionTreeNode::iterateAll() {

    for (int i = 0; i < children.size(); ++i) {
        auto mateParent = iterateOnce();

        if(mateParent != nullptr) {
            return mateParent;
        }
    }

    return nullptr;
}

decisionTreeNode* decisionTreeNode::iterateAllAll() {

    for (int i = 0; i < children.size(); ++i) {
        iterateAll();
    }

    return nullptr;
}

