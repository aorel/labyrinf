#pragma once

#include <vector>

#include "cell.h"
#include "player.h"
#include "command.h"
#include "settings.h"

class Labyrinth{
public:
    Labyrinth();
    bool checkCommand(Player &p, Command &command);
    const std::vector<std::vector<Cell>>& getCells() const;

private:
    std::vector<std::vector<Cell>> cells;
};
