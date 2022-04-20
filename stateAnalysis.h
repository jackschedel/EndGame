#ifndef ENDGAME_STATEANALYSIS_H
#define ENDGAME_STATEANALYSIS_H

#include <vector>
class chessBoard;
class piece;
class pieceMove;

class stateAnalysis {

public:

    chessBoard* board = new chessBoard();

    bool executeMove(pieceMove* move);

};


#endif //ENDGAME_STATEANALYSIS_H
