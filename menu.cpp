#include "Squadro.hpp"

void Squadro::menu()
{
    int answer = 0;
    std::cout << "FEN : " << YELLOW << _fen << RESET << std::endl << std::endl;
    std::cout << "1. Play with a friend" << std::endl;
    std::cout << "2. Play with a bot" << std::endl;
    std::cout << "3. Auto-Play" << std::endl;
    std::cout << "4. Start with a FEN" << std::endl;
    std::cout << "5. Quit" << std::endl;
    std::cout << "Choose your option : ";
    std::cin >> answer;
    std::cout << std::endl;
    while (answer < 1 || answer > 5)
    {
        std::cout << "Choose your option : ";
        std::cin >> answer;
        std::cout << std::endl;
    }
    if (answer == 4)
    {
        std::cout << "FEN : ";
        std::string fen;
        std::cin >> fen;
        reset(fen);
        system("clear");
        menu();
    }
    if (answer == 1)
        friend_play();
    if (answer == 2)
        bot_play();
    if (answer == 3)
        auto_play();
    if (answer == 4)
        exit(0);
}