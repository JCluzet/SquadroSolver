#include <iostream>
#include "Squadro.hpp"

Squadro::Squadro()
{
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            _gameboard[i][j] = 0;
        }
    }
    for (int i = 0; i < 6; i++)
    {
        _red[i] = 0;
        _yellow[i] = 0;
        _redend[i] = false;
        _yellowend[i] = false;
        _rscore[i] = 0;
        _yscore[i] = 0;
    }

    _yellowmoves[1] = 3;
    _yellowmoves[2] = 1;
    _yellowmoves[3] = 2;
    _yellowmoves[4] = 1;
    _yellowmoves[5] = 3;

    _redmoves[1] = 1;
    _redmoves[2] = 3;
    _redmoves[3] = 2;
    _redmoves[4] = 3;
    _redmoves[5] = 1;

    _gameboard[6][1] = 1; // red
    _gameboard[6][2] = 1;
    _gameboard[6][3] = 1;
    _gameboard[6][4] = 1;
    _gameboard[6][5] = 1;

    _gameboard[1][6] = 2; // yellow
    _gameboard[2][6] = 2;
    _gameboard[3][6] = 2;
    _gameboard[4][6] = 2;
    _gameboard[5][6] = 2;
}

void Squadro::reset()
{
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            _gameboard[i][j] = 0;
        }
    }
    for (int i = 0; i < 6; i++)
    {
        _red[i] = 0;
        _yellow[i] = 0;
        _redend[i] = false;
        _yellowend[i] = false;
        _rscore[i] = 0;
        _yscore[i] = 0;
    }

    _yellowmoves[1] = 3;
    _yellowmoves[2] = 1;
    _yellowmoves[3] = 2;
    _yellowmoves[4] = 1;
    _yellowmoves[5] = 3;

    _redmoves[1] = 1;
    _redmoves[2] = 3;
    _redmoves[3] = 2;
    _redmoves[4] = 3;
    _redmoves[5] = 1;

    _gameboard[6][1] = 1; // red
    _gameboard[6][2] = 1;
    _gameboard[6][3] = 1;
    _gameboard[6][4] = 1;
    _gameboard[6][5] = 1;

    _gameboard[1][6] = 2; // yellow
    _gameboard[2][6] = 2;
    _gameboard[3][6] = 2;
    _gameboard[4][6] = 2;
    _gameboard[5][6] = 2;
    _fen = "";
}

Squadro::~Squadro()
{
}

int get_linefor_red(int nb)
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

int down_orup(int nb)
{ // envoyer : red[i]
    if (nb > 6)
        return 1;
    else
        return 0;
}

int switch_side2(int n)
{
    if (n == 1)
        return(3);
    else if (n == 2)
        return(2);
    else if (n == 3)
        return(1);
    return(0);
}

void Squadro::reset_yellow(int nb)
{
    if (_yellow[nb] < 6)
    {
        _gameboard[nb][6] = 2;
        _yellow[nb] = 0;
        _yscore[nb] = 0;
    }
    else 
    {
        _gameboard[nb][0] = 2;
        _yellow[nb] = 6;
        if (_yellowmoves[nb] == 3)
            _yscore[nb] = 6;
        if (_yellowmoves[nb] == 2)
            _yscore[nb] = 3;
        if (_yellowmoves[nb] == 1)
            _yscore[nb] = 2;
    }
}

int Squadro::move_red_one(int nb) // 1
{ // return 1 sil faut arreter le move
    int line = get_linefor_red(_red[nb]);
    int ret = 0;
    _red[nb]++;
    int newline = get_linefor_red(_red[nb]);
    int newline2 = get_linefor_red(_red[nb] - 1);

    while (_gameboard[newline][nb] == 2)
    {
        // std::cout << "DETECT SHOCK" << std::endl;
        _gameboard[newline][nb] = 0;
        reset_yellow(newline);
        if (down_orup(_red[nb]) == 1)
        {
            // std::cout << "Go to ++\n" << std::endl;
            newline += 1;
            _red[nb] += 1;
        }
        else
        {
            // std::cout << "Go to --\n" << std::endl;
            newline -= 1;
            _red[nb] += 1;
        }
        ret = 1;
    }
    if (ret == 1)
    {
        _gameboard[line][nb] = 0;
        _gameboard[newline][nb] = 1;
        if (newline == 6)
        {
            _redend[nb] = true;
        }
        if (newline == 0)
        {
            _redmoves[nb] = switch_side2(_redmoves[nb]);
            return(1);
        }
        return (1);
    }
    else
    {
        // std::cout << "NO SHOCK" << std::endl;
        if (down_orup(_red[nb]) == 1)
        {
            newline2 += 1;
        }
        else
        {
            newline2 -= 1;
        }
        _gameboard[line][nb] = 0;
        _gameboard[newline2][nb] = 1;
        if (newline2 == 6)
        {
            _redend[nb] = true;
            return(1);
        }
        if (newline2 == 0)
        {
            _redmoves[nb] = switch_side2(_redmoves[nb]);
            return(1);
        }
    }
    return (0);
}

int Squadro::move_red(int nb)
{
    if (nb < 1 || nb > 5 || _red[nb] > 11)
        return (1);
    _rscore[nb] += 1;
    for (int i = 0; i < _redmoves[nb]; i++)
    {
        if (move_red_one(nb) == 1)
            return 0;
    }
    _fen += "r" + std::to_string(nb);
    return 0;
}

Squadro Squadro::operator=(Squadro &other)
{
    for (int i = 0; i < 6; i++)
    {
        _red[i] = other._red[i];
        _yellow[i] = other._yellow[i];
        _redmoves[i] = other._redmoves[i];
        _redend[i] = other._redend[i];
    }
    return *this;
}

int Squadro::redwin(void)
{
    int ret = 0;
    for (int i = 0; i < 6; i++)
    {
        if (_redend[i] == true)
        {
            ret++;
        }
    }
    if (ret > 3)
    {
        return 1;
    }
    return 0;
}

int Squadro::yellowwin(void)
{
    int ret = 0;
    for (int i = 0; i < 6; i++)
    {
        if (_yellowend[i] == true)
        {
            ret++;
        }
    }
    if (ret > 3)
    {
        return 1;
    }
    return 0;
}


int Squadro::whoplay() // return 1 if red, 2 if yellow
{
    int n = 0;
    if (_fen == "")
        return 0;
    while (_fen[n])
        n++;
    if (_fen[n - 2] == 'r')
        return 1;
    else
        return 2;
}







void Squadro::show()
{
    std::cout << "       ???       ???" << std::endl;
    std::cout << "       ???   ???   ???" << std::endl;
    std::cout << "       ??? ??? ??? ??? ???" << std::endl;
    std::cout << std::endl;
    for (int i = 0; i < 7; i++)
    {
        if (i == 0 || i == 6)
        {
            std::cout << "     ";
        }
        if (i == 1)
        {
            std::cout << "  ???  ";
        }
        if (i == 2)
        {
            std::cout << "?????????  ";
        }
        if (i == 3)
        {
            std::cout << " ??????  ";
        }
        if (i == 4)
        {
            std::cout << "?????????  ";
        }
        if (i == 5)
        {
            std::cout << "  ???  ";
        }
        for (int j = 0; j < 7; j++)
        {
            if ((i == 0 && j == 0) || (i == 6 && j == 0) || (i == 0 && j == 6) || (i == 6 && j == 6))
                std::cout << "  ";
            else
            {
                if (_gameboard[i][j] == 1)
                {
                    if (_redend[j] == true)
                        std::cout << GREEN << "???" << RESET << " ";
                    else if (_red[j] > 5)
                        std::cout << RED << "???" << RESET << " ";
                    else
                        std::cout << RED << "???" << RESET << " ";
                }
                else if (_gameboard[i][j] == 2)
                {
                    if (_yellowend[i] == true)
                        std::cout << GREEN << "???" << RESET << " ";
                    else if (_yellow[i] > 5)
                        std::cout << YELLOW << "???" << RESET << " ";
                    else
                        std::cout << YELLOW << "???" << RESET << " ";
                }
                else
                {
                    if (j == 0 || j == 6 || i == 0 || i == 6)
                        std::cout << ". ";
                    else
                        std::cout << _gameboard[i][j] << " ";
                }
            }
        }
        if (i == 0 || i == 6)
        {
            std::cout << "    ";
        }
        if (i == 1)
        {
            std::cout << " ?????????";
        }
        if (i == 2)
        {
            std::cout << " ???";
        }
        if (i == 3)
        {
            std::cout << " ??????";
        }
        if (i == 4)
        {
            std::cout << " ???";
        }
        if (i == 5)
        {
            std::cout << " ?????????";
        }
        std::cout << std::endl;
    }
        std::cout << std::endl;
        std::cout << "       ??? ??? ??? ??? ???" << std::endl;
        std::cout << "         ??? ??? ???  " << std::endl;
        std::cout << "         ???   ???  " << std::endl;
    //std::cout << std::endl << std::endl << std::endl;
        // std::cout << std::endl;
        // // output _red[u] from 1 to 5 
        // for (int u = 0; u < 7; u++)
        // {
        //     std::cout << "RED " << u << " : " << _red[u] << std::endl;
        // }
    std::cout << std::endl << "FEN : " << YELLOW << _fen << RESET << std::endl;

    std::cout << RED << "RED SCORE : " << this->scorered() << RESET << " | " << YELLOW << "YELLOW SCORE : " << this->scoreyellow() << RESET << std::endl << std::endl;
}