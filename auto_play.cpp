#include "Squadro.hpp"

void Squadro::auto_play()
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
            nb = this->find_best_rmove(_fen);
            std::cout << nb << std::endl;
            system("clear");
            this->move_red(nb);
        }
        if (turn == 2)
        {
            std::cout << "YELLOW : ";
            nb = this->find_best_ymove(_fen);
            std::cout << nb << std::endl;
            system("clear");
            this->move_yellow(nb);
        }
        this->show();
        sleep(2);
    if (turn == 2)
        turn = 1;
    else
        turn = 2;
    }
}