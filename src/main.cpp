#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"
#include "menu.h"


void load_game(){
  std::cout<< "loading game"<<std::endl;
  std::this_thread::sleep_for(std::chrono::seconds(1));
}

int main() {
  std::thread t0(load_game);//Mingqi: assign a thread waiting to load this game
  t0.join();

  Menu menu;
  std::cout<< "--- Current highest score is: " << menu.ReadHScore()<< " ---"<<std::endl;
  menu.DisplayDifficultyMenu();
  int user_in;

  std::cin>>user_in;
  menu.SetDifficulty(user_in);

  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  int numberOfToxicFoods = menu.GetDifficulty(); //Mingqi: number of toxic food impacts by game difficulty setting
  Game game(kGridWidth, kGridHeight, numberOfToxicFoods);
  std::thread t1(&Game::cycleThroughPhases, &game);
  game.Run(controller, renderer, kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << game.GetScore() << "\n";
  std::cout << "Size: " << game.GetSize() << "\n";
  t1.detach();
  menu.HandleHScore(game);
  return 0;
}