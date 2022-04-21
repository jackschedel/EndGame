#include <string>
#include <utility>
#include "chessBoard.h"
class piece;



#ifndef ENDGAME_PIECEMOVE_H
#define ENDGAME_PIECEMOVE_H

class pieceMove {
private:
    std::string nameDefSpecialMove[6] = {"doublePawn", "enPassant", "queensideCastle", "kingsideCastle", "upgrade", "none"};
public:
    enum specialMove{doublePawn, enPassant, queensideCastle, kingsideCastle, upgrade, none};


    piece* piece;
    int from;
    int to;
    int capturing;

    enum piece::type upgradeType = piece::pawn;
    specialMove specialMove = none;

    pieceMove(class piece* piece, int from, int to,enum specialMove specialMove = none, int capturing = -1, enum piece::type upgradeType = piece::pawn) {

        this->piece = piece;
        this->from = from;
        this->to = to;
        this->capturing = capturing;
        this->specialMove = specialMove;
        if(specialMove == upgrade) {
            this->upgradeType = upgradeType;
        }

    };

    std::string positionToString(int position){

        std::string tempReturn;

        tempReturn += char((position % 8) + 65);

        tempReturn += ((position / 8) + 49);

        return tempReturn;

    };

    std::string moveToString(){


        if(specialMove == kingsideCastle && piece->color == piece::white)
            return "O-O";

        if(specialMove == kingsideCastle && piece->color == piece::black)
            return "o-o";

        if(specialMove == queensideCastle && piece->color == piece::white)
            return "O-O-O";

        if(specialMove == queensideCastle && piece->color == piece::black)
            return "o-o-o";

        return positionToString(from) + " " + positionToString(to);
    };



    void printMove(chessBoard* board);

    std::string specialMoveToString();

};


#endif //ENDGAME_PIECEMOVE_H
