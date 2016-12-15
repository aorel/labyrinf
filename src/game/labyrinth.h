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

    bool checkCommand(const Player&, const PlayerEvent&);
    CellType getBonus(sf::Vector2i place);

protected:
    std::vector<std::vector<std::unique_ptr<Cell>>> cells;
<<<<<<< HEAD
    void test_init();
    void generator_init();

private:
	std::vector<std::vector<int>> generator(int width, int height);
	std::vector<std::pair<int, int>> adjacent(std::pair<int, int> cell);
=======
    void testInit();
    void generatorInit();

private:
    std::vector<std::vector<int>> generator(int width, int height);
    std::vector<std::pair<int, int>> adjacent(std::pair<int, int> cell);
>>>>>>> develop
};
