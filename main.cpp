#include <iostream>
#include <utility>

#include "stateAnalysis.h"
#include "GenerateFEN.h"
#include "chessBoard.h"
#include "pieceMove.h"
#include "piece.h"
#include "decisionTreeNode.h"


int main() {

    GenerateFEN fenGen("mate_in_lichess_db_puzzles.csv");

    std::pair<std::string, std::string> randomPuzzle = fenGen.randomFEN();

    std::cout << randomPuzzle.first << " " << randomPuzzle.second;


    stateAnalysis* state = new stateAnalysis();

    chessBoard board;
    board.boardInit(randomPuzzle.first);

    auto startingPosPair = board.givenStringParse(randomPuzzle.second);


    auto pseudoLegalMoves = board.genAllPseudoLegalMoves();

    pieceMove* move = nullptr;

    for (int i = 0; i < pseudoLegalMoves->size(); ++i) {


        if((*pseudoLegalMoves)[i].from == startingPosPair.first) {
            if ((*pseudoLegalMoves)[i].to == startingPosPair.second) {
                move = &(*pseudoLegalMoves)[i];
                break;
            }
        }
    }


    state->mainAnalysis(randomPuzzle.first, *move);




    /*
    chessBoard initBoard;

    initBoard.boardInit("3r2k1/4nppp/pq1p1b2/1p2P3/2r2P2/2P1NR2/PP1Q2BP/3R2K1 b - - 0 24");

    decisionTreeNode* decisionTree = new decisionTreeNode(initBoard);

    decisionTree->board.printBoard();

    std::cout << std::endl;

    auto PSMoveArr = decisionTree->board.genAllPseudoLegalMoves();

    decisionTree->board.pseudoLegalPrint(PSMoveArr);

    std::cout << std::endl;


    if(decisionTree->board.isInCheck(piece::white))
        std::cout << "white in check!"<< std::endl<< std::endl;

    if(decisionTree->board.isInCheck(piece::black))
        std::cout << "black in check!"<< std::endl<< std::endl;

    auto result = decisionTree->iterateOnce();

    std::cout << "psmove size: " << PSMoveArr->size() << std::endl;

    std::cout << "children size: " << decisionTree->children.size() << std::endl;


    chessBoard test;

    test.boardInit("3R2k1/4nppp/p4b2/1p2p3/2r2P2/2P1NR2/PP4BP/6K1 b - - 0 26");

    std::cout << test.isCheckmate();
*/

    /*
    std::vector<pieceMove>* PLmoves;

    PLmoves = state->board->pieceArr[34]->generatePseudoLegalMoves(34, state->board);




    pieceMove* move = &((*PLmoves)[1]);

    std::cout << std::endl << std::endl;

    bool executeSuccess = state->board->executeMove(move);

    if(!executeSuccess) {
        std::cout << "failed to execute move!" << std::endl;
    } else {


        state->board->printBoard();



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


    }


*/

}






