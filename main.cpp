#include <iostream>
#include "chessBoard.h"
#include "stateAnalysis.h"


int main() {

    stateAnalysis stateAnalysis;

    //board.boardInit();
    //board.boardInit("rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1");
    //board.boardInit("rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR w KQkq c6 0 2");

    //board.boardInit("r2q1rk1/1bp1bppp/p1np1n2/1p2p3/3PP3/1BP2N1P/PP3PP1/RNBQR1K1 b - d3 0 10");

    //board.boardInit("8/8/4k3/8/8/1R6/8/4K3 w - - 0 1");

    stateAnalysis.board->boardInit("8/7k/N7/8/8/8/8/4K3 w - - 0 1");







    //board.boardInit("r3k2r/8/1qn1bn1b/pppppppp/PPPPPPPP/1QNBBN2/8/R3K2R w Qkq - 10 18");





    //board.boardInit("r3k2r/8/5p2/8/8/5P2/8/R3K2R w --kq - 1 1");


    /* bishop testing
    board.pieceArr[35] = new piece(piece::bishop, piece::white);

    board.pieceArr[21] = new piece(piece::pawn, piece::black);
     */

    /*
     * "r2q1rk1/1bp1bppp/p1np1n2/1p2p3/3PP3/1BP2N1P/PP3PP1/RNBQR1K1 b - d3 0 10"
     * advanced FEN with en passant for testing ^
     * should look like
     * https://cdn.discordapp.com/attachments/446426925209092098/965708877683363960/unknown.png
     * and it does
     */


    stateAnalysis.board->printBoard();



    std::cout << std::endl;


    if(stateAnalysis.board->isInCheck(piece::white))
        std::cout << "white in check!"<< std::endl<< std::endl;

    if(stateAnalysis.board->isInCheck(piece::black))
        std::cout << "black in check!"<< std::endl<< std::endl;



    for (int i = 0; i < 64; ++i) {
        if(stateAnalysis.board->pieceArr[i] != nullptr) {
            stateAnalysis.board->pieceArr[i]->pseudoLegalPrint(i, stateAnalysis.board);
            std::cout << std::endl;
        }
    }






}






