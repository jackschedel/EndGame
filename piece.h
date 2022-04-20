#include <string>
#include <cctype>
#include <locale>
#include <vector>

class pieceMove;
class chessBoard;

#ifndef ENDGAME_PIECE_H
#define ENDGAME_PIECE_H


class piece {
private:
    std::string nameDefType[6] = {"pawn", "knight", "bishop", "rook", "queen", "king"};
    std::string nameDefColor[2] = {"white", "black"};

public:
    enum type {pawn, knight, bishop, rook, queen, king};
    enum color {white, black};

    type type;
    color color;

    piece(enum type type, enum color color);

    char pieceChar();

    std::vector<pieceMove>* generatePseudoLegalMoves(int position, chessBoard* board);

    void pseudoLegalPrint(int position, chessBoard* board, std::vector<pieceMove>* moveVector);

    std::string typeToString();

    std::string colorToString();
};


#endif //ENDGAME_PIECE_H
