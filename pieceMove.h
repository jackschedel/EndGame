class piece;

#ifndef ENDGAME_PIECEMOVE_H
#define ENDGAME_PIECEMOVE_H

class pieceMove {
private:
    std::string nameDefSpecialMove[6] = {"doublePawn", "enPassant", "queensideCastle", "kingsideCastle", "upgrade", "none"};
    std::string nameDefUpgradeType[5] = {"na", "knight", "bishop", "rook", "queen"};
public:
    enum specialMove{doublePawn, enPassant, queensideCastle, kingsideCastle, upgrade, none};

    enum upgradeType{na, knight, bishop, rook, queen};

    piece* piece;
    int from;
    int to;
    int capturing;

    upgradeType upgradeType = na;
    specialMove specialMove;

    pieceMove(class piece* piece, int from, int to,enum specialMove specialMove = none, int capturing = -1, enum upgradeType upgradeType = na) {

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

    std::string upgradeTypeToString();
};


#endif //ENDGAME_PIECEMOVE_H
