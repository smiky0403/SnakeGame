#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL.h"
#include "snake.h"
#include "toxic.h"

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  void Render(Snake const snake, SDL_Point const &food, SDL_Point const &boost, bool flag,
  const std::shared_ptr<ToxicFood> toxicfoods);
  void UpdateWindowTitle(int score, int fps);
  //Mingqi:Shared pointer
  void placeToxicFoods(const std::shared_ptr<ToxicFood> toxicfoods) const;
  

 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
};

#endif