#include "game.h"
#include <iostream>
#include "SDL.h"
#include <thread>

Game::Game(std::size_t grid_width, std::size_t grid_height,std::string directory)
    : snake(grid_width, grid_height),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)) {
        
      gameScore = std::make_unique<Score>(directory);
      timeStamp = std::chrono::system_clock::now();
      PlaceFood();
}
void Game::UpdateFood() {
 
  while(snake.alive == 1 ) {
    std::this_thread::sleep_for(std::chrono::microseconds(1));
    std::random_device random;
    std::mt19937 eng(random());
    std::uniform_int_distribution<int> dist(LOWEST_RANDOM,HIGHEST_RANDOM);
    int lastUpdateTime = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - timeStamp).count();
    if(dist(eng) == lastUpdateTime) {
      std::unique_lock<std::mutex> lock(mtx);
      timeStamp = std::chrono::system_clock::now();
      PlaceFood();
    }
    if(destroyThread == 0) { return; } // return point when game has ended
  }
  
}
void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;
  // create thread t to change food every n second
  std::thread t(&Game::UpdateFood,this);
  destroyThread = true;
  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake);
    Update();
    renderer.Render(snake, food, obstacle);

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
    destroyThread = false; // destroy thread
    t.join();
}
void Game::Obstacle() {
  int x, y;
  bool clearFlag;
  clearFlag = false;
  while(1) {
    x = random_w(engine);
    y = random_h(engine);
    
    // we have to check obstacle is not infront snake, and not in food
    if(!snake.SnakeCell(x,y) && (x != food.x && y != food.y)) {
      SDL_Point obstacleTemp = {x,y};
      
      if(clearFlag == false) { // clear element before add new 
        obstacle.clear();
        clearFlag = true;
      }

      if(obstacle.size() < NUMBER_OF_OBSTACLE) {
        obstacle.emplace_back(obstacleTemp);

      } else if(obstacle.size() == NUMBER_OF_OBSTACLE) {
        return;
      }
    }
  }
}
void Game::PlaceFood() {
  int x, y;
  bool flagFood;
  //std::cout << "place food" << std::endl;
  while (true) {
    flagFood = false;
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    for(int i = 0; i < obstacle.size(); i++) {
      if (obstacle.at(i).x == x && obstacle.at(i).y == y) {
        flagFood = true;
      }
    }
    if (!snake.SnakeCell(x, y) && flagFood == false) {
      food.x = x;
      food.y = y;
      return;
    }
  }
}

void Game::Update() {
  if (!snake.alive) return;

  snake.Update();

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  // Check if there's food over here
  if (food.x == new_x && food.y == new_y) {
    std::unique_lock<std::mutex> lock(mtx);
    score++;
    PlaceFood();
    Obstacle();
    // Grow snake and increase speed.
    snake.GrowBody();
    snake.speed += 0.015;
  }
  for(auto const &obstacle : obstacle) { // obstacle kill snake
      if (new_x == obstacle.x && new_y == obstacle.y) {
        snake.alive = false;
      }
  }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }