#pragma once

#include <vector>
#include <functional>

#include "cell.h"
#include "player.h"
#include "../events/playerEvent.h"
#include "../settings.h"

class Labyrinth{
public:
    Labyrinth();
    Labyrinth(std::function<Cell*()> cellFactory);
    virtual ~Labyrinth() = default;

    bool checkCommand(const Player &, const PlayerEvent&);

protected:
    std::vector<std::vector<std::unique_ptr<Cell>>> cells;
    void test_init();
};
