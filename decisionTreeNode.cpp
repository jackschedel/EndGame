#include "decisionTreeNode.h"

#include "piece.h"
#include "pieceMove.h"

void decisionTreeNode::iterateOnce() {

    auto PLmoves = board.genAllPseudoLegalMoves();

    for (int i = 0; i < PLmoves->size(); ++i) {

        chessBoard temp = board;

        


    }

}
