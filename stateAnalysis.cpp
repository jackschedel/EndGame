#include "stateAnalysis.h"

#include "pieceMove.h"
#include "piece.h"


bool stateAnalysis::executeMove(pieceMove* move) {

    bool executeSuccess = board->prepareExecutePseudoLegal(move);

    if(!executeSuccess){
        return false;
    }



    chessBoard* tempBoard = board->tempCopy;


    chessBoard* tempBoard2 = board;


    board = tempBoard;


    //delete tempBoard2;

    return true;

}
