//11327217 蔡易勳     11327222 林瑋倫 
#include <iostream>
#include <string>
#include <fstream>

/*
原始迷宮所採用的字符定義如下：
1. 字符'O'表示障礙物 (Obstacle)
2. 字符'E'表示空格 (Empty cell)
3. 字符'G'表示目標 (Goal)，抵達這個位置後，也視同一個可以行走的空格。
   程式輸出所採用的字符定義如下：
4. 字符'V'表示曾經走過的位置 (Visited)
5. 字符'R'表示成功可行的路徑 (Route)
*/
struct Coordinate {
  int x;
  int y;
};

void PrintTitle();
void SkipSpace(std::string &str);

// Class Declaration
class Stack{
 private:
  struct StackNode{ 
    Coordinate item; // a coordinate(x, y)is an item
    StackNode *next;
  }; // end StackNode
  StackNode *topPtr;
 public:
  Stack();
  Stack(const Stack& aStack) {
    if (aStack.topPtr == NULL) {
      topPtr = NULL; // original list is empty
    } else {
      topPtr = new StackNode;
      topPtr->item = aStack.topPtr->item;
      StackNode *newPtr = topPtr;
      for (StackNode *origPtr = aStack.topPtr->next; origPtr != NULL; origPtr = origPtr->next) {
         newPtr->next = new StackNode;
        newPtr = newPtr->next;
        newPtr->item = origPtr->item;
      } // end for
    newPtr->next = NULL;
    } // end if-else
  } // end copy construct
  
  ~Stack() {
    while (!isEmpty()) {
      pop();
    }
  }
  bool isEmpty() {
    return topPtr == NULL;
  }

  //bad_alloc 是 C++ 標準例外類別，當 new 失敗時會丟出這個例外。
  //用 catch (bad_alloc& e) 比 catch (bad_alloc e) 好，因為：
  //避免複製例外物件（效率更好）
  //確保多型行為正確
  //e.what() 會輸出錯誤訊息（通常是 "std::bad_alloc"）
  void push(const Coordinate& newItem) {
    try { 
        StackNode *newPtr = new StackNode;
        newPtr->item = newItem;
        newPtr->next = topPtr;
        topPtr = newPtr;
    } // end try
    catch (std::bad_alloc& e) {  // ← 用參考 (&)
        std::cerr << "記憶體配置失敗: " << e.what() << std::endl;
    } // end catch
}
  void pop() {
    if (!isEmpty()){ 
      StackNode *temp = topPtr;
      topPtr = topPtr->next;
      temp->next = NULL;
      delete temp;
    } // end if
  }
  void getTop(Coordinate& stackTop) {
    if (!isEmpty()) {
      stackTop = topPtr->item;
    }
  }
  void pop(Coordinate& stackTop) {
    if (!isEmpty()) {
      stackTop = topPtr->item;
      StackNode *temp = topPtr;
      topPtr = topPtr->next;
      temp->next = NULL;
      delete temp;
    } // end if
  }
}; // end Stack
class Maze {
 private:
  char **maze_grid; // 採用 C++標準函式 new 動態配置陣列以儲存迷宮。
  char **visited_grid;
  char **route_grid;
  
  int maze_rows;
  int maze_columns;
 public:
    Maze() {}
    ~Maze() {
      for (int i = 0; i < maze_rows; i++) {
        delete[] maze_grid[i];
        delete[] visited_grid[i];
        delete[] route_grid[i];
      }
      delete[] maze_grid;
      delete[] visited_grid;
      delete[] route_grid;

    }
    void fetchFile() {
      std::ifstream in;
      std::string file_num;
      std:: cout << "Input a file number: ";
      std::getline(std::cin, file_num);
      printf("\n");
      SkipSpace(file_num);
      std::string txt_path = "input" + file_num + ".txt";
      in.open(txt_path);
      if(in.fail()){ 
        std::cout <<  txt_path + "does not exist!";
        return; 
      }
      in >>  maze_columns >> maze_rows;
      maze_grid = new char*[maze_rows];
      visited_grid = new char*[maze_rows];
      route_grid = new char*[maze_rows];
      for (int i = 0; i < maze_rows; i++) {
        maze_grid[i] = new char[maze_columns];
        visited_grid[i] = new char[maze_columns];
        route_grid[i] = new char[maze_columns];
        for (int j = 0; j < maze_columns; j++) {
          in >> maze_grid[i][j];
          visited_grid[i][j] = maze_grid[i][j];
          route_grid[i][j] = maze_grid[i][j];
        }
      } 
      in.close();
    }
    bool Dfs(Maze &maze, int r, int c) {

  
  
    }
    void taskOne() { // 從左上角出發(依照指定行走模式)走到目標 G 的一條路徑
      
      


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
    Maze maze1; // for task1, 2, 3
    std::string cmd, file_num;
    PrintTitle();
    std::getline(std::cin, cmd);
    printf("\n");
    SkipSpace(cmd);
    if (cmd == "0" || cmd.empty()) {
      return 0;
    } else if (cmd == "1") {
      maze1.fetchFile();
      maze1.taskOne();
      
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
