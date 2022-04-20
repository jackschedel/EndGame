#include <cctype>
#include <iostream>
#include <vector>
#include <string>

#include "piece.h"


#ifndef ENDGAME_CHESSBOARD_H
#define ENDGAME_CHESSBOARD_H


class pieceMove;
class piece;


class chessBoard {
private:


public:
    chessBoard *tempCopy = nullptr;

    bool whiteInCheck = false;

    bool blackInCheck = false;

    bool whiteToMove = true;

    int whiteKingPos = -1;

    int blackKingPos = -1;

    bool canCastle[4] = {false};

    piece* pieceArr[64]{nullptr};


    /*
     * 0: white queenside
     * 1: white kingside
     * 2: black queenside
     * 3: black kingside
     */

    int enPassantTarget = -1;

    int stringToPosition(std::string givenString);

    bool isInCheck(enum piece::color colorToCheck, int position = -1);

    void boardInit(std::string fenString = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

    void printBoard();

    chessBoard() = default;

    std::string positionToString(int position);

    bool executeMove(pieceMove *move);

    std::vector<pieceMove>* genAllPseudoLegalMoves();

    void pseudoLegalPrint(std::vector<pieceMove>* PSMoveArr);


    };

#endif //ENDGAME_CHESSBOARD_H