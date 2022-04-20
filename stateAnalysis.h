#include <vector>

#include "chessBoard.h"

class piece;
class pieceMove;


#ifndef ENDGAME_STATEANALYSIS_H
#define ENDGAME_STATEANALYSIS_H





class stateAnalysis {

public:

    chessBoard* board = new chessBoard();

    bool executeMove(pieceMove* move);

    stateAnalysis() = default;

};


#endif //ENDGAME_STATEANALYSIS_H
