#include "chessBoard.h"

void chessBoard::boardInit(std::string fenString) {

    int initState = 0;

    int currSquare = 0;

    char tempLower;

    int passantFile = -1;

    bool toPlace = false;

    auto currType = piece::rook;

    auto currColor = piece::white;

    piece* newPiece = nullptr;

    for (int i = 0; i < fenString.size(); ++i) {

        if(fenString[i] == ' ') {
            initState++;
            continue;
        }

        if(initState == 0) {

            tempLower = std::tolower(fenString[i]);

            toPlace = true;

            switch(tempLower) {
                case 'p':
                    currType = piece::pawn;
                    break;
                case 'n':
                    currType = piece::knight;
                    break;
                case 'b':
                    currType = piece::bishop;
                    break;
                case 'q':
                    currType = piece::queen;
                    break;
                case 'k':
                    currType = piece::king;
                    break;
                default:
                    toPlace = false;
            }

            if(toPlace) {

                if(tempLower == fenString[i]) {
                    currColor = piece::white;
                } else {
                    currColor = piece::black;
                }


                newPiece = new piece(currType, currColor);

                pieceArr[currSquare] = newPiece;

                currSquare++;
            } else if(fenString[i] != '/') {
                currSquare += (fenString[i] - 48);
            }

        } else if(initState == 1) {

            whiteToMove = (fenString[i] == 'w');
        } else if(initState == 2) {

            /*
             * 0: white queenside
             * 1: white kingside
             * 2: black queenside
             * 3: black kingside
             */

            switch(fenString[i]) {
                case 'q':
                    canCastle[0] = true;
                    break;
                case 'k':
                    canCastle[1] = true;
                    break;
                case 'Q':
                    canCastle[2] = true;
                    break;
                case 'K':
                    canCastle[3] = true;
            }

        } else if(initState == 3) {

            if(fenString[i] != '-' && passantFile == -1) {
                passantFile = (fenString[i] * 8);

            }else if(passantFile != -1) {
                enPassantTarget = passantFile + fenString[i] - 1;
            }

        }


    }



}

void chessBoard::printBoard() {
    for (int i = 7; i > -1; ++i) {

        for (int j = 0; j < 8; ++j) {
            if(j == 7){
                std::cout << std::endl;
            }

            if(pieceArr[(8 * i) + j] != nullptr) {

                std::cout << pieceArr[(8 * i) + j]->pieceChar();

            } else {
                std::cout << " ";

            }


        }




    }
}
