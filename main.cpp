#include <iostream>

#include "stateAnalysis.h"
#include "chessBoard.h"
#include "pieceMove.h"
#include "piece.h"


int main() {

    stateAnalysis* state = new stateAnalysis();

    //board.boardInit();
    //board.boardInit("rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1");
    //board.boardInit("rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR w KQkq c6 0 2");

    //board.boardInit("r2q1rk1/1bp1bppp/p1np1n2/1p2p3/3PP3/1BP2N1P/PP3PP1/RNBQR1K1 b - d3 0 10");

    //board.boardInit("8/8/4k3/8/8/1R6/8/4K3 w - - 0 1");

    state->board->boardInit("8/7k/N7/8/8/8/8/4K3 w - - 0 1");







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


    //state->board->printBoard();



    std::cout << std::endl;


    if(state->board->isInCheck(piece::white))
        std::cout << "white in check!"<< std::endl<< std::endl;

    if(state->board->isInCheck(piece::black))
        std::cout << "black in check!"<< std::endl<< std::endl;


    for (int i = 0; i < 64; ++i) {
        if(state->board->pieceArr[i] != nullptr) {

            std::vector<pieceMove>* PLmoves = state->board->pieceArr[i]->generatePseudoLegalMoves(i, state->board);

            state->board->pieceArr[i]->pseudoLegalPrint(i, state->board, PLmoves);
            std::cout << std::endl;
        }
    }

    std::vector<pieceMove>* PLmoves;

    for (int i = 0; i < 64; ++i) {
        if(state->board->pieceArr[i] != nullptr) {

            PLmoves = state->board->pieceArr[i]->generatePseudoLegalMoves(i, state->board);

            state->board->pieceArr[i]->pseudoLegalPrint(i, state->board, PLmoves);
            std::cout << std::endl;

            break;
        }
    }

    pieceMove* move = &((*PLmoves)[0]);



    bool executeSuccess = state->executeMove(move);

    if(!executeSuccess) {
        std::cout << "failed to execute move!" << std::endl;
    } else {


        state->board->printBoard();



        std::cout << std::endl;


        std::cout << state->board->pieceArr[0];


        if(state->board->isInCheck(piece::white))
            std::cout << "white in check!"<< std::endl<< std::endl;

        if(state->board->isInCheck(piece::black))
            std::cout << "black in check!"<< std::endl<< std::endl;


        for (int i = 0; i < 64; ++i) {
            if(state->board->pieceArr[i] != nullptr) {

                std::vector<pieceMove>* PLmoves = state->board->pieceArr[i]->generatePseudoLegalMoves(i, state->board);

                state->board->pieceArr[i]->pseudoLegalPrint(i, state->board, PLmoves);
                std::cout << std::endl;
            }
        }



    }





}






