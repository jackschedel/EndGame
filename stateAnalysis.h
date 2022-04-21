#include <vector>
#include <queue>
#include <utility>
#include <string>


#include "chessBoard.h"

class piece;
class pieceMove;


#ifndef ENDGAME_STATEANALYSIS_H
#define ENDGAME_STATEANALYSIS_H





class stateAnalysis {

public:

    chessBoard* board = new chessBoard();


    stateAnalysis() = default;

    void mainAnalysis(std::string fenCode, pieceMove startingMove);

};


#endif //ENDGAME_STATEANALYSIS_H
