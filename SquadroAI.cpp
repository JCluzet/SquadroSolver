#include <iostream>
#include "Squadro.hpp"
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

Squadro::Squadro(const Squadro &a)
{
    for (int i = 0; i < 7; i++)
    {
        _red[i] = a._red[i];
        _redend[i] = a._redend[i];
        _yellowend[i] = a._yellowend[i];
        _yellow[i] = a._yellow[i];
        _redmoves[i] = a._redmoves[i];
        _yellowmoves[i] = a._yellowmoves[i];
    }
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            _gameboard[i][j] = a._gameboard[i][j];
        }
    }
}

int Squadro::find_best_redmove()
{
    // Use constructor to copy the gameboard
    Squadro sq1(*this);
    Squadro sq2(*this);
    Squadro sq3(*this);
    Squadro sq4(*this);
    Squadro sq5(*this);

    // Test all possible moves, and return the best one (the one that have more probability to win)
    // To find the best move, we need to test all possible moves, and test all possible moves until the end of the game
    // To avoid too many tests, we try 1 million test by turn (1 million test = 1 million turns)

    // First, we test all possible moves for red
    int bestmove = 0;
    for (int i = 1; i < 6; i++)
    {
        if (!sq1._redend[i])
        {
            sq1.move_red(i);
        }
        show();
        usleep(600000);
    }

    return bestmove;
}


