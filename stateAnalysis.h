#include <vector>
#include <queue>

#include "chessBoard.h"

class piece;
class pieceMove;


#ifndef ENDGAME_STATEANALYSIS_H
#define ENDGAME_STATEANALYSIS_H





class stateAnalysis {

public:

    chessBoard* board = new chessBoard();

    stateAnalysis() = default;

};


#endif //ENDGAME_STATEANALYSIS_H
