#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"
#include "score.h"
#include "memory"
int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};
  
  int a = 1;
  while(a)
  {
    std::unique_ptr<Score> score = std::make_unique<Score>();
    switch(score->GetMode()) {
        case 1: {
            // Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
            // Controller controller;
            // Game game(kGridWidth, kGridHeight);
            // game.Run(controller, renderer, kMsPerFrame);
            // score.AddNewScore(game.GetScore());
            break;
        }
        case 2: {
            //score.PrintPlayer();
            break;
        }
        default: {
            a = 0; // quit game
        }
    }
  }

  // end
  return 0;
}