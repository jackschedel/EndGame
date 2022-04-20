#include "pieceMove.h"
#include "piece.h"
#include <iostream>
#include "chessBoard.h"

void pieceMove::printMove(chessBoard* board) {
    std::cout << board->positionToString(to) << " ";

    if(this->capturing != -1){
        std::cout << "capturing ";
    }

    if(this->specialMove != none){
        std::cout << specialMoveToString();
    }

    std::cout << std::endl;

}

std::string pieceMove::specialMoveToString() {
    return nameDefSpecialMove[specialMove];
}
