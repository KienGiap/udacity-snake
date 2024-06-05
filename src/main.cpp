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
  const std::string directory = "../Score.txt";
  bool quitflag = 1;
  while(quitflag)
  {
    std::unique_ptr<Score> score = std::make_unique<Score>(directory);
    
    score->PrintMenu();
    
    switch(score->GetMode()) {
        case 1: {
            Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
            Controller controller;
            Game game(kGridWidth, kGridHeight);
            game.Run(controller, renderer, kMsPerFrame);
            score->AddNewScore(game.GetScore());
            break;
        }
        case 2: {
            score->PrintPlayer();
            break;
        }
        case 3:
            score->ClearDataBase(); // not sure why this code fail
            break;
        default: {
            quitflag = 0;     // case 4: quit game
            break;
        }
    }
  }
  std::cout << "Good byte" << std::endl;
  // end
  return 0;
}