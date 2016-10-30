#pragma once

#include <functional>

typedef enum Command
{
    PlayerUp,
    PlayerDown,
    PlayerLeft,
    PlayerRight,
} Command;

typedef std::function< void(Command) > CommandFunction;
