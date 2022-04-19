#include "chessBoard.h"

void chessBoard::boardInit(std::string fenString) {

    int initState = 0;

    int currSquare = 56;

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
                case 'r':
                    currType = piece::rook;
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
                    currColor = piece::black;
                } else {
                    currColor = piece::white;
                }


                newPiece = new piece(currType, currColor);

                pieceArr[currSquare] = newPiece;

                currSquare++;
            } else if(fenString[i] != '/') {
                currSquare += (fenString[i] - 48);
            } else {
                currSquare -= 16;
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
                passantFile = fenString[i] - 97;

            }else if(passantFile != -1) {
                /*
                std::cout << passantFile << std::endl;
                std::cout << (fenString[i] - 49) * 8 << std::endl;
                 */

                enPassantTarget = passantFile + (fenString[i] - 49) * 8;
            }

        }


    }


}

void chessBoard::printBoard() {


    for (int i = 7; i >= 0; --i) {

        for (int j = 0; j < 8; ++j) {
            if (j == 0) {
                std::cout << std::endl;
            }

            if (pieceArr[(8 * i) + j] != nullptr) {

                std::cout << pieceArr[(8 * i) + j]->pieceChar();

            } else {
                std::cout << "-";

            }

            std::cout << " ";
        }



    }

    std::cout  << std::endl  << std::endl << "to move: ";

    if (whiteToMove) {
        std::cout << "white" << std::endl;
    } else {
        std::cout << "black" << std::endl;
    }


    std::cout << "en passant target: ";

    if(enPassantTarget == -1) {
        std::cout << "none" << std::endl;
    } else {

        std::cout << enPassantTarget << std::endl;

    }

    std::cout << "castles available: " << std::endl;

    if(canCastle[0])
        std::cout << "  - white queenside" << std::endl;

    if(canCastle[1])
        std::cout << "  - white kingside" << std::endl;

    if(canCastle[2])
        std::cout << "  - black queenside" << std::endl;

    if(canCastle[3])
        std::cout << "  - black kingside" << std::endl;


}

int chessBoard::stringToPosition(std::string givenString) {

    char rank = std::tolower(givenString[0]);

    char file = givenString[1];

    rank -= 97;

    return 8 * (file - 49) + rank;
}

std::string chessBoard::positionToString(int position){

    std::string tempReturn;

    tempReturn += char((position % 8) + 65);

    tempReturn += ((position / 8) + 49);

    return tempReturn;

}

