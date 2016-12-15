#include "labyrinth.h"
#include <utility>
#include <algorithm>
#include <random>
#include <iterator>

Labyrinth::Labyrinth() : Labyrinth( [](){return new Cell;} ){
    generator_init();
}

void Labyrinth::fromString (const std::string &labyrinthString)
{
    auto position = 0;
    auto i = 0;
    auto j = 0;
    while (position < labyrinthString.length())
    {
        std::cout << labyrinthString[position];
        if(labyrinthString[position] != ';' && labyrinthString[position] != '\n')
        {
            CellType type;
            switch(labyrinthString[position])
            {
                case '0':
                    type = WALL;
                    break;

                case '1':
                    type = GROUND;
                    break;

                case '2':
                    type = WATER;
                    break;

                case '3':
                    type = FIRE;
                    break;

                case '4':
                    type = HEART;
                    break;

                default:
                    type = WALL;
                    break;
            }
            cells[i][j]->setType(type);
            ++i;
        }

        else
        {
            ++j;
            i = 0;
        }

        ++position;
    }
}

std::string Labyrinth::toString()
{
    std::cout << "To String:" << std::endl;
    std::string result = "";

    for(auto i (0); i < settings::labyrinthSizeX; ++i)
    {
        for(auto j (0); j < settings::labyrinthSizeY; ++j)
        {
            CellType type = cells[j][i]->getType();
            switch(type)
            {
                case WALL:
                    result += "0";
                    break;

                case GROUND:
                    result += "1";
                    break;

                case WATER:
                    result += "2";
                    break;

                case FIRE:
                    result += "3";
                    break;

                case HEART:
                    result += "4";
                    break;
            }
        }
        result += ";";
    }

    std::cout << result << std::endl;
    return result;
}

Labyrinth::Labyrinth(std::function<Cell*()> cellFactory){
    for(int i(0); i<settings::labyrinthSizeX; ++i){
        std::vector<std::unique_ptr<Cell>> cellRow;
        for(int j(0); j<settings::labyrinthSizeY; ++j){
            cellRow.emplace_back( cellFactory() );
        }
        cells.push_back(std::move(cellRow));
    }
}

/*<<<<<<< HEAD
bool Labyrinth::checkCommand(const Player &p, const PlayerEvent& playerEvent){

    PressedKey key = playerEvent.getKey();
    sf::Vector2i position = p.getPosition();
    if(key == PressedKey::Up && position.y == 0){
        return false;
    }
    else if(key == PressedKey::Down && position.y == (settings::labyrinthSizeY-1)){
        return false;
    }
    else if(key == PressedKey::Left && position.x == 0){
        return false;
    }
    else if(key == PressedKey::Right && position.x == (settings::labyrinthSizeX-1)){
        return false;
    }
*/
bool Labyrinth::checkCommand(const Player &p, const PlayerEvent& playerEvent){
    PressedKey key = playerEvent.getKey();
    sf::Vector2i position = p.getPosition();

    if(key == PressedKey::Up && cells[position.x][position.y-1]->getType() == WALL){
        return false;
    }
    else if(key == PressedKey::Down && cells[position.x][position.y+1]->getType() == WALL){
        return false;
    }
    else if(key == PressedKey::Left && cells[position.x-1][position.y]->getType() == WALL){
        return false;
    }
    else if(key == PressedKey::Right && cells[position.x+1][position.y]->getType() == WALL){
        return false;
    }
    return true;
}

//=======
CellType Labyrinth::getBonus(sf::Vector2i place)
{
    if (cells[place.x][place.y]->getType() == HEART){
        cells[place.x][place.y]->setType(GROUND);
        return HEART;
    }
    return cells[place.x][place.y]->getType();
}
//>>>>>>> feature/game



void Labyrinth::test_init(){
    for(int i(0); i<settings::labyrinthSizeX; ++i){
        for(int j(0); j<settings::labyrinthSizeY; ++j){
            if( i == 0 || i == settings::labyrinthSizeX-1 || j == 0 || j == settings::labyrinthSizeY-1 ){
                cells[i][j]->setType(WALL);//cells[i][j].setType(WALL);
            }
            else if( i == j){
                cells[i][j]->setType(WATER);
            }else if( i+1 == j){
                cells[i][j]->setType(HEART);
            }
            else if( i+2 == j){
                cells[i][j]->setType(FIRE);
            }
            else{
                cells[i][j]->setType(GROUND);
            }
        }
    }
}

void Labyrinth::generator_init()
{
    /*std::vector<std::vector<int>> temp = generator(settings::labyrinthSizeX, settings::labyrinthSizeY);
    for(auto i = 0; i < settings::labyrinthSizeY; ++i)
    {
        for(auto j = 0; j < settings::labyrinthSizeX; ++j)
            std::cout << temp[i][j];
        std::cout << std::endl;
    }

    std::cout << "-----------------------------" << std::endl;

    for(auto i = 0; i < settings::labyrinthSizeY; ++i)
    {
        for(auto j = 0; j < settings::labyrinthSizeX; ++j)
        {
            if(temp[i][j] == 1)
                cells[j][i]->setType(WALL);
            if(temp[i][j] == 0)
                cells[j][i]->setType(GROUND);
            if ((i == j) && (temp[i][j] == 0)){
                    cells[i][j]->setType(HEART);
                }
                if ((i + j == 10) && (temp[i][j] == 0)){
                    cells[i][j]->setType(FIRE);
                }
                if ((i + j == 8) && (temp[i][j] == 0)){
                    cells[i][j]->setType(WATER);
                }
        }
    }

    toString();*/
    std::cout <<  "------------------" << std::endl << "00000000000000000000;04111112131101110100;01000000000001000100;01140203010101110100;01000101010101000100;01111311111111111100;01000101010000010000;01110104010111011100;01010001010100010100;01011101041111010100;01010101010100010100;01010101010411010100;00010000010001000000;01111111011104111100;01010101010101000100;01010101010101140100;00010000000101000000;01111111110101111400;00000000000000000000;00000000000000000000;" << "-----------------------------" << std::endl;
    fromString("00000000000000000000;04111112131101110100;01000000000001000100;01140203010101110100;01000101010101000100;01111311111111111100;01000101010000010000;01110104010111011100;01010001010100010100;01011101041111010100;01010101010100010100;01010101010411010100;00010000010001000000;01111111011104111100;01010101010101000100;01010101010101140100;00010000000101000000;01111111110101111400;00000000000000000000;00000000000000000000;");
}

std::vector<std::pair<int, int>> Labyrinth::adjacent(std::pair<int, int> cell)
{
    std::vector<std::pair<int, int>> result;
    std::vector<std::pair<int, int>> iterable =
    {std::pair<int, int>(1, 0), std::pair<int, int>(0, 1),
     std::pair<int, int>(-1, 0), std::pair<int, int>(0, -1)};

    for(auto item : iterable)
    {
        result.push_back(std::pair<int, int>
                         (item.first + cell.first, item.second + cell.second));

        result.push_back(std::pair<int, int>
                         (item.first * 2 + cell.first, item.second * 2 + cell.second));
    }

    return result;
}

std::vector<std::vector<int>> Labyrinth::generator(int width, int height)
{
    std::vector<std::vector<int>> maze (height, std::vector<int>(width));
    for(auto i = 0; i < width; ++i)
    {
        for(auto j = 0; j < height; ++j)
            maze[i][j] = 0;
    }

    for(auto i = 0; i < height; ++i)
    {
        for(auto j = 0; j < width; ++j)
        {
            if((i % 2 == 1) && (j % 2 == 1))
                maze[i][j] = 0;

            else
                maze[i][j] = 1;
        }
    }

    for(auto i = 0; i < height; ++i)
    {
        maze[i][0] = 1;
        maze[i][width - 1] = 1;
    }

    for(auto j = 0; j < width; ++j)
    {
        maze[0][j] = 1;
        maze[height - 1][j] = 1;
    }

    std::vector<std::pair<int, int>> spaceCells;
    std::vector<std::pair<int, int>> wallCells;

    for(auto i = 0; i < height; ++i)
    {
        for(auto j = 0; j < width; ++j)
        {
            if(maze[i][j] == 0)
                spaceCells.push_back(std::pair<int, int>(i, j));

            if(maze[i][j] == 1)
                wallCells.push_back(std::pair<int, int>(i, j));
        }
    }

    std::vector<std::pair<int, int>> connected;
    connected.push_back(std::pair<int, int>(1, 1));

    while(connected.size() < spaceCells.size())
    {
        std::pair<int, int> doA = {-1, -1};
        std::pair<int, int> doB = {-1, -1};
        std::random_device randomDevice;
        std::mt19937 gen(randomDevice());
        std::shuffle(connected.begin(), connected.end(), gen);
        std::pair<int, int> A;
        std::pair<int, int> B;

        for(auto i : connected)
        {
            if(doA != std::pair<int, int>{-1, -1})
                break;

            std::vector<std::pair<int, int>> temp = adjacent(i);
            for(unsigned j(0); j < temp.size(); j += 2)
            {
                A = temp[j];
                B = temp[j + 1];

                if(std::find(wallCells.begin(), wallCells.end(), A)
                    == wallCells.end())
                    continue;

                if((std::find(spaceCells.begin(), spaceCells.end(), B)
                   == spaceCells.end()) ||
                   std::find(connected.begin(), connected.end(), B)
                   != connected.end())
                   continue;

                doA = A;
                doB = B;
                break;
            }
        }

        A = doA;
        B = doB;
        maze[A.first][A.second] = 0;
        for(auto i = wallCells.begin(); i != wallCells.end(); ++i)
        {
            if(*i == A)
            {
                wallCells.erase(i);
                break;
            }
        }

        spaceCells.push_back(A);
        connected.push_back(A);
        connected.push_back(B);
    }

    return maze;
}
