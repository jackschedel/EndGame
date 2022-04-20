#include "chessBoard.h"
#include "pieceMove.h"
#include "piece.h"


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


                if(currType == piece::king) {

                    if(currColor == piece::black){
                        blackKingPos = currSquare;
                    }else {
                        whiteKingPos = currSquare;
                    }

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
                    canCastle[2] = true;
                    break;
                case 'k':
                    canCastle[3] = true;
                    break;
                case 'Q':
                    canCastle[0] = true;
                    break;
                case 'K':
                    canCastle[1] = true;
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


    // TODO: run check for whether side is in check

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

bool chessBoard::isInCheck(enum piece::color colorToCheck, int position) {

    if(position == -1) {

        if (colorToCheck == piece::white) {
            position = whiteKingPos;
        } else {
            position = blackKingPos;
        }
    }



    // knight check
    int newPosition = 0;

    if( (position % 8) > 0 && (position / 8)  > 1) {

        newPosition = position - 17;

        if (newPosition >= 0 && newPosition < 64) {

            if (pieceArr[newPosition] != nullptr)
                if (pieceArr[newPosition]->color != colorToCheck && pieceArr[newPosition]->type == piece::knight)
                    return true;


        }
    }

    if( (position % 8) < 7 && (position / 8)  > 1) {
        newPosition = position - 15;
        if (newPosition >= 0 && newPosition < 64) {
            if (pieceArr[newPosition] != nullptr)
                if (pieceArr[newPosition]->color != colorToCheck && pieceArr[newPosition]->type == piece::knight)
                    return true;


        }
    }

    if( (position % 8) > 1 && (position / 8)  > 0) {
        newPosition = position - 10;
        if (newPosition >= 0 && newPosition < 64) {

            if (pieceArr[newPosition] != nullptr)
                if (pieceArr[newPosition]->color != colorToCheck && pieceArr[newPosition]->type == piece::knight)
                    return true;

        }
    }

    if( (position % 8) < 6 && (position / 8)  > 0) {
        newPosition = position - 6;
        if (newPosition >= 0 && newPosition < 64) {

            if (pieceArr[newPosition] != nullptr)
                if (pieceArr[newPosition]->color != colorToCheck && pieceArr[newPosition]->type == piece::knight)
                    return true;

        }
    }

    if( (position % 8) > 1 && (position / 8)  < 7) {
        newPosition = position + 6;
        if (position >= 0 && position < 64) {

            if (pieceArr[newPosition] != nullptr)
                if (pieceArr[newPosition]->color != colorToCheck && pieceArr[newPosition]->type == piece::knight)
                    return true;

        }
    }

    if( (position % 8) < 6 && (position / 8)  < 7) {
        newPosition = position + 10;
        if (position >= 0 && position < 64) {


            if (pieceArr[newPosition] != nullptr)
                if (pieceArr[newPosition]->color != colorToCheck && pieceArr[newPosition]->type == piece::knight)
                    return true;

        }
    }

    if( (position % 8) > 0 && (position / 8)  < 6) {
        newPosition = position + 15;
        if (position >= 0 && position < 64) {
            if (pieceArr[newPosition] != nullptr)
                if (pieceArr[newPosition]->color != colorToCheck && pieceArr[newPosition]->type == piece::knight)
                    return true;

        }
    }

    if( (position % 8) < 7 && (position / 8)  < 6 ){
        newPosition = position + 17;
        if (position >= 0 && position < 64) {
            if (pieceArr[newPosition] != nullptr)
                if (pieceArr[newPosition]->color != colorToCheck && pieceArr[newPosition]->type == piece::knight)
                    return true;

        }
    }



    // pawn check
    if(colorToCheck == piece::white) {

        // +7 and +9
        if(position / 8 < 7) {

            // pawn to right, +9
            if(position % 8 != 7) {

                newPosition = position + 9;

                if(pieceArr[newPosition] != nullptr && pieceArr[newPosition]->color != colorToCheck && pieceArr[newPosition]->type == piece::pawn){
                    return true;
                }

            }

            // pawn to left, +7
            if(position % 8 != 0) {

                newPosition = position + 7;

                if(pieceArr[newPosition] != nullptr && pieceArr[newPosition]->color != colorToCheck && pieceArr[newPosition]->type == piece::pawn){
                    return true;
                }

            }

        }

    } else {

        // -7 and -9
        if(position / 8 > 0) {

            // pawn to right, -7
            if(position % 8 != 7) {

                newPosition = position - 7;

                if(pieceArr[newPosition] != nullptr && pieceArr[newPosition]->color != colorToCheck && pieceArr[newPosition]->type == piece::pawn){
                    return true;
                }

            }

            // pawn to left, -9
            if(position % 8 != 0) {
                newPosition = position - 9;

                if(pieceArr[newPosition] != nullptr && pieceArr[newPosition]->color != colorToCheck && pieceArr[newPosition]->type == piece::pawn){
                    return true;
                }

            }
        }
    }



    // bishop + queen diag check
    int tempPosition = position;
    int tempPosition2 = position;

    tempPosition -= 9;
    // down left
    while (tempPosition >= 0 && tempPosition < 64) {
        if( (tempPosition2 % 8) > 0 && (tempPosition2 / 8)  > 0) {

            if (pieceArr[tempPosition] != nullptr) {
                if (pieceArr[tempPosition]->color != colorToCheck) {
                    if (pieceArr[tempPosition]->type == piece::bishop || pieceArr[tempPosition]->type == piece::queen) {
                        return true;
                    }
                } else {
                    break;
                }
            }

            tempPosition -= 9;
            tempPosition2 -= 9;
        }else{
            break;
        }
    }

    tempPosition2 = position;
    tempPosition = position;
    tempPosition -= 7;
    // down right
    while (tempPosition >= 0 && tempPosition < 64) {
        if( (tempPosition2 % 8) < 7 && (tempPosition2 / 8)  > 0) {

            if (pieceArr[tempPosition] != nullptr) {
                if (pieceArr[tempPosition]->color != colorToCheck) {
                    if (pieceArr[tempPosition]->type == piece::bishop || pieceArr[tempPosition]->type == piece::queen) {
                        return true;
                    }
                } else {
                    break;
                }
            }

            tempPosition -= 7;
            tempPosition2 -= 7;
        }else{
            break;
        }
    }

    tempPosition2 = position;
    tempPosition = position;
    tempPosition += 7;
    // up left
    while (tempPosition >= 0 && tempPosition < 64) {
        if( (tempPosition2 % 8) > 0 && (tempPosition2 / 8)  < 7) {

            if (pieceArr[tempPosition] != nullptr) {
                if (pieceArr[tempPosition]->color != colorToCheck) {
                    if (pieceArr[tempPosition]->type == piece::bishop || pieceArr[tempPosition]->type == piece::queen) {
                        return true;
                    }
                } else {
                    break;
                }
            }

            tempPosition += 7;
            tempPosition2 += 7;
        }else{
            break;
        }
    }

    tempPosition2 = position;
    tempPosition = position;
    tempPosition += 9;
    // up right
    while (tempPosition >= 0 && tempPosition < 64) {
        if( (tempPosition2 % 8) < 7 && (tempPosition2 / 8)  < 7) {

            if (pieceArr[tempPosition] != nullptr) {
                if (pieceArr[tempPosition]->color != colorToCheck) {
                    if (pieceArr[tempPosition]->type == piece::bishop || pieceArr[tempPosition]->type == piece::queen) {

                        return true;
                    }
                } else {
                    break;
                }
            }

            tempPosition += 9;
            tempPosition2 += 9;
        }else{
            break;
        }
    }



    // rook + queen rank/file check

    tempPosition = position;
    tempPosition--;
    // left
    while(tempPosition % 8 != 7 && tempPosition >= 0 && tempPosition < 64) {

        if (pieceArr[tempPosition] != nullptr) {
            if (pieceArr[tempPosition]->color != colorToCheck) {
                if (pieceArr[tempPosition]->type == piece::rook || pieceArr[tempPosition]->type == piece::queen) {

                    return true;
                }
            } else {
                break;
            }
        }

        tempPosition--;
    }

    tempPosition = position;
    tempPosition++;
    // right
    while(tempPosition % 8 != 0 && tempPosition >= 0 && tempPosition < 64) {

        if (pieceArr[tempPosition] != nullptr) {
            if (pieceArr[tempPosition]->color != colorToCheck) {
                if (pieceArr[tempPosition]->type == piece::rook || pieceArr[tempPosition]->type == piece::queen) {

                    return true;
                }
            } else {
                break;
            }
        }

        tempPosition++;
    }

    tempPosition = position;
    tempPosition += 8;
    // up
    while(tempPosition >= 0 && tempPosition < 64) {

        if (pieceArr[tempPosition] != nullptr) {
            if (pieceArr[tempPosition]->color != colorToCheck) {
                if (pieceArr[tempPosition]->type == piece::rook || pieceArr[tempPosition]->type == piece::queen) {

                    return true;
                }
            } else {
                break;
            }
        }


        tempPosition += 8;
    }

    tempPosition = position;
    tempPosition -= 8;
    // down
    while(tempPosition >= 0 && tempPosition < 64) {

        if (pieceArr[tempPosition] != nullptr) {
            if (pieceArr[tempPosition]->color != colorToCheck) {
                if (pieceArr[tempPosition]->type == piece::rook || pieceArr[tempPosition]->type == piece::queen) {

                    return true;
                }
            } else {
                break;
            }
        }

        tempPosition -= 8;
    }


    return false;
}

bool chessBoard::prepareExecutePseudoLegal(pieceMove* move) {

    enum piece::color tempColor = move->piece->color;

    chessBoard tempBoardCopy = *this;

    chessBoard* tempBoard = &tempBoardCopy;

    if(move->specialMove == pieceMove::none || move->specialMove == pieceMove::enPassant || move->specialMove == pieceMove::doublePawn) {

        if(move->capturing != -1) {
            piece* toDelete = tempBoard->pieceArr[move->capturing];

            if(toDelete->type == piece::rook && toDelete->color == piece::black) {
                if (move->capturing == 56)
                    tempBoard->canCastle[2] = false;

                if (move->capturing == 63)
                    tempBoard->canCastle[3] = false;
            }

            if(toDelete->type == piece::rook && toDelete->color == piece::white) {
                if (move->capturing == 0)
                    tempBoard->canCastle[0] = false;

                if (move->capturing == 7)
                    tempBoard->canCastle[1] = false;
            }

            tempBoard->pieceArr[move->capturing] = nullptr;

            delete toDelete;

        }

        tempBoard->pieceArr[move->to] = move->piece;

        tempBoard->pieceArr[move->from] = nullptr;

    }

    if(move->specialMove == pieceMove::queensideCastle) {

        if(move->piece->color == piece::white) {

            if(tempBoard->isInCheck(tempColor, 4) || tempBoard->isInCheck(tempColor, 3) || tempBoard->isInCheck(tempColor, 2))
                return false;

            tempBoard->pieceArr[3] = tempBoard->pieceArr[0];

            tempBoard->pieceArr[0] = nullptr;

            tempBoard->pieceArr[2] = tempBoard->pieceArr[4];

            tempBoard->pieceArr[4] = nullptr;

            whiteKingPos = 2;

        }else {

            if(tempBoard->isInCheck(tempColor, 60) || tempBoard->isInCheck(tempColor, 59) || tempBoard->isInCheck(tempColor, 58))
                return false;

            tempBoard->pieceArr[59] = tempBoard->pieceArr[56];

            tempBoard->pieceArr[56] = nullptr;

            tempBoard->pieceArr[58] = tempBoard->pieceArr[60];

            tempBoard->pieceArr[60] = nullptr;

            whiteKingPos = 58;

        }

    }

    if(move->specialMove == pieceMove::kingsideCastle) {

        if(move->piece->color == piece::white) {

            if(tempBoard->isInCheck(tempColor, 4) || tempBoard->isInCheck(tempColor, 5) || tempBoard->isInCheck(tempColor, 6))
                return false;

            tempBoard->pieceArr[5] = tempBoard->pieceArr[7];

            tempBoard->pieceArr[7] = nullptr;

            tempBoard->pieceArr[6] = tempBoard->pieceArr[4];

            tempBoard->pieceArr[4] = nullptr;

            whiteKingPos = 6;

        }else {

            if(tempBoard->isInCheck(tempColor, 60) || tempBoard->isInCheck(tempColor, 61) || tempBoard->isInCheck(tempColor, 62))
                return false;

            tempBoard->pieceArr[61] = tempBoard->pieceArr[63];

            tempBoard->pieceArr[63] = nullptr;

            tempBoard->pieceArr[62] = tempBoard->pieceArr[60];

            tempBoard->pieceArr[60] = nullptr;

            blackKingPos = 62;

        }

    }


    if(move->specialMove == pieceMove::upgrade) {

        if(move->capturing != -1) {
            piece* toDelete = tempBoard->pieceArr[move->capturing];

            tempBoard->pieceArr[move->capturing] = nullptr;

            delete toDelete;

        }

        piece* toDelete2 = tempBoard->pieceArr[move->from];

        tempBoard->pieceArr[move->from] = nullptr;

        delete toDelete2;


        tempBoard->pieceArr[move->to] = new piece(move->upgradeType, tempColor);

    }


    if(tempBoard->isInCheck(tempColor)){
        return false;
    } else {

        tempCopy = tempBoard;

    }

    return true;
}


