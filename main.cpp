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

void Squadro::reset(std::string game)
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
    Squadro a;
    a.menu();
    return(0);
}