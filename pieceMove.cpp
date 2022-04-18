#include "pieceMove.h"
#include "piece.h"
#include <iostream>
void pieceMove::printMove() {
    std::cout << to << " ";

    if(capturing != -1){
        std::cout << "capturing ";
    }

    if(specialMove != na){
        std::cout << specialMove;
    }

    std::cout << std::endl;

}
