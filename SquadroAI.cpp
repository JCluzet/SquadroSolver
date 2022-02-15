#include <iostream>
#include "Squadro.hpp"
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

Squadro::Squadro(Squadro &a)
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

int Squadro::scorered() 
{
    // the score of red is the 
    int score = 0;
    for (int i = 0; i < 6; i++)
    {
        score += _rscore[i];
    }
    return score;
}

int Squadro::AI_redscore()
{
    return (scorered() - scoreyellow());
}

int Squadro::AI_yellowscore()
{
    return (scoreyellow() - scorered());
}

int Squadro::scoreyellow()
{
    // the score of yellow is the 
    int score = 0;
    for (int i = 0; i < 6; i++)
    {
        score += _yscore[i];
    }
    return score;
}

int Squadro::find_best_move(std::string fen)
{
    int bestmove = 0;
    _fen = fen;
    Squadro a;
    a.get_fen(fen);
    int bestscore = -100000;
    for (int i = 1; i < 6; i++)
    {
        if (a._redend[i] == false)
        {
            a.move_red(i);
            for (int j = 1; j < 6; j++)
            {
                if (a._yellowend[j] == false)
                {
                    a.move_yellow(j);
                    for (int v = 1; v < 6; v++)
                    {
                        if (a._redend[v] == false)
                        {
                            a.move_red(v);
                            int score = a.AI_redscore();
                            if (score > bestscore)
                            {
                                bestscore = score;
                                bestmove = i;
                            }
                            a.get_fen(fen);
                        }
                    }
                }
            }
        }
    }


    return bestmove;
}


