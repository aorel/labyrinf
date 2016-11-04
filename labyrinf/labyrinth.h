#pragma once

#include <vector>

#include "cell.h"
//#include "cellDrawable.h"
#include "player.h"
#include "command.h"
#include "settings.h"

class Labyrinth{
public:
    Labyrinth();
    Labyrinth(std::function< Cell* () > cellFactory);
    virtual ~Labyrinth() = default;
    
    bool checkCommand(const Player &p, Command &command);
    //const std::vector<std::vector<Cell>>& getCells() const;

protected:
    std::vector<std::vector<std::unique_ptr<Cell>>> cells;
    void test_init();
};
