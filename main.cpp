#include <iostream>
#include <array>

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
  char player = 'X';
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

int main() {
  bool Game = true;
  bool Quit = false;

  while(Game) {
    PrintBoard(board);
    Quit = PlayerInput(board);
    system("clear");
    if(Quit == true) {
      Game = false;
    }
  }
}
