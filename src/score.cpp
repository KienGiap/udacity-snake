
#include "score.h"
#include "limits"

bool Menu::startGame = false;
std::string Score::currentName = "default";
void Score::PrintMenu() {
    if(GetStartGame() == false) {
        std::cout << "!!! WELCOME TO SNAKE GAME !!!" << std::endl;
        std::cout << "Enter your name: ";
        std::getline(std::cin,currentName);
        SetStartGame(true);
    }
    std::cout << "\nValid options: 1 - 4 " << std::endl;
    std::cout << "1. start game" << std::endl;
    std::cout << "2. leader board" << std::endl;
    std::cout << "3. reset score" << std::endl;
    std::cout << "4. quit game" << std::endl;
    do {
       std::cout << "Enter------> ";
       int usrInput;
       std::cin >> usrInput;
       SetMenu(usrInput);
    } while (GetMenu() < 1 || GetMenu() > 4);   
}

void Score::LoadToRam(std::string keyword,std::string value) {
    if(keyword == (usr + "0")) {
        maxUsr.user = value;
    } else if (keyword == (val +"0")) {
        maxUsr.score = std::stoi(value);
    } else {
        static std::string recentUserName;
        if (keyword.find(usr) != std::string::npos) {
            recentUserName = value;       
        } else if (keyword.find(val) != std::string::npos) {
            T_user tempp = {recentUserName, std::stoi(value)};
            recentScore.push_back(tempp);
        }
    }
}
Score::Score(std::string const& directory) : filePath(directory) {
    // read data from file
    std::string line, keyword, value;
    std::ifstream file(filePath);
    if(file.is_open()) {
        while(getline(file,line)) {
            std::istringstream iss(line);
            iss >> keyword;
            value = line.substr(keyword.size() + 1);
            LoadToRam(keyword,value);
        }
    }
    file.close();
}
Score::~Score() {
    std::ofstream file(filePath);
    if(file.is_open()) {
        file << usr + "0" << " " <<maxUsr.user << '\n';
        file << val + "0" << " " << maxUsr.score << '\n';
        for(int i = 0; i < MAX_USER; i++) {
            file << usr << i+1 << " " << recentScore[i].user << '\n';
            file << val << i+1 << " " << recentScore[i].score << '\n';
        }
        file.flush();
    }
    file.close();
}
void Score::ClearDataBase() {
    // ask people enter yes
    std::string ans;
    std::cout << "are you sure? 'y': yes, 'n':no ---> ";
    std::cin >> ans;
    if(ans == "n") {
        return;
    } else if (ans == "y") {
        std::ofstream file(filePath);
        if(!file) {std::cout << "open failed" << std::endl;}
        if(file.is_open()) {
           // std::cout << "open success" << std::endl;
            file << usr + "0" << " " << "default" << '\n';
            file << val + "0" << " " << "0" << '\n';
            for(int i = 0; i < MAX_USER; i++) {
                file << usr << i+1 << " " << "no user" << '\n';
                file << val << i+1 << " " << "0" << '\n';
            }
            std::cout << "clear success" << std::endl; // i dont know why program reach this, but not write to file
            file.flush();
        }
        file.close();
    }
}
void Score::AddNewScore(int const& score) {
    if(score > maxUsr.score) {
        maxUsr.score = score;
        maxUsr.user = currentName;
    }
    T_user temp = {currentName,score};
    recentScore.emplace_front(temp);
    if(MAX_USER <= recentScore.size()) {
        recentScore.pop_back();
    }
}

void Score::PrintPlayer(){
    std::cout << "=========================" << std::endl;
    std::cout << "MAX SCORE: " << maxUsr.score << " BY: "<< maxUsr.user << std::endl;
    for(int i = 0; i < MAX_USER; i++){
        std::cout << "usr#" << i + 1 << ": " << recentScore[i].user << " "<< "score: "<< recentScore[i].score << std::endl;
    }
    std::cout << "=========================" << std::endl;
}
