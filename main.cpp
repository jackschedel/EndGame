#include <iostream>
#include "chessBoard.h"

int main() {

    chessBoard board;

    //board.boardInit();
    //board.boardInit("rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1");
    //board.boardInit("rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR w KQkq c6 0 2");


    board.boardInit("r2q1rk1/1bp1bppp/p1np1n2/1p2p3/3PP3/1BP2N1P/PP3PP1/RNBQR1K1 b - d3 0 10");
    /*
     * "r2q1rk1/1bp1bppp/p1np1n2/1p2p3/3PP3/1BP2N1P/PP3PP1/RNBQR1K1 b - d3 0 10"
     * advanced FEN with en passant for testing ^
     * should look like
     * https://cdn.discordapp.com/attachments/446426925209092098/965708877683363960/unknown.png
     * and it does
     */


    board.printBoard();


    std::cout << std::endl;

    int tempPosition = board.stringToPosition("B1");


    board.pieceArr[tempPosition]->pseudoLegalPrint(tempPosition, &board);


}






