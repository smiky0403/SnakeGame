#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <thread>
#include <mutex>
#include <chrono>
#include "snake.h"
//#include "game.h"

class Game;

class Controller {
 public:
  void HandleInput(bool &running, Snake &snake, Game &game) const;
  void test();

 private:
  void ChangeDirection(Snake &snake, Snake::Direction input,
                       Snake::Direction opposite, bool _paused) const;
  void Freeze(Snake &snake) const; //Mingqi
  void ResumeDirection(Snake &snake) const;//Mingqi
  std::mutex _mutex;
};

#endif