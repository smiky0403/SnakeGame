#include "game.h"
#include <iostream>
#include "SDL.h"

Game::Game(std::size_t grid_width, std::size_t grid_height, int numberOftoxicfoods)
    : snake(grid_width, grid_height),
      engine(dev()),
      _numberOftoxicfoods(numberOftoxicfoods),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)) {
  _toxicfoods = std::shared_ptr<ToxicFood>(new ToxicFood());
  PlaceFood();
  PlaceBoost();
  PlaceToxicFood();
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;
  bool flag = true;



  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake, *this);
    //bool flag_border = this->_border;
    Update();

    //Mingqi: add below section thread to toggle light of boost
    if(getCurrentPhase() == LightPhase::green){
      flag =true;
    }else{
      flag =false;
    }

    renderer.Render(snake, food, boost, flag, _toxicfoods);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y)) {
      food.x = x;
      food.y = y;
      return;
    }
  }
}

void Game::Update() {
  if (!snake.alive) return;
  //this->_border;
  //if(flag_border){}
  snake.Update();
 

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);
  // Check if there's food over here
  if (food.x == new_x && food.y == new_y) {
    score++;
    PlaceFood();
    // Grow snake and increase speed.
    snake.GrowBody();
    snake.speed += 0.02;
  }

  //Mingqi: key player game strategy here:  player need to balance between either: 
   //speed up the snake  or  grow the snake to get higher score
  if (boost.x == new_x && boost.y == new_y ) {
    if( this->getCurrentPhase()== LightPhase::green){ //score increase high by eating green since its elapse time are short
         score+=5;
         snake.speed += 0.05;  //Mingqi: snake increase lots of speed only
         PlaceBoost();
    }else{ //score increase low by eating green since its elapse time are higher
         score+=1;
         snake.speed += 0.01;  //Mingqi: snake increase lots of speed only
      PlaceBoost();
    }
  }

  ///Mingqi:Shared pointer Is the new cell a toxic food
  if ( _toxicfoods->Cell(Coord(new_x, new_y)) ) {
    std::cout << "you eat toxic food, game over" << std::endl;
    snake.alive = false;
    return;
  }


}

int Game::GetScore() const { return score; }
void Game::SetScore(int score_in) { this->score =score_in; } //Mingqi: mostly unused
int Game::GetSize() const { return snake.size; }

//Mingqi: global control on game booster
void Game::PlaceBoost() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y)) {
      boost.x = x;
      boost.y = y;
      return;
    }
  }
}
//Mingqi: Function below used below to switch light for boost, red and green make different effect
Game::LightPhase Game::toggleLight(){
    LightPhase _nextPhase = (_currentPhase == LightPhase::red)? green : red;
    return _nextPhase;
};

void Game::cycleThroughPhases(){
    std::chrono::time_point<std::chrono::system_clock> lastUpdate;
    lastUpdate= std::chrono::high_resolution_clock::now();
     while(true){
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        long timeSinceLastUpdate = 
        std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()
         - lastUpdate).count();  
         long phasetime = (_currentPhase == LightPhase::red)? 3000 : 1000;
         if( timeSinceLastUpdate > phasetime){
              _currentPhase = toggleLight();
              lastUpdate= std::chrono::high_resolution_clock::now();
         }
     }
};

//Mingqi:Shared pointer: place toxic food one by one
void Game::PlaceToxicFood() {

  if(_numberOftoxicfoods > 0){

    std::cout << "toxic food placed as white color, be careful don't hit!"<<std::endl;
  }
  
  int x, y;
  while (true) {
    /// Return if we meet the size requirements.

    if (_numberOftoxicfoods == _toxicfoods->size()) {
      return;
    }

    /// Randomly generate the x and y coordinate.

    x = random_w(engine);
    y = random_h(engine);

    // Check that the location is not occupied by
    // a (snake item + food item) before placing t.

    auto foodExists = food.x == x && food.y == y;
    auto boostExists = boost.x == x && boost.y == y;
    if ( !snake.SnakeCell(x, y) && !foodExists && !boostExists ) {
      _toxicfoods->addCoord(Coord(x, y));
    }

  }
}