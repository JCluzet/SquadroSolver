#include "Squadro.hpp"

#include <time.h>
#include <stdlib.h>
// include for sleep
#include <unistd.h>

int main(void)
{
    int nb = 0;
    int temp = 0;
    Squadro a;
    a.show();

    // show a prompt to choose what point to move
    // ask question and answer with y or n
    std::cout << "\nAuto-move y or manual-move n ? (y/n)" << std::endl;
    std::string answer;
    std::cin >> answer;
    if (answer == "y")
    {
        // generate a random num between 1 and 5
        // move the point to that num
        // if the point is not in the end, ask to move again
        system("clear");
        while (1)
        {
            if (temp == 0)
            {
                int nb = 0;
                nb = rand() % 5 + 1;
                std::cout << "Moving red " << nb << std::endl << std::endl;
                while (a.move_red(nb) == 1)
                {
                    nb = rand() % 5 + 1;
                }
                temp = 1;
            }
            else
            {
                int nb = 0;
                nb = rand() % 5 + 1;
                std::cout << "Moving yellow " << nb << std::endl << std::endl;
                while (a.move_yellow(nb) == 1)
                {
                    nb = rand() % 5 + 1;
                }
                temp = 0;
            }
            if (a.redwin() == 1)
            {
                a.show();
                std::cout << "\nRED WIN" << std::endl;
                return 0;
            }
            if (a.yellowwin() == 1)
            {
                a.show();
                std::cout << "\nYELLOW WIN" << std::endl;
                return 0;
            }
            // sleep 1 second
            // touch to continue
            // std::cout << "Touch to show" << std::endl;
            // std::cin.ignore();
            // std::cin.get();
            a.show();
            sleep(1);
            system("clear");

        }
    }
    else
    {
        while (1)
        {
            if (nb == 1)
            {
                std::cout << "\nYELLOW move: \n";
                nb = 0;
            }
            else
            {
                std::cout << "\nRED move: \n";
                nb = 1;
            }
            int up;
            std::cin >> up;
            if (nb == 1)
            {
                while (a.move_red(up) == 1)
                {
                    nb = 0;
                    std::cout << "ERROR: Choose a valid point to move: ";
                    std::cin >> up;
                }
            }
            else
            {
                while (a.move_yellow(up) == 1)
                {
                    nb = 0;
                    std::cout << "ERROR: Choose a valid point to move: ";
                    std::cin >> up;
                }
            }
            a.show();
        }
    }
}