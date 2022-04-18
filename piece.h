#include <string>
#include <cctype>
#include <locale>

#ifndef ENDGAME_PIECE_H
#define ENDGAME_PIECE_H


class piece {
public:
    enum type {pawn, knight, bishop, rook, queen, king};
    enum color {white, black};

    type type;
    color color;

    piece(enum type type, enum color color);

    char pieceChar();


};


#endif //ENDGAME_PIECE_H
