#include "stateAnalysis.h"

#include "pieceMove.h"
#include "piece.h"
#include "decisionTreeNode.h"

void stateAnalysis::mainAnalysis(std::string fenCode, pieceMove startingMove) {

    chessBoard initBoard;

    auto checkMates = new std::vector<decisionTreeNode*>;

    initBoard.boardInit(fenCode);

    decisionTreeNode* decisionTree = new decisionTreeNode(initBoard);

    decisionTree->board.executeMove(&startingMove);

    decisionTree->board.printBoard();

    std::cout << std::endl;

    decisionTree->iterateAll(4, board->whiteToMove, checkMates);


    for (int i = 0; i < checkMates->size(); ++i) {
        decisionTreeNode* tempRoot = (*checkMates)[i];

        while(tempRoot != nullptr){


            if(tempRoot->move != nullptr)
                std::cout << tempRoot->move->moveToString() << std::endl;

            tempRoot = tempRoot->parent;

        }

        std::cout << std::endl << std::endl;

    }

    std::cout << "done";


}
