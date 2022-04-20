#include "piece.h"
#include "chessBoard.h"
#include "pieceMove.cpp"



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


/*

         if( (position % 8) > 1 && (position / 8)  > 0) {


 */

std::vector<pieceMove>* piece::generatePseudoLegalMoves(int position, chessBoard* board) {

    auto toReturn = new std::vector<pieceMove>;

    if(type == pawn) {

        if(color == white){
            // white
            // if still in rank 2 (can double move)
            if(position < 16) {
                if(board->pieceArr[position + 16] == nullptr && board->pieceArr[position + 8] == nullptr)
                    toReturn->push_back(pieceMove(this, position, position + 16, pieceMove::doublePawn));
            }
            // if in ranks 2-6 (normal move)
            if(position < 48 && board->pieceArr[position + 8] == nullptr)
                toReturn->push_back(pieceMove(this, position, position + 8));

            // if in rank 7 (upgrade)
            if(position > 47 && board->pieceArr[position + 8] == nullptr){
                toReturn->push_back(pieceMove(this, position, position + 8, pieceMove::upgrade, -1, piece::knight));
                toReturn->push_back(pieceMove(this, position, position + 8, pieceMove::upgrade, -1, piece::bishop));
                toReturn->push_back(pieceMove(this, position, position + 8, pieceMove::upgrade, -1, piece::rook));
                toReturn->push_back(pieceMove(this, position, position + 8, pieceMove::upgrade, -1, piece::queen));

            }

            // capturing for all but last row
            if(position % 8 != 0) {
                if (board->pieceArr[position + 7] != nullptr)
                    if (position < 48 && board->pieceArr[position + 7]->color == black)
                        toReturn->push_back(pieceMove(this, position, position + 7, pieceMove::none, position + 7));
            }

            if(position % 8 != 7) {
                if (board->pieceArr[position + 9] != nullptr)
                    if (position < 48 && board->pieceArr[position + 9]->color == black)
                        toReturn->push_back(pieceMove(this, position, position + 9, pieceMove::none, position + 9));
            }

            // capturing + upgrading
            if(position % 8 != 0) {
                if (board->pieceArr[position + 7] != nullptr) {
                    if (position > 47 && board->pieceArr[position + 7]->color == black) {
                        toReturn->push_back(
                                pieceMove(this, position, position + 7, pieceMove::upgrade, position + 7,
                                          piece::knight));
                        toReturn->push_back(
                                pieceMove(this, position, position + 7, pieceMove::upgrade, position + 7,
                                          piece::bishop));
                        toReturn->push_back(
                                pieceMove(this, position, position + 7, pieceMove::upgrade, position + 7,
                                          piece::rook));
                        toReturn->push_back(
                                pieceMove(this, position, position + 7, pieceMove::upgrade, position + 7,
                                          piece::queen));
                    }
                }
            }

            if(position % 8 != 7) {
                if (board->pieceArr[position + 9] != nullptr) {
                    if (position > 47 && board->pieceArr[position + 9]->color == black) {
                        toReturn->push_back(
                                pieceMove(this, position, position + 9, pieceMove::upgrade, position + 9,
                                          piece::knight));
                        toReturn->push_back(
                                pieceMove(this, position, position + 9, pieceMove::upgrade, position + 9,
                                          piece::bishop));
                        toReturn->push_back(
                                pieceMove(this, position, position + 9, pieceMove::upgrade, position + 9,
                                          piece::rook));
                        toReturn->push_back(
                                pieceMove(this, position, position + 9, pieceMove::upgrade, position + 9,
                                          piece::queen));
                    }
                }
            }

            // en passant
            if(position > 31 && position < 40) {

                if(position % 8 != 0 && position + 7 == board->enPassantTarget)
                    toReturn->push_back(pieceMove(this, position, position + 7, pieceMove::enPassant, position - 1));

                if(position % 8 != 7 && position + 9 == board->enPassantTarget)
                    toReturn->push_back(pieceMove(this, position, position + 9, pieceMove::enPassant, position + 1));

            }


        } else {
            //black

            // if still in rank 7 (can double move)
            if(position > 47) {
                if(board->pieceArr[position - 16] == nullptr && board->pieceArr[position - 8] == nullptr)
                    toReturn->push_back(pieceMove(this, position, position - 16, pieceMove::doublePawn));
            }

            // if in ranks 2-6 (normal move)
            if(position > 15 && board->pieceArr[position - 8] == nullptr)
                toReturn->push_back(pieceMove(this, position, position - 8));

            // if in rank 2 (upgrade)
            if(position < 16 && board->pieceArr[position - 8] == nullptr){
                toReturn->push_back(pieceMove(this, position, position - 8, pieceMove::upgrade, -1, piece::knight));
                toReturn->push_back(pieceMove(this, position, position - 8, pieceMove::upgrade, -1, piece::bishop));
                toReturn->push_back(pieceMove(this, position, position - 8, pieceMove::upgrade, -1, piece::rook));
                toReturn->push_back(pieceMove(this, position, position - 8, pieceMove::upgrade, -1, piece::queen));

            }

            // capturing for all but last row
            if(position % 8 != 7) {
                if (board->pieceArr[position - 7] != nullptr)
                    if (position > 15 && board->pieceArr[position - 7]->color == white)
                        toReturn->push_back(pieceMove(this, position, position - 7, pieceMove::none, position - 7));
            }

            if(position % 8 != 0) {
                if (board->pieceArr[position - 9] != nullptr)
                    if (position > 15 && board->pieceArr[position - 9]->color == white)
                        toReturn->push_back(pieceMove(this, position, position - 9, pieceMove::none, position - 9));
            }

            // capturing + upgrading
            if(position % 8 != 7) {
                if (board->pieceArr[position - 7] != nullptr) {
                    if (position < 16 && board->pieceArr[position - 7]->color == white) {
                        toReturn->push_back(
                                pieceMove(this, position, position - 7, pieceMove::upgrade, position - 7,
                                          piece::knight));
                        toReturn->push_back(
                                pieceMove(this, position, position - 7, pieceMove::upgrade, position - 7,
                                          piece::bishop));
                        toReturn->push_back(
                                pieceMove(this, position, position - 7, pieceMove::upgrade, position - 7,
                                          piece::rook));
                        toReturn->push_back(
                                pieceMove(this, position, position - 7, pieceMove::upgrade, position - 7,
                                          piece::queen));
                    }
                }
            }

            if(position % 8 != 0) {
                if (board->pieceArr[position - 9] != nullptr) {
                    if (position < 16 && board->pieceArr[position - 9]->color == white) {
                        toReturn->push_back(
                                pieceMove(this, position, position - 9, pieceMove::upgrade, position - 9,
                                          piece::knight));
                        toReturn->push_back(
                                pieceMove(this, position, position - 9, pieceMove::upgrade, position - 9,
                                          piece::bishop));
                        toReturn->push_back(
                                pieceMove(this, position, position - 9, pieceMove::upgrade, position - 9,
                                          piece::rook));
                        toReturn->push_back(
                                pieceMove(this, position, position - 9, pieceMove::upgrade, position - 9,
                                          piece::queen));
                    }
                }
            }

            // en passant
            if(position > 23 && position < 32) {

                if(position % 8 != 7 && position - 7 == board->enPassantTarget)
                    toReturn->push_back(pieceMove(this, position, position - 7, pieceMove::enPassant, position + 1));

                if(position % 8 != 0 && position - 9 == board->enPassantTarget)
                    toReturn->push_back(pieceMove(this, position, position - 9, pieceMove::enPassant, position - 1));

            }


        }
    }
    else if(type == knight) {

        /*
         * https://www.chessprogramming.org/Knight_Pattern
         * made it much easier to visualize
         */


        int newPosition = 0;

        if( (position % 8) > 0 && (position / 8)  > 1) {

            newPosition = position - 17;

            if (newPosition >= 0 && newPosition < 64) {

                if (board->pieceArr[newPosition] != nullptr)
                    if (board->pieceArr[newPosition]->color != this->color)
                        toReturn->push_back(pieceMove(this, position, newPosition, pieceMove::none, newPosition));

                if (board->pieceArr[newPosition] == nullptr) {
                    toReturn->push_back(pieceMove(this, position, newPosition));

                }

            }
        }

        if( (position % 8) < 7 && (position / 8)  > 1) {
            newPosition = position - 15;
            if (newPosition >= 0 && newPosition < 64) {
                if (board->pieceArr[newPosition] != nullptr)
                    if (board->pieceArr[newPosition]->color != this->color)
                        toReturn->push_back(pieceMove(this, position, newPosition, pieceMove::none, newPosition));

                if (board->pieceArr[newPosition] == nullptr) {
                    toReturn->push_back(pieceMove(this, position, newPosition));

                }

            }
        }

        if( (position % 8) > 1 && (position / 8)  > 0) {
            newPosition = position - 10;
            if (newPosition >= 0 && newPosition < 64) {

                if (board->pieceArr[newPosition] != nullptr)
                    if (board->pieceArr[newPosition]->color != this->color)
                        toReturn->push_back(pieceMove(this, position, newPosition, pieceMove::none, newPosition));

                if (board->pieceArr[newPosition] == nullptr) {
                    toReturn->push_back(pieceMove(this, position, newPosition));

                }

            }
        }

        if( (position % 8) < 6 && (position / 8)  > 0) {
            newPosition = position - 6;
            if (newPosition >= 0 && newPosition < 64) {

                if (board->pieceArr[newPosition] != nullptr)
                    if (board->pieceArr[newPosition]->color != this->color)
                        toReturn->push_back(pieceMove(this, position, newPosition, pieceMove::none, newPosition));

                if (board->pieceArr[newPosition] == nullptr) {
                    toReturn->push_back(pieceMove(this, position, newPosition));

                }

            }
        }



        if( (position % 8) > 1 && (position / 8)  < 7) {
            newPosition = position + 6;
            if (position >= 0 && position < 64) {

                if (board->pieceArr[newPosition] != nullptr)
                    if (board->pieceArr[newPosition]->color != this->color)
                        toReturn->push_back(pieceMove(this, position, newPosition, pieceMove::none, newPosition));

                if (board->pieceArr[newPosition] == nullptr) {
                    toReturn->push_back(pieceMove(this, position, newPosition));

                }

            }
        }



        if( (position % 8) < 6 && (position / 8)  < 7) {
            newPosition = position + 10;
            if (position >= 0 && position < 64) {


                if (board->pieceArr[newPosition] != nullptr)
                    if (board->pieceArr[newPosition]->color != this->color)
                        toReturn->push_back(pieceMove(this, position, newPosition, pieceMove::none, newPosition));

                if (board->pieceArr[newPosition] == nullptr) {
                    toReturn->push_back(pieceMove(this, position, newPosition));

                }

            }
        }

        if( (position % 8) > 0 && (position / 8)  < 6) {
            newPosition = position + 15;
            if (position >= 0 && position < 64) {
                if (board->pieceArr[newPosition] != nullptr)
                    if (board->pieceArr[newPosition]->color != this->color)
                        toReturn->push_back(pieceMove(this, position, newPosition, pieceMove::none, newPosition));

                if (board->pieceArr[newPosition] == nullptr) {
                    toReturn->push_back(pieceMove(this, position, newPosition));

                }

            }
        }


        if( (position % 8) < 7 && (position / 8)  < 6 ){
            newPosition = position + 17;
            if (position >= 0 && position < 64) {
                if (board->pieceArr[newPosition] != nullptr)
                    if (board->pieceArr[newPosition]->color != this->color)
                        toReturn->push_back(pieceMove(this, position, newPosition, pieceMove::none, newPosition));

                if (board->pieceArr[newPosition] == nullptr) {
                    toReturn->push_back(pieceMove(this, position, newPosition));

                }

            }
        }



    }

    else if(type == bishop || type == queen) {

        int tempPosition = position;

        int tempPosition2 = position;

        tempPosition -= 9;
        // down left
        while (tempPosition >= 0 && tempPosition < 64) {
            if( (tempPosition2 % 8) > 0 && (tempPosition2 / 8)  > 0) {

                if (board->pieceArr[tempPosition] != nullptr)
                    if (board->pieceArr[tempPosition]->color == this->color)
                        break;
                if (board->pieceArr[tempPosition] != nullptr) {
                    if (board->pieceArr[tempPosition] != nullptr) {
                        toReturn->push_back(pieceMove(this, position, tempPosition, pieceMove::none, tempPosition));
                        break;
                    }
                }

                toReturn->push_back(pieceMove(this, position, tempPosition));
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

                if (board->pieceArr[tempPosition] != nullptr)
                    if (board->pieceArr[tempPosition]->color == this->color)
                        break;

                if (board->pieceArr[tempPosition] != nullptr) {
                    if (board->pieceArr[tempPosition] != nullptr) {
                        toReturn->push_back(pieceMove(this, position, tempPosition, pieceMove::none, tempPosition));
                        break;
                    }
                }

                toReturn->push_back(pieceMove(this, position, tempPosition));
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
                if (board->pieceArr[tempPosition] != nullptr)
                    if (board->pieceArr[tempPosition]->color == this->color)
                        break;

                if (board->pieceArr[tempPosition] != nullptr) {
                    if (board->pieceArr[tempPosition] != nullptr) {
                        toReturn->push_back(pieceMove(this, position, tempPosition, pieceMove::none, tempPosition));
                        break;
                    }
                }

                toReturn->push_back(pieceMove(this, position, tempPosition));
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

                if (board->pieceArr[tempPosition] != nullptr)
                    if (board->pieceArr[tempPosition]->color == this->color)
                        break;
                if (board->pieceArr[tempPosition] != nullptr) {
                    if (board->pieceArr[tempPosition] != nullptr) {
                        toReturn->push_back(pieceMove(this, position, tempPosition, pieceMove::none, tempPosition));
                        break;
                    }
                }

                toReturn->push_back(pieceMove(this, position, tempPosition));
                tempPosition += 9;
                tempPosition2 += 9;
            }else{
                break;
            }
        }


    }

    if(type == rook || type == queen) {


        int tempPosition = position;
        tempPosition--;
        // left
        while(tempPosition % 8 != 7 && tempPosition >= 0 && tempPosition < 64) {
            if(board->pieceArr[tempPosition] != nullptr)
                if(board->pieceArr[tempPosition]->color == this->color)
                    break;

            if(board->pieceArr[tempPosition] != nullptr) {
                if (board->pieceArr[tempPosition] != nullptr) {
                    toReturn->push_back(pieceMove(this, position, tempPosition, pieceMove::none, tempPosition));
                    break;
                }
            }



            toReturn->push_back(pieceMove(this, position, tempPosition));

            tempPosition--;
        }

        tempPosition = position;
        tempPosition++;
        // right
        while(tempPosition % 8 != 0 && tempPosition >= 0 && tempPosition < 64) {
            if(board->pieceArr[tempPosition] != nullptr)
                if(board->pieceArr[tempPosition]->color == this->color)
                    break;

            if(board->pieceArr[tempPosition] != nullptr) {
                if (board->pieceArr[tempPosition] != nullptr) {
                    toReturn->push_back(pieceMove(this, position, tempPosition, pieceMove::none, tempPosition));
                    break;
                }
            }

            toReturn->push_back(pieceMove(this, position, tempPosition));

            tempPosition++;
        }


        tempPosition = position;
        tempPosition += 8;
        // up
        while(tempPosition >= 0 && tempPosition < 64) {
            if(board->pieceArr[tempPosition] != nullptr)
                if(board->pieceArr[tempPosition]->color == this->color)
                    break;

            if(board->pieceArr[tempPosition] != nullptr) {
                if (board->pieceArr[tempPosition] != nullptr) {
                    toReturn->push_back(pieceMove(this, position, tempPosition, pieceMove::none, tempPosition));
                    break;
                }
            }

            toReturn->push_back(pieceMove(this, position, tempPosition));

            tempPosition += 8;
        }


        tempPosition = position;
        tempPosition -= 8;
        // down
        while(tempPosition >= 0 && tempPosition < 64) {
            if(board->pieceArr[tempPosition] != nullptr)
                if(board->pieceArr[tempPosition]->color == this->color)
                    break;

            if(board->pieceArr[tempPosition] != nullptr) {
                if (board->pieceArr[tempPosition] != nullptr) {
                    toReturn->push_back(pieceMove(this, position, tempPosition, pieceMove::none, tempPosition));
                    break;
                }
            }

            toReturn->push_back(pieceMove(this, position, tempPosition));

            tempPosition -= 8;
        }


    }

    if(type == king){

        // right
        if((position % 8) < 7) {
            if(board->pieceArr[position + 1] != nullptr) {
                if (board->pieceArr[position + 1]->color != this->color) {
                    toReturn->push_back(pieceMove(this, position, position + 1, pieceMove::none, position + 1));

                }
            } else {
                toReturn->push_back(pieceMove(this, position, position + 1));
            }
        }


        // down right
        if((position / 8) > 0 && (position % 8) < 7) {
            if(board->pieceArr[position - 7] != nullptr) {
                if (board->pieceArr[position - 7]->color != this->color) {
                    toReturn->push_back(pieceMove(this, position, position - 7, pieceMove::none, position - 7));

                }
            } else {
                toReturn->push_back(pieceMove(this, position, position - 7));
            }
        }

        // down
        if((position / 8) > 0) {
            if(board->pieceArr[position - 8] != nullptr) {
                if (board->pieceArr[position - 8]->color != this->color) {
                    toReturn->push_back(pieceMove(this, position, position - 8, pieceMove::none, position - 8));

                }
            } else {
                toReturn->push_back(pieceMove(this, position, position - 8));
            }
        }


        // down left
        if((position / 8) > 0 && (position % 8) > 0) {
            if(board->pieceArr[position - 7] != nullptr) {
                if (board->pieceArr[position - 7]->color != this->color) {
                    toReturn->push_back(pieceMove(this, position, position - 7, pieceMove::none, position - 7));

                }
            } else {
                toReturn->push_back(pieceMove(this, position, position - 7));
            }
        }

        // left
        if((position % 8) > 0) {
            if(board->pieceArr[position - 1] != nullptr) {
                if (board->pieceArr[position - 1]->color != this->color) {
                    toReturn->push_back(pieceMove(this, position, position - 1, pieceMove::none, position - 1));

                }
            } else {
                toReturn->push_back(pieceMove(this, position, position - 1));
            }
        }

        // up left
        if((position / 8) < 7 && (position % 8) > 0) {
            if(board->pieceArr[position + 7] != nullptr) {
                if (board->pieceArr[position + 7]->color != this->color) {
                    toReturn->push_back(pieceMove(this, position, position + 7, pieceMove::none, position + 7));

                }
            } else {
                toReturn->push_back(pieceMove(this, position, position + 7));
            }
        }

        // up
        if((position / 8) < 7) {
            if(board->pieceArr[position + 8] != nullptr) {
                if (board->pieceArr[position + 8]->color != this->color) {
                    toReturn->push_back(pieceMove(this, position, position + 8, pieceMove::none, position + 8));

                }
            } else {
                toReturn->push_back(pieceMove(this, position, position + 8));
            }
        }

        // up right
        if((position / 8) < 7 && (position % 8) < 7) {
            if(board->pieceArr[position + 9] != nullptr) {
                if (board->pieceArr[position + 9]->color != this->color) {
                    toReturn->push_back(pieceMove(this, position, position + 9, pieceMove::none, position + 9));

                }
            } else {
                toReturn->push_back(pieceMove(this, position, position + 9));
            }
        }

    }

    // castling
    if(type == rook) {

        //TODO: relies on blackIncheck and whiteIncheck values that are never changed

        // TODO: check if any in between squares are under attack

        if(color == black && !(board->blackInCheck)) {

            if(position == 56 && board->canCastle[2]) {
                if(board->pieceArr[57] == nullptr && board->pieceArr[58] == nullptr && board->pieceArr[59] == nullptr) {

                    toReturn->push_back(pieceMove(this, position, 59, pieceMove::queensideCastle));
                }
            }

            if(position == 63 && board->canCastle[3]) {

                if(board->pieceArr[61] == nullptr && board->pieceArr[62] == nullptr) {
                    toReturn->push_back(pieceMove(this, position, 61, pieceMove::kingsideCastle));
                }
            }

        }

        if(color == white && !(board->whiteInCheck)) {

            if(position == 0 && board->canCastle[0]) {
                if(board->pieceArr[1] == nullptr && board->pieceArr[2] == nullptr && board->pieceArr[3] == nullptr) {
                    toReturn->push_back(pieceMove(this, position, 3, pieceMove::queensideCastle));
                }
            }

            if(position == 7 && board->canCastle[1]) {

                if(board->pieceArr[5] == nullptr && board->pieceArr[6] == nullptr) {
                    toReturn->push_back(pieceMove(this, position, 5, pieceMove::kingsideCastle));
                }

            }
        }


    }


    return toReturn;
}

void piece::pseudoLegalPrint(int position, chessBoard *board, std::vector<pieceMove>* moveVector) {

    std::cout << colorToString() << " " << typeToString() << ": " << board->positionToString(position) <<std::endl;

    for (int i = 0; i < moveVector->size(); ++i) {
        std::cout << " - ";
        (*moveVector)[i].printMove(board);

    }

    if(moveVector->size() == 0) {
        std::cout << "no legal moves" << std::endl;

    }
    std::cout << std::endl;


}

std::string piece::typeToString() {

    return nameDefType[type];

}

std::string piece::colorToString() {



    return nameDefColor[color];
}

