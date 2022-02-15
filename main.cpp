#include "Squadro.hpp"

#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
// lib for usleep
#include <unistd.h>
// include for sleep
// include lib for ofstream
#include <fstream>

std::string getlastline(std::string filename)
{
    std::ifstream file(filename);
    std::string line;
    std::string lastline;
    while (std::getline(file, line))
    {
        lastline = line;
    }
    return lastline;
}

int alreadyexist(std::string filename, std::string line)
{
    std::ifstream file(filename);
    std::string line2;
    while (std::getline(file, line2))
    {
        if (line2 == line)
        {
            return (1);
        }
    }
    return (0);
}

void go_deep()
{
    Squadro a;

    int temp = 0;
    int v = 0;
    int win = 0;
    int nb = 0;
    std::ofstream myfile;
    myfile.open("DeepLearning.txt", std::ios::app);
    std::string game = "";
    while (1)
    {
        sranddev();
        //usleep(10000);
        nb = rand() % 5 + 1;
        // std::cout << "Vasy genere: " << nb << std::endl;
        if (temp == 0) // move red
        {
            sranddev();
            nb = rand() % 5 + 1;
            while (a.move_red(nb) == 1)
            {
                //std::cout << "Couldnt move red with nb: " << nb << "Here GAME: " << game << std::endl;
                //sleep (10);
                sranddev();
                nb = rand() % 5 + 1;
            }
            game += "r" + std::to_string(nb);
        }
        if (temp == 1) // move yellow
        {
            sranddev();
            nb = rand() % 5 + 1;
            while (a.move_yellow(nb) == 1)
            {
                sranddev();
                nb = rand() % 5 + 1;
            }
            game += "y" + std::to_string(nb);
        }
        if (a.redwin() == 1)
        {
            v++;
            a.reset();
            game += "R";
            win = 1;
        }
        if (a.yellowwin() == 1)
        {
            v++;
            a.reset();
            game += "Y";
            win = 1;
        }
        if (win == 1)
        {
            //std::cout << "ŸO\n" << std::endl;
            // if (alreadyexist("DeepLearning.txt", game) == 0)
            // {
                myfile << game << std::endl;
                //std::cout << game << std::endl;
                std::cout << "Games played : " << v << std::endl;
            //     game = "";
            // }
            // else
            // {
            //     std::cout << "already exist" << std::endl;
            //     //std::cout << "\b\b\b\b\b\b\b\b\b\b\b\b\b";
            //     game = "";
            // }
            win = 0;
        }
        if (temp == 0)
            temp = 1;
        else
            temp = 0;
    }
}

void Squadro::get_fen(std::string game)
{
    this->reset();
    int i = 0;
    while (game[i])
    {
        if (game[i] == 'r')
        {
            i++;
            this->move_red(game[i] - 48);
        }
        if (game[i] == 'y')
        {
            i++;
            this->move_yellow(game[i] - 48);
        }
        i++;
    }
    // sq->show();
}

std::string remove_lastmove(std::string game)
{
    // remove the last 2 chars in game string and return it
    std::string newgame = "";
    int i = 0;
    while (game[i])
    {
        i++;
    }
    game[i - 1] = '\0';
    game[i - 2] = '\0';
    return(game);
}

int main(void)
{
    int nb = 0;
    int temp = 0;
    int v = 0;
    int count = 0;
    std::string game;
    int out = 0;
    Squadro a;
    system("clear");
    a.show();

    // show a prompt to choose what point to move
    // ask question and answer with y or n
    std::cout << "Do you want to start with an FEN ? (y/n)" << std::endl;
    std::string answer;
    std::cin >> answer;
    if (answer == "y")
    {
        std::cout << "Enter the FEN: " << std::endl;
        std::string fen;
        std::cin >> fen;
        a.get_fen(fen);
        a.show();
        sleep (10);
        exit (1);
    }

        else 
        {
    std::cout << "\nTraining DeepLearning (y) or manual-move (n) ? (y/n)" << std::endl;
    std::string answer;
    std::cin >> answer;
    if (answer == "y")
    {
        std::string answer2;
        std::cout << "Do you want to train with the gameboard output ? (y/n)" << std::endl;
        std::cin >> answer2;
        if (answer2 == "n")
        {
            go_deep();
            exit(0);
        }
        else
        {
            out=1;
        }
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
                myfile.open("DeepLearning.txt", std::ios::app);
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
                    if (out == 1)
                    {
                        a.show();
                        std::cout << std::endl
                                  << "Moving red " << nb << std::endl
                                  << std::endl;
                        usleep(550000);
                    }
                    if (out == 1)
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
                    if (out == 1)
                    {
                        a.show();
                        std::cout << std::endl
                                  << "Moving yellow " << nb << std::endl
                                  << std::endl;
                        usleep(550000);
                    }
                    if (out == 1)
                        std::cout << "Games played : " << v << std::endl;
                    temp = 0;
                }
                if (a.redwin() == 1)
                {
                    if (out == 1)
                    {
                        a.show();
                        std::cout << "\nRED WIN" << std::endl;
                    }
                    v++;
                    a.reset();
                    // myfile << "R" << std::endl;
                    // std::string line;
                    // line = getlastline("DeepLearning.txt");
                    // if (alreadyexist("DeepLearning.txt", line) == 1)
                    // {
                    //     std::ofstream myfile;
                    //     std::cout << "The line already exist" << std::endl;
                    //     myfile.open("DeepLearning.txt", std::ios::app);
                    //     // touch to delete line
                    //     std::cin.get();
                    //     // delete the last line
                    //     myfile.seekp(-line.length() - 1, std::ios_base::end);
                    // }
                    count = 0;
                }
                if (a.yellowwin() == 1)
                {
                    if (out == 1)
                    {
                        a.show();
                        std::cout << "\nYELLOW WIN" << std::endl;
                    }
                    v++;
                    a.reset();
                    myfile << "Y" << std::endl;
                    // get the last line of the file and put it in line
                    // std::string line;
                    // line = getlastline("DeepLearning.txt");
                    // if (alreadyexist("DeepLearning.txt", line) == 1)
                    // {
                    //     std::ofstream myfile;
                    //     std::cout << "The line already exist" << std::endl;
                    //     myfile.open("DeepLearning.txt", std::ios::app);
                    // }

                    count = 0;
                }
                if (out == 1)
                {
                    usleep(20000);
                    system("clear");
                }
                else
                {
                    // sleep(1);
                    std::cout << "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b";
                    if (v < 10)
                        std::cout << "\b";
                    if (v < 100)
                        std::cout << "\b\b";
                    if (v < 1000)
                        std::cout << "\b\b\b";
                    if (v < 10000)
                        std::cout << "\b\b\b\b";
                    if (v < 100000)
                        std::cout << "\b\b\b\b\b";
                    if (v < 1000000)
                        std::cout << "\b\b\b\b\b\b";
                    if (v < 10000000)
                        std::cout << "\b\b\b\b\b\b\b";
                    std::cout << "Games played : " << v;
                }
                // if (v > )
                // {
                //     exit(0);
                // }
            }
        }
    }
    else
    {
            game = "";
        while (1)
        {
            if (nb == 1)
            {
                std::cout << "\nYELLOW move: (8 to find best move)\n";
                nb = 0;
            }
            else
            {
                std::cout << "\nRED move: (8 to find best move)\n";
                nb = 1;
            }
            int up;
            std::cin >> up;
            // if cin is 'y', find the best move
            // if up is 1, find the best move
            if (up == 9)
            {
                // std::cout << "game: " << game << std::endl;
                // sleep(10);
                if (game != "")
                {
                    std::cout << "Cancel move..." << std::endl;
                    sleep (2);
                    a.reset();
                    game = remove_lastmove(game);
                    // std::cout << "game after: " << game << std::endl;
                    // sleep (10);
                    a.get_fen(game);
                    // sleep (2);
                    system("clear");
                    a.show();
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
                    up=0;
                    std::cin >> up;
                }
            }
            if (up == 8)
            {
                std::cout << "finding the best move for : " << game << " ..." << std::endl;
                std::cout << a.find_best_move(game) << std::endl;
                std::cout << "done" << std::endl;
                sleep (1);
                std::cin >> up;
                // else
                //     a.find_best_yellowmove();
            }
            // else
            // {
                if (nb == 1)
                {
                    while (a.move_red(up) == 1)
                    {
                        nb = 0;
                        std::cout << "ERROR: Choose a valid point to move: ";
                        std::cin >> up;
                    }
                    // b = a;
                    game += "r" + std::to_string(up);
                }
                else
                {
                    while (a.move_yellow(up) == 1)
                    {
                        nb = 0;
                        std::cout << "ERROR: Choose a valid point to move: ";
                        std::cin >> up;
                    }
                    // b = a;
                    game += "y" + std::to_string(up);
                }
                if (a.yellowwin() == 1)
                {
                    std::cout << "YELLOW WIN" << std::endl;
                    a.reset();
                    std::cout << "FEN : " << game << std::endl;
                    exit(0);
                }
                if (a.redwin() == 1)
                {
                    std::cout << "RED WIN" << std::endl;
                    a.reset();
                    std::cout << "FEN : " << game << std::endl;
                    exit(0);
                }
            // }
            a.show();
            if (nb == 1)
                std::cout << "\nScore RED : " << a.AI_redscore()-1 << " Score YELLOW : " << a.AI_yellowscore()+1 << std::endl;
            else
                std::cout << "\nScore RED : " << a.AI_redscore() << " Score YELLOW : " << a.AI_yellowscore() << std::endl;
        }
    }
}
}