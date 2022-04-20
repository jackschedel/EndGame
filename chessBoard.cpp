#include "chessBoard.h"

#include "pieceMove.h"
#include "piece.h"
#include "prettyprint.hpp"


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


bool chessBoard::executeMove(pieceMove* move) {

    enum piece::color tempColor = move->piece->color;


    auto revertArr = pieceArr;

    auto revertCastle = canCastle;

    auto revertWhiteK = whiteKingPos;

    auto revertBlackK = blackKingPos;


    if(move->specialMove == pieceMove::none || move->specialMove == pieceMove::enPassant || move->specialMove == pieceMove::doublePawn) {

        if(move->capturing != -1) {
            piece* toDelete = pieceArr[move->capturing];

            if(toDelete->type == piece::rook && toDelete->color == piece::black) {
                if (move->capturing == 56)
                    canCastle[2] = false;

                if (move->capturing == 63)
                    canCastle[3] = false;
            }

            if(toDelete->type == piece::rook && toDelete->color == piece::white) {
                if (move->capturing == 0)
                    canCastle[0] = false;

                if (move->capturing == 7)
                    canCastle[1] = false;
            }

            pieceArr[move->capturing] = nullptr;

            // delete toDelete;

        }

        if(move->piece->type == piece::rook && tempColor == piece::black) {
            if (move->capturing == 56)
                canCastle[2] = false;

            if (move->capturing == 63)
                canCastle[3] = false;
        }

        if(move->piece->type == piece::rook && tempColor == piece::white) {
            if (move->capturing == 0)
                canCastle[0] = false;

            if (move->capturing == 7)
                canCastle[1] = false;
        }

        if(move->piece->type == piece::king && tempColor == piece::black) {
            blackKingPos = move->to;
        }

        if(move->piece->type == piece::king && tempColor == piece::white) {
            whiteKingPos = move->to;
        }


        pieceArr[move->to] = move->piece;

        pieceArr[move->from] = nullptr;

    }

    if(move->specialMove == pieceMove::queensideCastle) {

        if(move->piece->color == piece::white) {

            if(!canCastle[0] || isInCheck(tempColor, 4) || isInCheck(tempColor, 3) || isInCheck(tempColor, 2))
                return false;

            pieceArr[3] = pieceArr[0];

            pieceArr[0] = nullptr;

            pieceArr[2] = pieceArr[4];

            pieceArr[4] = nullptr;

            whiteKingPos = 2;

            canCastle[0] = false;

        }else {

            if(!canCastle[2] || isInCheck(tempColor, 60) || isInCheck(tempColor, 59) || isInCheck(tempColor, 58))
                return false;

            pieceArr[59] = pieceArr[56];

            pieceArr[56] = nullptr;

            pieceArr[58] = pieceArr[60];

            pieceArr[60] = nullptr;

            whiteKingPos = 58;

            canCastle[2] = false;

        }

    }

    if(move->specialMove == pieceMove::kingsideCastle) {

        if(move->piece->color == piece::white) {

            if(!canCastle[1] || isInCheck(tempColor, 4) || isInCheck(tempColor, 5) || isInCheck(tempColor, 6))
                return false;

            pieceArr[5] = pieceArr[7];

            pieceArr[7] = nullptr;

            pieceArr[6] = pieceArr[4];

            pieceArr[4] = nullptr;

            whiteKingPos = 6;

            canCastle[1] = false;

        }else {

            if(!canCastle[3] || isInCheck(tempColor, 60) || isInCheck(tempColor, 61) || isInCheck(tempColor, 62))
                return false;

            pieceArr[61] = pieceArr[63];

            pieceArr[63] = nullptr;

            pieceArr[62] = pieceArr[60];

            pieceArr[60] = nullptr;

            blackKingPos = 62;

            canCastle[3] = false;

        }

    }


    if(move->specialMove == pieceMove::upgrade) {

        if(move->capturing != -1) {
            piece* toDelete = pieceArr[move->capturing];

            pieceArr[move->capturing] = nullptr;

            delete toDelete;

        }

        piece* toDelete2 = pieceArr[move->from];

        pieceArr[move->from] = nullptr;

        delete toDelete2;


        pieceArr[move->to] = new piece(move->upgradeType, tempColor);

    }


    if(isInCheck(tempColor)){

        for (int i = 0; i < 64; ++i) {
            pieceArr[i] = revertArr[i];
        }

        for (int i = 0; i < 4; ++i) {
            canCastle[i] = revertCastle[i];
        }

        whiteKingPos = revertWhiteK;

        blackKingPos = revertBlackK;


        return false;
    }


    whiteToMove = tempColor == piece::black;


    return true;
}

std::vector<pieceMove>* chessBoard::genAllPseudoLegalMoves() {

    auto PLmoves = new std::vector<pieceMove>;

    for (int i = 0; i < 64; ++i) {

        if(pieceArr[i] != nullptr) {
            if((whiteToMove && pieceArr[i]->color == piece::white)  ||  (!whiteToMove && pieceArr[i]->color == piece::black)){

                std::vector<pieceMove>* tempPLMoves = pieceArr[i]->generatePseudoLegalMoves(i, this);


                for (int j = 0; j < tempPLMoves->size(); ++j) {
                    PLmoves->push_back((*tempPLMoves)[j]);

                }


            }


        }
    }


    return PLmoves;
}


void chessBoard::pseudoLegalPrint(std::vector<pieceMove>* PSMoveArr) {


    for (int i = 0; i < PSMoveArr->size(); ++i) {



        std::cout << (*PSMoveArr)[i].piece->colorToString()  << " " << (*PSMoveArr)[i].piece->typeToString();
        std:: cout << " " << positionToString((*PSMoveArr)[i].from) << " to ";
        std:: cout << positionToString((*PSMoveArr)[i].to);

        std::string specialMove = (*PSMoveArr)[i].specialMoveToString();

        if((*PSMoveArr)[i].capturing != -1) {
            std:: cout << " capturing ";
        }

        if(specialMove != "none")
            std:: cout << " (" << specialMove << ") ";




        std::cout << std::endl;



    }



}



