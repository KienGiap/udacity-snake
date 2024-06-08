#ifndef SCORE_H
#define SCORE_H

#include "sstream"
#include "fstream"
#include "iostream"
#include "vector"
#include "deque"
#include "cassert"
#include "string"
#include "vector"

#define MAX_USER 5

typedef struct DATABASE {
    std::string user;
    int score;
} T_user;

class Menu {
    public:
        virtual void PrintPlayer() = 0;
        virtual void PrintMenu() = 0;
        void SetStartGame(bool x) { startGame = x;}
        bool GetStartGame() { return startGame; }
        void SetMenu(int menu) {this->menu = menu;}
        int GetMenu() { return menu; }
    private:
        int menu;
        static bool startGame; //is startgame the first time
};

class Score : public Menu {
    public:
        Score() {};
        Score(std::string const& directory);
        ~Score();
        void AddNewScore(int const &score);
        void PrintMenu() override;
        void PrintPlayer() override;
        void ClearDataBase();
        
    private:
        void LoadToRam(std::string keyword,std::string value);

        std::deque<T_user> recentScore;
        static std::string currentName;
        T_user maxUsr;
        std::string filePath;
        const std::string usr = "username";
        const std::string val = "score";
};

#endif