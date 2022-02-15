#include <iostream>
#include "Squadro.hpp"

int get_xfor_yellow(int nb)
{
    int line = 0;
    switch (nb)
    {
    case 0:
        line = 6;
        break;
    case 1:
        line = 5;
        break;
    case 2:
        line = 4;
        break;
    case 3:
        line = 3;
        break;
    case 4:
        line = 2;
        break;
    case 5:
        line = 1;
        break;
    case 6:
        line = 0;
        break;
    case 7:
        line = 1;
        break;
    case 8:
        line = 2;
        break;
    case 9:
        line = 3;
        break;
    case 10:
        line = 4;
        break;
    case 11:
        line = 5;
        break;
    case 12:
        line = 6;
        break;
    default:
        break;
    }
    return line;
}

int down_orup2(int nb)
{ // envoyer : red[i]
    if (nb > 6)
        return 1;
    else
        return 0;
}

void Squadro::reset_red(int nb)
{
    if (_red[nb] < 6)
    {
        _gameboard[6][nb] = 1;
        _red[nb] = 0;
        _rscore[nb] = 0;
    }
    else 
    {
        _gameboard[0][nb] = 1;
        _red[nb] = 6;
        _rscore[nb] = 6/_redmoves[nb];
    }
}

int switch_side(int n)
{
    if (n == 1)
        return(3);
    else if (n == 2)
        return(2);
    else if (n == 3)
        return(1);
    return(0);
}

int Squadro::move_yellow_one(int nb) // 2
{ // return 1 sil faut arreter le move
    int x = get_xfor_yellow(_yellow[nb]);
    int ret = 0;
    _yellow[nb]++;
    int newx = get_xfor_yellow(_yellow[nb]);
    int newx2 = get_xfor_yellow(_yellow[nb] - 1);

    while (_gameboard[nb][newx] == 1)
    {
        // std::cout << "DETECT SHOCK" << std::endl;
        _gameboard[nb][newx] = 0;
        reset_red(newx);
        if (down_orup2(_yellow[nb]) == 1)
        {
            // std::cout << "Go to +\n" << std::endl;
            newx += 1;
            _yellow[nb] += 1;
        }
        else
        {
            // std::cout << "Go to -\n" << std::endl;
            newx -= 1;
            _yellow[nb] += 1;
        }
        ret = 1;
    }
    if (ret == 1)
    {
        _gameboard[nb][x] = 0;
        _gameboard[nb][newx] = 2;
        if (newx == 6)
        {
            _yellowend[nb] = true;
        }
        if (newx == 0)
        {
            _yellowmoves[nb] = switch_side(_yellowmoves[nb]);
            return(1);
        }
        return (1);
    }
    else
    {
        // std::cout << "NO SHOCK" << std::endl;
        if (down_orup2(_yellow[nb]) == 1)
        {
            newx2 += 1;
            // _yellow[nb] += 1;
        }
        else
        {
            newx2 -= 1;
            // _yellow[nb] += 1;
        }
        _gameboard[nb][x] = 0;
        _gameboard[nb][newx2] = 2;
        if (newx2 == 6)
        {
            _yellowend[nb] = true;
            return(1);
        }
        if (newx2 == 0)
        {
            _yellowmoves[nb] = switch_side(_yellowmoves[nb]);
            return(1);
        }
    }
    return (0);
}

int Squadro::move_yellow(int nb)
{
    if (nb < 1 || nb > 5)
        return (1);
    if (_yellow[nb] > 11)
    {
        return 1;
    }
    _yscore[nb] += 1;
    // std::cout << "There is " << _yellowmoves[nb] << " moves for " << nb << std::endl;
    for (int i = 0; i < _yellowmoves[nb]; i++)
    {
        if (move_yellow_one(nb) == 1)
        {
            // std::cout << "YELLOW " << nb << " is done here:" << std::endl;
            // _gameboard[nb][6] = 0;
            return 0;
        }
        // std::cout << "MOVE OK > YELLOW[nb] >> " << _yellow[nb] << std::endl;
        // std::cout << std::endl;
    }
        // show();
    // if (_yellow[nb] > 11)
    // {
    //     _gameboard[nb][6] = 9;
    //     return 1;
    // }
    return 0;
}