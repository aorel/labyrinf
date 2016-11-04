#pragma once

#include "../settings.h"

typedef enum CellType{
    WALL,
    GROUND,
    WATER,
    FIRE,
} CellType;

class Cell{
public:
    Cell() = default;
    //Cell(CellType t);
    virtual ~Cell() = default;

    CellType getType() const;
    virtual void setType(CellType t);

protected:
    CellType type = GROUND;
};
