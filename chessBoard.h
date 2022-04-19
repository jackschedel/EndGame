#ifndef ENDGAME_CHESSBOARD_H
#define ENDGAME_CHESSBOARD_H

#include "piece.h"
#include <cctype>
#include <iostream>
#include <vector>

class chessBoard {
private:



public:
    bool whiteInCheck = false;

    bool blackInCheck = false;

    bool whiteToMove = true;

    bool canCastle[4] = {false};

    /*
     * 0: white queenside
     * 1: white kingside
     * 2: black queenside
     * 3: black kingside
     */

    int enPassantTarget = -1;

    int stringToPosition(std::string givenString);


    piece* pieceArr[64] {nullptr};

    void boardInit(std::string fenString = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

    void printBoard();

    std::string positionToString(int position);
};


#endif //ENDGAME_CHESSBOARD_H
