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
    Game game(kGridWidth, kGridHeight,directory);
    game.gameScore->PrintMenu();
    switch(game.gameScore->GetMenu()) {
        case 1: {
            Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
            Controller controller;
            game.Run(controller, renderer, kMsPerFrame);
            game.gameScore->AddNewScore(game.GetScore());
            break;
        }
        case 2: {
            game.gameScore->PrintPlayer();
            break;
        }
        case 3:
            game.gameScore->ClearDataBase(); // not sure why this code fail
            break;
        default: {
            quitflag = 0;     // case 4: quit game
            break;
        }
    }
  }
  std::cout << "Good bye !" << std::endl;
  // end
  return 0;
}