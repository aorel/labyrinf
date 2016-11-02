#pragma once

#include "settings.h"

typedef enum CellType{
    WALL,
    GROUND,
    WATER,
    FIRE,
} CellType;

class Cell{
public:
    void setType(CellType t);
    CellType getType() const;
private:
    CellType type = GROUND;
};
