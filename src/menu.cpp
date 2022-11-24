#include "menu.h"


Menu::Menu() { _difficulty = 0; };

int Menu::GetDifficulty()
{
    return _difficulty;
}

void Menu::SetDifficulty(int difficulty_in)
{
    if (difficulty_in > 0 && difficulty_in < 4)
    {
        _difficulty = difficulty_in - 1; 
    }
    else if(!std::cin){
        std::cout << "wrong input, choose game mode to be easy instead" << std::endl;
    }else
    {
        std::cout << "Invalid input, plese re-input a diffuclt level between 1 -3: " << std::endl;
        std::cin >> difficulty_in;
        this->SetDifficulty(static_cast<int>(difficulty_in));
    }
}

//Mingqi: pop up menu to console for player to select a level
void Menu::DisplayDifficultyMenu()
{
    std::cout << "----Select Game Difficulty Level----" << std::endl;
    std::cout << "1. Easy" << std::endl;
    std::cout << "2. Medium" << std::endl;
    std::cout << "3. Hard" << std::endl;
    std::cout << "Please choose: "<< std::endl;
}

//Mingqi: score will be read from game and store to a file, reset to 0 if the player want it
int Menu::ReadHScore() const{
    std::string line;
    std::ifstream myfile("../file/record.txt");
    if (myfile.is_open()){
    while (getline (myfile,line)){
    }
    myfile.close();
    }
    return stoi(line);
    };


void Menu::ResetHScore(){   //Mingqi: reset highest score to 0 on the file, mostly unused
    std::ofstream myfile;
    myfile.open ("../file/record.txt");
    myfile << "0";
    myfile.close();
    };

void Menu::SetHScore(Game &game){
    std::ofstream myfile;
    myfile.open ("../file/record.txt");
    myfile << std::to_string(game.GetScore());
    myfile.close();
    };

void Menu::HandleHScore(Game &game){
     if(this->ReadHScore() < game.GetScore() ){
        std::cout << "Congrated, you've achieve a new highest scored" << std::endl;
        std::cout << "New record: " << game.GetScore() << std::endl;
        this->SetHScore(game);
     }
};