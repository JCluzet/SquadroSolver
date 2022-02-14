#include <iostream>

class Squadro {
    private:
        int _red[6];
        bool _redend[6];
        bool _yellowend[6];
        int _yellow[6];
        int _redmoves[6];
        int _yellowmoves[6];
        int _gameboard[7][7];
    public:
        Squadro();
        Squadro(const Squadro &a);
        ~Squadro();
        void show();
        
        int move_yellow(int nb);
        int move_yellow_one(int nb);
        void reset_red(int nb);
        int redwin();

        int move_red(int nb);
        int move_red_one(int nb);
        void reset_yellow(int nb);
        int yellowwin();

        // AI PART
        int find_best_redmove();
        void reset();
        // int find_best_yellowmove();
}; // RED IS 1 and YELLOW IS 2