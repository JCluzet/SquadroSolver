#include "Squadro.hpp"

void Squadro::friend_play()
{
    int turn = 0;
    int nb = 0;
    if (_fen == "")
    {

    std::cout << "Who start? (1 or 2)" << std::endl;
    std::cout << 1 << ": Red" << std::endl;
    std::cout << 2 << ": Yellow" << std::endl;
    std::cin >> turn;
    std::cout << std::endl;
    while (turn < 1 || turn > 2)
    {
        std::cout << "Choose your option : ";
        std::cin >> turn;
        std::cout << std::endl;
    }
    system("clear");
    }
    else
    {
        if (whoplay() == 1)
            turn = 1;
        else
            turn = 2;
    }
    this->show();

    while (this->redwin() == 0 && this->yellowwin() == 0)
    {
        if (turn == 1)
        {
            std::cout << "RED : ";
            std::cin >> nb;
            system("clear");
            while (nb < 1 || nb > 5 || _redend[nb] == true)
            {
                system("clear");
                this->show();
                std::cout << "UNAVAILABLE | Choose your option for RED turn : ";
                std::cin >> nb;
                std::cout << std::endl;
                system("clear");
            }
            this->move_red(nb);
        }
        if (turn == 2)
        {
            std::cout << "YELLOW : ";
            std::cin >> nb;
            system("clear");
            while (nb < 1 || nb > 5 || _yellowend[nb] == true)
            {
                system("clear");
                std::cout << "UNAVAILABLE | Choose your option for YELLOW turn : ";
                std::cin >> nb;
                std::cout << std::endl;
                system("clear");
            }
            this->move_yellow(nb);
        }
        this->show();
    if (turn == 2)
        turn = 1;
    else
        turn = 2;
    }
}

void Squadro::bot_play()
{
    int turn = 0;
    int nb = 0;
    int auton = 0;
    if (_fen == "")
    {
    std::cout << "Who start? (1 or 2)" << std::endl;
    std::cout << 1 << ": Red" << std::endl;
    std::cout << 2 << ": Yellow" << std::endl;
    std::cin >> turn;
    std::cout << std::endl;
    while (turn < 1 || turn > 2)
    {
        std::cout << "Choose your option : ";
        std::cin >> turn;
        std::cout << std::endl;
    }
    if (turn == 1)
        auton = 2;
    else
        auton = 1;
    system("clear");
    }
    else
    {
        if (whoplay() == 1)
        {
            turn = 1;
            auton = 2;
        }
        else
        {
            turn = 2;
            auton = 1;
        }
    }
    this->show();

    while (this->redwin() == 0 && this->yellowwin() == 0)
    {
        if (turn == 1)
        {
            std::cout << "RED : ";
            if (auton == 2)
            {
            std::cin >> nb;
            system("clear");
            while (nb < 1 || nb > 5 || _redend[nb] == true)
            {
                system("clear");
                this->show();
                std::cout << "UNAVAILABLE | Choose your option for RED turn : ";
                std::cin >> nb;
                std::cout << std::endl;
                system("clear");
            }
            }
            else
            {
                nb = this->find_best_rmove(_fen);
                std::cout << nb << std::endl;
            }
            this->move_red(nb);
        }
        if (turn == 2)
        {
            std::cout << "YELLOW : ";
            if (auton == 1)
            {
            std::cin >> nb;
            system("clear");
            while (nb < 1 || nb > 5 || _yellowend[nb] == true)
            {
                system("clear");
                std::cout << "UNAVAILABLE | Choose your option for YELLOW turn : ";
                std::cin >> nb;
                std::cout << std::endl;
                system("clear");
            }
            }
            else
            {
                nb = this->find_best_ymove(_fen);
                std::cout << nb << std::endl;
            }
            this->move_yellow(nb);
        }
        this->show();
    if (turn == 2)
        turn = 1;
    else
        turn = 2;
    }
}