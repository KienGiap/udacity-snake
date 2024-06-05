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
        void PrintMenu();
        int GetMenu();
        std::string GetName() { return name; }
    private:
        int menu;
        std::string name; // current user name;
};

class Score : public Menu {
    public:
        Score();
        ~Score();
        void AddNewScore(int score);
        void PrintPlayer() override;
        int GetMode() { return mode; }
    private:
        void LoadToRam(std::string keyword,std::string value);
        int mode;
        std::deque<T_user> recentScore;
        std::string currentName = "default";
        T_user maxUsr;
        const std::string directory = "../Score.txt";
        const std::string usr = "username";
        const std::string val = "score";
};

#endif