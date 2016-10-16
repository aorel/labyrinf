#pragma once

typedef enum Action
{
    Player_up,
    Player_down,
    Player_left,
    Player_right,
} Action;

class Command{
private:
    Command();

public:
    const Action action;
    Command(Action a);
};
