#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

#define RED "\033[1;31m"
#define YELLOW "\033[1;33m"
#define RESET "\033[0m"
#define GREEN "\033[1;32m"


class Squadro {
    private:
        int _red[6];
        bool _redend[6];
        bool _yellowend[6];
        int _yscore[6];
        int _rscore[6];
        int _yellow[6];
        int _redmoves[6];
        int _yellowmoves[6];
        int _gameboard[7][7];
        std::string _fen;
    public:
        Squadro();
        void menu();
        Squadro operator=(Squadro& other);
        Squadro(Squadro &a);
        ~Squadro();
        int scorered();
        int whoplay();
        int AI_redscore(std::string game);
        int scoreyellow();
        int AI_yellowscore(std::string game);
        void show();
        void friend_play();
        void bot_play();
        void auto_play();
        
        int move_yellow(int nb);
        int move_yellow_one(int nb);
        void reset_red(int nb);
        int redwin();

        int move_red(int nb);
        int move_red_one(int nb);
        int find_best_rmove(std::string fen);
        int find_best_ymove(std::string fen);
        void reset_yellow(int nb);
        int yellowwin();

        // AI PART
        int find_best_move(std::string fen);
        void reset(std::string game);
        void reset();
        // int find_best_yellowmove();
}; // RED IS 1 and YELLOW IS 2