#ifndef GAME_H
#define GAME_H

#include <random>
#include <thread>
#include <memory>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include "toxic.h"

class Game{
 public:
  Game(std::size_t grid_width, std::size_t grid_height,
  int numberOfToxcFoods);
  enum LightPhase{
    red = 0,
    green = 1,
  };
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  void SetScore(int score_in); //Mingqi: mostly unused
  int GetSize() const;
  LightPhase toggleLight();
  void cycleThroughPhases();
  LightPhase getCurrentPhase(){return _currentPhase;};
  bool getPaused(){return _paused;};//Mingqi
  void setPaused(bool pause_in){ _paused = pause_in;};//Mingqi
  bool _border = false;//Mingqi

 private:
  Snake snake;
  SDL_Point food;
  SDL_Point boost;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;
  

  int score{0};

  void PlaceFood();
  void PlaceBoost();//Mingqi
  void Update();//Mingqi
    
  bool _paused = false;//Mingqi
  LightPhase _currentPhase = LightPhase::green;
  
  //Mingqi:Shared pointer 
  std::shared_ptr<ToxicFood> _toxicfoods;
  void PlaceToxicFood();
  int _numberOftoxicfoods = 0;
  
};

#endif