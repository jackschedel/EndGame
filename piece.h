#include <string>
#include <locale>

#ifndef ENDGAME_PIECE_H
#define ENDGAME_PIECE_H


class piece {
public:
    enum type {pawn, knight, bishop, rook, queen, king};
    enum color {white, black};

    type type;
    color color;

    bool specialMove = true;
    /*
     * for kings + rooks: specialMove is whether castle is allowed,
     * is set to false after moving
     * en passant + pawn double move will not be handled here.
     */

    piece(enum type type, enum type color);


};


#endif //ENDGAME_PIECE_H
