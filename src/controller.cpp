#include "controller.h"
#include <iostream>
#include "snake.h"
#include "game.h"

//#include "SDL.h"

void Controller::ChangeDirection(Snake &snake, Snake::Direction input,
                                 Snake::Direction opposite, bool _paused) const {
  if ( (snake.direction != opposite || snake.size == 1 ) &&  !_paused) snake.direction = input;
  return;
}

//Mingqi: added Freeze function to freeze snake
void Controller::Freeze(Snake &snake) const {
  snake.direction = Snake::Direction::kFreeze;
  return;
}

//Mingqi: get Opposite direct of current direction, 
//use it when resume game, snake to recover the direction before freeze
void Controller::ResumeDirection(Snake &snake) const{
  if(snake.direction == Snake::Direction::kFreeze && snake.last_direction != Snake::Direction::kFreeze ){
    snake.direction = snake.last_direction;
}
}

void Controller::HandleInput(bool &running, Snake &snake, Game &game) const {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    } else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
        case SDLK_UP:
          ChangeDirection(snake, Snake::Direction::kUp,
                          Snake::Direction::kDown, game.getPaused());
          break;

        case SDLK_DOWN:
          ChangeDirection(snake, Snake::Direction::kDown,
                          Snake::Direction::kUp, game.getPaused());
          break;

        case SDLK_LEFT:
          ChangeDirection(snake, Snake::Direction::kLeft,
                          Snake::Direction::kRight, game.getPaused());
          break;

        case SDLK_RIGHT:
          ChangeDirection(snake, Snake::Direction::kRight,
                          Snake::Direction::kLeft, game.getPaused());
          break;

        //Mingqi: hit b to turn border on or off, once snake hit border, it dies
        //Mingqi: border inside game should also notice snake each time key b hitten
        case SDLK_b:
          if(!game.getPaused()){
            game._border ? game._border = false : game._border = true;
            snake._border = game._border; 
            if(game._border){
              std::cout << "border activated" << std::endl;
              }else{
              std::cout <<  "border deactivated" << std::endl;
            }
          }
          break;

        //Mingqi: add ESC key function to pause game: i.e freeze snakes and all other relevant elements
         //std::cout << t.
        case SDLK_ESCAPE:
          auto t1 = std::chrono::high_resolution_clock::now();
          long duration = 0;

          //std::cout <<t1 <std::endl;
          if(snake.direction != Snake::Direction::kFreeze){
            snake.last_direction = snake.direction;
          } //Make sure always record the snake direction before pause game
          
          if(!game.getPaused()){//hit ESC once to pause the game
             std::cout << "Game is paused"<<std::endl;
             Freeze(snake); 
             game.setPaused(true);
            }
            else{  //hit ESC again to resume the game
             std::cout << "Game is resumed"<<std::endl;
             ResumeDirection(snake);
            game.setPaused(false);
            }
          break;
      }
    }
  }
}