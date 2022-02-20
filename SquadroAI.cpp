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
    int score = 0;
    for (int i = 0; i < 6; i++)
        score += _rscore[i];
    return score;
}

int Squadro::AI_redscore(std::string game)
{
     int score;
    int scoretoremove = 0;
    int score2 = scoreyellow() - scorered();
    std::cout << "AI FEN : " << game << " for score : " << scorered() - scoreyellow() - 1 << std::endl;
    for (int i = 0; i < 6; i++)
    {
        this->move_yellow(i);
        score = scoreyellow() - scorered() - 1;
        if ( score > score2 )
        {
            scoretoremove = score - score2;
            std::cout << "Score to remove detected for the " << i << " :  " << scoretoremove << std::endl;
        }
        this->reset(game);
    }
    this->reset(game);
    return (scorered() - scoreyellow() - scoretoremove);
}

int Squadro::AI_yellowscore(std::string game)
{
    int score;
    int scoretoremove = 0;
    int score2 = scorered() - scoreyellow();
    std::cout << "AI FEN : " << game << " for score : " << scoreyellow() - scorered() << std::endl;
    for (int i = 0; i < 6; i++)
    {
        this->move_red(i);
        score = scorered() - scoreyellow() - 1;
        if ( score > score2 )
        {
            scoretoremove = score - score2;
            std::cout << "Score to remove detected for the " << i << " :  " << scoretoremove << std::endl;
        }
        this->reset(game);
    }
    this->reset(game);
    return (scoreyellow() - scorered() - scoretoremove);
}

int Squadro::scoreyellow()
{
    int score = 0;
    for (int i = 0; i < 6; i++)
        score += _yscore[i];
    return score;
}

int Squadro::find_best_ymove(std::string fen)
{
    int bestmove = 0;
    std::string game;
    game = fen;
    _fen = fen;
    Squadro a;
    a.reset(fen);
    int bestscore = -100000;
    for (int i = 1; i < 6; i++)
    {
        if (a._yellowend[i] == false)
        {
            a.move_yellow(i);
            game += "y" + std::to_string(i);
            if (a._yellowend[i] == false)
            {
                int score = a.AI_yellowscore(game);
                if (score > bestscore)
                {
                    bestscore = score;
                    bestmove = i;
                }
            }
        }
        a.reset(fen);
        game = fen;
    }
    if (bestmove == 0)
    {
        std::cout << "No move found, return random by default" << std::endl;
        sleep (1);
        bestmove = rand() % 6 + 1;
        while (a._redend[bestmove] == true)
            bestmove = rand() % 6 + 1;
        return (bestmove);
    }
    return bestmove;
}

int Squadro::find_best_rmove(std::string fen)
{
    int bestmove = 0;
    _fen = fen;
    std::string game = fen;
    Squadro a;
    a.reset(fen);
    int bestscore = -100000;
    for (int i = 1; i < 6; i++)
    {
        if (a._redend[i] == false)
        {
            a.move_red(i);
            game += "r" + std::to_string(i);
            if (a._redend[i] == false)
            {
                int score = a.AI_redscore(game);
                if (score > bestscore)
                {
                    bestscore = score;
                    bestmove = i;
                }
            }
        }
        a.reset(fen);
        std::cout << "RESET" << std::endl << std::endl << std::endl;
        game = fen;
    }
    if (bestmove == 0)
    {
        std::cout << "No move found, return random by default" << std::endl;
        sleep (1);
        bestmove = rand() % 6 + 1;
        while (a._redend[bestmove] == true)
            bestmove = rand() % 6 + 1;
        return (bestmove);
    }
    return bestmove;
}

int Squadro::find_best_move(std::string fen)
{
    int bestmove = 0;
    _fen = fen;
    unsigned int i = 0;
    Squadro a;
    while (fen[i])
        i++;
    if (i > 2)
    {
        if (fen[i - 2] == 'r')
            return find_best_ymove(fen);
        else if (fen[i - 2] == 'y')
            return find_best_rmove(fen);
        else
        {
            std::cout << "ERROR finding the last color, return 1 by default" << std::endl;
            bestmove = 1;
        }
    }
    if (bestmove == 0)
    {
        std::cout << "No move found, return 1 by default" << std::endl;
        return (1);
    }
    return bestmove;
}
