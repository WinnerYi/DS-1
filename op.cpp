//11327217 蔡易勳     11327222 林瑋倫 
#include <iostream>
#include <string>
#include <fstream>
void PrintTitle ();
void SkipSpace(std::string &str);
// Class Declaration
class Maze {
 public:
    Maze() {
      
    }

    ~Maze() {
      
    }


    void taskOne(std::string file_num) { // 從左上角出發(依照指定行走模式)走到目標 G 的一條路徑
      std::ifstream in;
      std::ofstream out;
      std::string txt_path = "input" + file_num + ".txt";
      in.open(txt_path);
      if(in.fail()){ 
        std::cout <<  txt_path + "does not exist!";
        return; 
      }
      std::string res;
      in >> res;
      std::cout << res;
      


    }

    void taskTwo() { // 從左上角出發(依照指定行走模式)走過 N 個目標的一條路徑
        
    }

    void taskThree() { // 從左上角出發(依照指定行走模式)走過所有目標 G 以計算總數
        
    }

    void taskFourne() { // 從左上角出發走到目標 G 的一條最短路徑
        
    }
};
int main() {
  while (true) {
    Maze m;
    std::string cmd, file_num;
    PrintTitle();
    std::getline(std::cin, cmd);
    printf("\n");
    SkipSpace(cmd);
    if (cmd == "0" || cmd.empty()) {
      return 0;
    } else if (cmd == "1") {
      std:: cout << "Input a file number: ";
      std::getline(std::cin, file_num);
      printf("\n");
      SkipSpace(file_num);
      m.taskOne(file_num);
      
    } else if (cmd == "2") {
      
    } else if (cmd == "3") {
      
      
    } else if (cmd == "4") {
      
    } else {
      std::cout << "Command does not exist!\n";
    }
    printf("\n");  
  }

}

void SkipSpace(std::string &str) {
  for (int i = 0; i < str.size(); i++) {
    if (str[i] != ' ') break;
    if (str[i] == ' ') {
      str.erase(str.begin() + i);
      i--;
    }
  }
  for (int i = str.size()-1; i >= 0; i--) {
    if (str[i] != ' ') break;
    if (str[i] == ' ') {
      str.erase(str.begin() + i);
    }
  }
}
void PrintTitle () {
  std::cout << "*** (^_^) Data Structure (^o^) ***\n";
  std::cout << "*** Find the Goal(s) in a Maze ***\n";
  std::cout << "* 0. Quit                        *\n";
  std::cout << "* 1. Find one goal               *\n";
  std::cout << "* 2. Find goal(s) as requested   *\n";
  std::cout << "* 3. How many goals?             *\n";    
  std::cout << "* 4. Shortest path to one goal   *\n";
  std::cout << "**********************************\n";
  std::cout << "Input a command(0, 1, 2, 3, 4): ";
} 
