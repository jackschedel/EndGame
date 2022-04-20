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

    void printMove(chessBoard* board);

    std::string specialMoveToString();

};


#endif //ENDGAME_PIECEMOVE_H
