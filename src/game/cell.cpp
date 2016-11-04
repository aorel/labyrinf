#include "cell.h"

/*
Cell::Cell(CellType t) :
        type(t){
}
*/

CellType Cell::getType() const{
    return type;
}

void Cell::setType(CellType t){
    type = t;
}
