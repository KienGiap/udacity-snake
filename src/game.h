#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include <chrono>
#include "mutex"
#include <memory>
#define NUMBER_OF_OBSTACLE 3
#define LOWEST_RANDOM     6
#define HIGHEST_RANDOM    10
class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;
  
 private:
  Snake snake;
  SDL_Point food;
  std::vector<SDL_Point> obstacle;
  // change food
  std::chrono::system_clock::time_point timeStamp;
  std::mutex mtx;
  bool destroyThread;
  //
  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};

  void PlaceFood();
  void Obstacle();
  void UpdateFood();
  void Update();
};

#endif