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
  int y, x;  // 往下是正, 往右是正
};

void PrintTitle();
void SkipSpace(std::string &str);
std::string ReadInput();

// Class Declaration
class Stack{
 private:
  struct StackNode{ 
    Coordinate coordinate_item; // a coordinate(x, y)is an coordinate_item
    StackNode *next;
  }; // end StackNode
  StackNode *topPtr;
 public:
  Stack() {
    topPtr = nullptr;
  }
  Stack(const Stack& aStack) {
    if (aStack.topPtr == NULL) {
      topPtr = NULL; // original list is empty
    } else {
      topPtr = new StackNode;
      topPtr->coordinate_item = aStack.topPtr->coordinate_item;
      StackNode *newPtr = topPtr;
      for (StackNode *origPtr = aStack.topPtr->next; origPtr != NULL; origPtr = origPtr->next) {
         newPtr->next = new StackNode;
        newPtr = newPtr->next;
        newPtr->coordinate_item = origPtr->coordinate_item;
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
  void push(const Coordinate& newcoordinate_Item) {
    try { 
        StackNode *newPtr = new StackNode;
        newPtr->coordinate_item = newcoordinate_Item;
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
      stackTop = topPtr->coordinate_item;
    }
  }
  void pop(Coordinate& stackTop) {
    if (!isEmpty()) {
      stackTop = topPtr->coordinate_item;
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
  bool can_go_to_goal = false;
  int maze_rows;
  int maze_columns;
 public:
    Maze() {}
    ~Maze() {
      resetMaze();
    }
    void resetMaze() {
      for (int i = 0; i < maze_rows; i++) {
        delete[] maze_grid[i];
        delete[] visited_grid[i];
        delete[] route_grid[i];
      }
      delete[] maze_grid;
      delete[] visited_grid;
      delete[] route_grid;
      can_go_to_goal = false;
    }
    bool fetchFile() {
      std::ifstream in;
      std:: cout << "Input a file number: ";
      std::string file_num = ReadInput();
      std::string txt_path = "input" + file_num + ".txt";
      in.open(txt_path);
      if(in.fail()){ 
        std::cout << std::endl << txt_path + " does not exist!\n";
        return false; 
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
      return true;
    }
    void bestroutine(Stack path) {
      
      Coordinate temp_coor;
      
      while (!path.isEmpty()) {
        path.getTop(temp_coor);
        route_grid[temp_coor.y][temp_coor.x] = 'R';
        path.pop();
      }
    }
    void Dfs() { // for task 1
      Stack path;
      Coordinate start;
      start.y = 0;
      start.x = 0;// y first, then x    
      path.push(start);  
      int dx[4] = {1, 0, -1, 0}; // 右下左上
      int dy[4] = {0, 1, 0, -1};  
  
      int dir = 0; //右邊開始
    
      while (!path.isEmpty()) {
        Coordinate cur;
        path.getTop(cur);
        
        if (visited_grid[cur.y][cur.x] == 'G') {
          can_go_to_goal = true;
          if (!path.isEmpty())  {
            path.pop();
          }
          bestroutine(path);
          
          return;
        }
        visited_grid[cur.y][cur.x] = 'V';
        bool moved = false;
        for (int i = 0; i < 4; i++) {
          int ndir = (dir + i) % 4;
          
          int nx = cur.x + dx[ndir];
          int ny = cur.y + dy[ndir];
          
          if ((0 <= nx && nx < maze_columns) && (0 <= ny && ny < maze_rows) && (visited_grid[ny][nx] != 'V') && (visited_grid[ny][nx] != 'O')) {
            Coordinate temp;
            temp.y = ny;
            temp.x = nx;
            dir = ndir;
            if (visited_grid[temp.y][temp.x] == 'G') {
              can_go_to_goal = true;
              bestroutine(path);
              return;
            } else {
              visited_grid[temp.y][temp.x] = 'V';
            }
       
            path.push(temp);
            moved = true;
            break;
          }
        }
        if (!moved) {
          path.pop();
        }


      }
      can_go_to_goal = false;
  
    }
    void taskOne() { // 從左上角出發(依照指定行走模式)走到目標 G 的一條路徑
      Dfs();
      for (int i = 0; i < maze_rows; i++) {
        for (int j = 0; j < maze_columns; j++) {
          std::cout << visited_grid[i][j];
        }
        printf("\n");
      } 
      printf("\n");
      if (can_go_to_goal) {
        for (int i = 0; i < maze_rows; i++) {
          for (int j = 0; j < maze_columns; j++) {
            std::cout << route_grid[i][j];
          }
          printf("\n");
        } 
        
      }
      


    }

    void taskTwo() { // 從左上角出發(依照指定行走模式)走過 N 個目標的一條路徑
        
    }

    void taskThree() { // 從左上角出發(依照指定行走模式)走過所有目標 G 以計算總數
        
    }

    void taskFourne() { // 從左上角出發走到目標 G 的一條最短路徑
        
    }
};
int main() {
  Maze maze1; // for task1, 2, 3
  bool maze1_is_empty = true;
  while (true) {
    
    
    PrintTitle();
    std::string cmd = ReadInput();
    printf("\n");
    if (cmd == "0") {
      return 0;
    } else if (cmd == "1") {
      if (!maze1_is_empty) maze1.resetMaze();
      if (maze1.fetchFile()) {
        maze1_is_empty = false;
        maze1.taskOne();
      }
      
    } else if (cmd == "2") {
      
    } else if (cmd == "3") {
      
      
    } else if (cmd == "4") {
      
    } else {
      std::cout << "Command does not exist!\n";
    }
    printf("\n");  
  }

}

std::string ReadInput() {
  std::string input;
  while (1) {
    std::getline(std::cin, input);
    SkipSpace(input);
    if (input.empty()) continue;
    else break;
  }
  return input;
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
