#include <iostream>
#include <array>
#include <vector>

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

//Check if positions in the board given the mark result in a winning condition
bool CheckWinCon(const std::array<std::array<char, 3>, 3>& board, const char mark) {
  bool CanWin = false;
  std::vector<std::pair<int, int>> vec;
  for(size_t row = 0; row < board.size(); row++) {
    for(size_t col = 0; col < board.size(); col++) {
      if (board[row][col] == mark) {
        std::pair<int, int> map = {row, col};
        vec.push_back(map);
      }
    }
  }

  std::vector<std::pair<int, int>> expected1 = {
    {0, 0},
    {0, 1},
    {0, 2}
  };
  std::vector<std::pair<int, int>> expected2 = {
    {1, 0},
    {1, 1},
    {1, 2}
  };
  std::vector<std::pair<int, int>> expected3 = {
    {2, 0},
    {2, 1},
    {2, 2}
  };
  std::vector<std::pair<int, int>> expected4 = {
    {0, 0},
    {1, 1},
    {2, 2}
  };
  std::vector<std::pair<int, int>> expected5 = {
    {0, 2},
    {1, 1},
    {2, 0}
  };
  if (vec == expected1 || vec == expected2 || vec == expected3 || vec == expected4 || vec == expected5) {
    CanWin = true;
  }

  return CanWin;
}

bool PlayerInput(std::array<std::array<char, 3>, 3>& board) {
  bool output = false;
  const char player = 'X';
  char input;

  std::cout << "Select a cell (1-9): ";
  std::cin >> input;

  if(input == 'q' || input == 'Q') {
    output = false;
  }

  if(input != 'q' || input != 'Q') {
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

// The AI/Enemy function
// It needs to read the board, pick the best position in the board and print that position while also being aware of the player.
void Enemy(std::array<std::array<char, 3>, 3>& board) {
  const char enemy = 'O';

}

int main() {
  bool Game = true;
  bool Quit = false;

  while(Game) {
    PrintBoard(board);
    Quit = PlayerInput(board);
    system("clear");
    CheckWinCon(board, 'X');
    if(Quit == true) {
      Game = false;
    }
  }
}
