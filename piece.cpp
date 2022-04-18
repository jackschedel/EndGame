#include "piece.h"

piece::piece(enum type type, enum color color){
    this->type = type;
    this->color = color;
}

char piece::pieceChar() {

    char toReturn;

    switch(type) {
        case pawn:
            toReturn = 'P';
            break;
        case knight:
            toReturn = 'N';
            break;
        case bishop:
            toReturn = 'B';
            break;
        case rook:
            toReturn = 'R';
            break;
        case queen:
            toReturn = 'Q';
            break;
        case king:
            toReturn = 'K';
    }

    if(color == white){
        toReturn = std::tolower(toReturn);
    }

    return toReturn;

}
