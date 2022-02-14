#include "Squadro.hpp"

#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
// lib for usleep
#include <unistd.h>
// include for sleep
// include lib for ofstream
#include <fstream>

int main(void)
{
    int nb = 0;
    int temp = 0;
    int v = 0;
    int count = 0;
    Squadro a;
    system("clear");
    a.show();

    // show a prompt to choose what point to move
    // ask question and answer with y or n
    std::cout << "\nAuto-move y or manual-move n ? (y/n)" << std::endl;
    std::string answer;
    std::cin >> answer;
    if (answer == "y")
    {
        while (1)
        {
            count = 0;
        // generate a random num between 1 and 5
        // move the point to that num
        // if the point is not in the end, ask to move again
        system("clear");
        while (1)
        {
            std::ofstream myfile;
            myfile.open("count.txt", std::ios::app);
            if (temp == 0)
            {
                int nb = 0;
                srand(time(NULL));
                nb = rand() % 5 + 1;
                while (a.move_red(nb) == 1)
                {
                    nb = rand() % 5 + 1;
                    myfile << "r:" << nb;
                }
                count++;
                a.show();
                std::cout << std::endl << "Moving red " << nb << std::endl << std::endl;
                std::cout << "Games played : " << v << std::endl;
                temp = 1;
            }
            else
            {
                int nb = 0;
                // use time to random rand()
                srand(time(NULL));

                nb = rand() % 5 + 1;
                while (a.move_yellow(nb) == 1)
                {
                    nb = rand() % 5 + 1;
                    myfile << "y:" << nb;
                }
                count++;
                a.show();
                std::cout << std::endl << "Moving yellow " << nb << std::endl << std::endl;
                std::cout << "Games played : " << v << std::endl;
                temp = 0;
            }
            if (a.redwin() == 1)
            {
                a.show();
                std::cout << "\nRED WIN" << std::endl;
                    v++;
                a.reset();
                myfile << "R" << std::endl;
                count = 0;
            }
            if (a.yellowwin() == 1)
            {
                a.show();
                std::cout << "\nYELLOW WIN" << std::endl;
                    v++;
                a.reset();
                // add a line in count.txt containing the count var 
                myfile << "Y" << std::endl;
                count = 0;
            }
            // sleep 1 second
            // touch to continue
            // std::cout << "Touch to show" << std::endl;
            // std::cin.ignore();
            // std::cin.get();
            usleep(20000);
            system("clear");
        if (v > 100)
        {
            exit(0);
        }
        }
        }
    }
    else
    {
        while (1)
        {
            if (nb == 1)
            {
                std::cout << "\nYELLOW move: (y to find best move)\n";
                nb = 0;
            }
            else
            {
                std::cout << "\nRED move: (y to find best move)\n";
                nb = 1;
            }
            int up;
            std::cin >> up;
            // if cin is 'y', find the best move
            if (up == 'y')
            {
                if (nb == 1)
                    std::cout << "Here is the best red move : " << a.find_best_redmove() << std::endl;

                // else
                //     a.find_best_yellowmove();
            }
            else
            {
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
            }
            a.show();
        }
    }
}