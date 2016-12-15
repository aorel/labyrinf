#pragma once

#include "../settings.h"

typedef enum CellType{
    WALL,
    GROUND,
    WATER,
    FIRE,
    HEART
} CellType;

class Cell{
public:
    Cell() = default;
    virtual ~Cell() = default;

    CellType getType() const;
    virtual void setType(CellType t);
protected:
    CellType type = GROUND;
};
