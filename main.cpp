#include <iostream>
#include <array>

const char player { 'X' };
const char enemy { 'O' };

std::array<std::array<char, 3>, 3> board = {{
  {' ', ' ', ' '},
  {' ', ' ', ' '},
  {' ', ' ', ' '}
}};

void PrintBoard(const std::array<std::array<char, 3>, 3>& board) {
  for(size_t row = 0; row < board.size(); row++) {
    for(size_t col = 0; col < board.size(); col++) {
      std::cout << board[row][col] << " ";
      if(col < 2) {
        std::cout << "|";
      }
    }
    std::cout << "\n";
    if(row < 2) {
      std::cout << "--+--+--" << "\n";
    }
  }
}

bool PlayerInput(std::array<std::array<char, 3>, 3>& board) {
  bool output = false;
  char input;

  std::cout << "Select a cell (1-9): ";
  std::cin >> input;

  if(input == 'q' || input == 'Q') {
    output = false;
  }

  if(input != 'q' && input != 'Q') {
    int pos = input - '0';
    if(pos >= 0 && pos <= 9) {
        int index = pos - 1;
        int x = index / 3;
        int y = index % 3;
        if(board[x][y] == ' ') {
          board[x][y] = player;
        }
    } 
  }
  return output;
}

bool WinPositions(const std::array<std::array<char, 3>, 3>& board, char mark) {
  bool WinIsTrue = false;
  for(size_t x = 0; x < board.size(); x++) {
    if(board[x][x] == mark) {
      WinIsTrue = true;
      std::cout << "You Win!\n";
    }
  }
  for(size_t y = 0; y < board.size(); y++) {
    if(board[y][y] == mark) {
      WinIsTrue = true;
      std::cout << "You Win!\n";
    }
  }
  return WinIsTrue;
}

// The AI/Enemy function
// It needs to read the board, pick the best position in the board and print that position while also being aware of the player.
void Enemy(std::array<std::array<char, 3>, 3>& board) {
  int RandomVal = rand() % 9;
  int x = RandomVal / 3;
  int y = RandomVal % 3;

  if(board[x][y] == ' ') {
    board[x][y] = enemy;
  }
}

int main() {
  bool Game = true;
  bool Quit = false;
  bool Win = false;

  while(Game) {
    PrintBoard(board);
    Quit = PlayerInput(board);
    Enemy(board);
    Win = WinPositions(board, player);
    system("clear");
    if(Quit == true && Win == true) {
      Game = false;
    }
  }
}
