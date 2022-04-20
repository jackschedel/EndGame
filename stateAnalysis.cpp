#include "stateAnalysis.h"
#include "chessBoard.h"
#include "pieceMove.h"
#include "piece.h"


bool stateAnalysis::executeMove(pieceMove* move) {

    bool executeSuccess = board->prepareExecutePseudoLegal(move);

    if(!executeSuccess){
        return false;
    }



    chessBoard* tempBoard = board->tempCopy;

    delete board;

    board = tempBoard;

    return true;



}
