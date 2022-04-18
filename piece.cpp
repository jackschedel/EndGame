#include "piece.h"
#include "chessBoard.h"

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

    if(color == black){
        toReturn = std::tolower(toReturn);
    }

    return toReturn;

}

std::vector<pieceMove>* piece::generatePseudoLegalMoves(int position, chessBoard* board) {

    auto toReturn = new std::vector<pieceMove>;

    if(type == pawn) {

        if(color == white){

            // if still in rank 2 (can double move)
            if(position < 16) {
                if(board->pieceArr[position + 16] == nullptr)
                    toReturn->push_back(pieceMove(this, position, position + 16, pieceMove::doublePawn));
            }
            if(board->pieceArr[position + 8] == nullptr)
                toReturn->push_back(pieceMove(this, position, position + 8));

        } else {
            // if still in rank 7 (can double move)
            if(position > 47) {
                if(board->pieceArr[position - 16] == nullptr)
                    toReturn->push_back(pieceMove(this, position, position + 16, pieceMove::doublePawn));
            }
            if(board->pieceArr[position - 8] == nullptr)
                toReturn->push_back(pieceMove(this, position, position + 8));

        }
    }



    return toReturn;
}
