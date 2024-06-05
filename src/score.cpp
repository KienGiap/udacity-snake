
#include "score.h"
#include "limits"
void Menu::PrintMenu() {
    std::cout << "!!! WELCOME TO SNAKE GAME !!!" << std::endl;
    std::cout << "Enter your name: ";
    std::getline(std::cin,name);
    std::cout << "Valid options: 1 - 3 " << std::endl;
    std::cout << "1. start game" << std::endl;
    std::cout << "2. leader board" << std::endl;
    std::cout << "3. quit game" << std::endl;
    do {
       std::cout << "Enter------> "; 
       std::cin >> menu;
    } while (menu < 1 || menu > 3);
    
}
int Menu::GetMenu() {
    Menu::PrintMenu(); 
    return menu; 
}

void Score::LoadToRam(std::string keyword,std::string value) {
    if(keyword == (usr + "0")) {
        maxUsr.user = value;
    } else if (keyword == (val +"0")) {
        maxUsr.score = std::stoi(value);
    } else {
        static std::string temp;
        if (keyword.find(usr) != std::string::npos) {
            temp = value;       // TODO 
        } else if (keyword.find(val) != std::string::npos) {
            T_user tempp = {temp, std::stoi(value)};
            recentScore.push_back(tempp);
        }
    }
}
static int count = 0;
Score::Score() : mode(1), currentName("Menu::GetName()") {
    // read data from file
    std::string line, keyword, value;
    std::ifstream file(directory);
    if(file.is_open()) {

        while(getline(file,line)) {
            std::istringstream iss(line);
            iss >> keyword;
            value = line.substr(keyword.size() + 1);
            count ++;
            LoadToRam(keyword,value);
        }
        std::cout << "count:" << count  << std::endl;
    }
    file.close();
    // choose menu

}
Score::~Score() {
    std::ofstream file(directory);
    if(file.is_open()) {
        file << usr + "0" << " " <<maxUsr.user << '\n';
        file << val + "0" << " " << maxUsr.score << '\n';
        for(int i = 0; i < MAX_USER; i++) {
            file << usr << i+1 << " " << recentScore[i].user << '\n';
            file << val << i+1 << " " << recentScore[i].score << '\n';
        }
    }
    file.close();
}
void Score::AddNewScore(int score) {
    if(score > maxUsr.score) {
        maxUsr.score = score;
        maxUsr.user = currentName;
    }
    T_user temp = {currentName,score};
    recentScore.push_front(temp);
    if(MAX_USER <= recentScore.size()) {
        recentScore.pop_back();
    }
}

void Score::PrintPlayer(){
     std::cout << "max"<< " " << maxUsr.score << " "<< maxUsr.user << std::endl;
    for(int i = 0; i < MAX_USER; i++){
        std::cout << "username#" << i + 1 << ": " << recentScore[i].user << " "<< "score: "<< recentScore[i].score << std::endl;
    }
}

int main() {
    // while(1) {
    //     Score a;
    //     a.PrintPlayer();
    // }
    Score a;
    Score b;
    a.PrintPlayer();
    b.PrintPlayer();
    return 0;
}