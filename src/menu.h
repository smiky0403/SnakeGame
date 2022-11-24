//Mingqi:File User I/O implementation for menu selection
#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <fstream>
#include "game.h"


class Menu {
    public:
        Menu();
        void DisplayDifficultyMenu();
        void SetDifficulty(int difficulty);
        int GetDifficulty();

        int ReadHScore() const;
        void ResetHScore();//mostly unused
        void SetHScore(Game &game);
        void HandleHScore(Game &game);
        
        
    private:
        int _difficulty;

};


#endif 