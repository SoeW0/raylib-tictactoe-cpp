#include "raylib.h"
#include <array>
#include <optional>
#include <cstdlib>

constexpr int CELLHEIGHT = 3;
constexpr int CELLWIDTH = 3;

//Game State
enum struct GameState {
  Playing,
  GameEnd
};

enum struct CanMark {
  canMark,
  cannotMark
};

//Cell state that holds special values
enum struct CellState {
  X,
  O,
  Empty
}; 

//Cell data that holds the positions, size and Cell State
struct Cell {
  Rectangle rects;
  CellState state;
};

struct CellPos {
  size_t y;
  size_t x;
};

struct Player {
  CanMark mark;
  bool alreadyMarked;
  bool hasWon;
};

struct Enemy {
  CanMark mark;
  bool alreadyMarked;
  bool hasWon;
};

//alias for the grid array
using Grid = std::array<std::array<Cell, CELLHEIGHT>, CELLWIDTH>;

//function to create a grid
void CreateGrid(Grid& grid) {
  int padding = 5;
  float size = 100; 
  float PosX = 250;
  float PosY = 100;

  for(int col = 0; col < CELLHEIGHT; col++) {
    for(int row = 0; row < CELLWIDTH; row++) {
      float px = PosX + row * (size + padding);
      float py = PosY + col * (size + padding);

      grid[col][row].state = CellState::Empty;
      grid[col][row].rects = { px, py, size, size};
    }
  }
}

//Draw the grid of rectangles
void DrawRecGrid(const Grid& grid) {
  for(int col = 0; col < CELLHEIGHT; col++) {
    for(int row = 0; row < CELLWIDTH; row++) {
      DrawRectangleRec(grid[col][row].rects, RAYWHITE);
      DrawRectangleLinesEx(grid[col][row].rects, 5, GRAY);
    }
  }
}

//Gets pointer and rect collision on hover
std::optional<CellPos> GetCollisionHover(const Grid& grid, Vector2 pointer) {
  for(size_t col = 0; col < CELLHEIGHT; col++) {
    for(size_t row = 0; row < CELLWIDTH; row++) {
      if(CheckCollisionPointRec(pointer, grid[col][row].rects)) {
        return CellPos { col, row };
      }
    }
  }
  return std::nullopt;
}

//A function to draw the symbols inside the selected rectangle permanently
void DrawSymbol(const Grid& grid) {
  for(int col = 0; col < CELLHEIGHT; col++) {
    for(int row = 0; row < CELLWIDTH; row++) {
      int x = grid[col][row].rects.x;
      int y = grid[col][row].rects.y;
      if(grid[col][row].state == CellState::X) DrawText("X", x + 20, y + 5, 100, BLACK);
      if(grid[col][row].state == CellState::O) DrawText("O", x + 20, y + 5, 100, BLACK);
    }
  }
}

//Changes the cellstate given a position
void ChangeState(CellPos pos, Grid& grid, CellState state) {
  if(grid[pos.y][pos.x].state == CellState::Empty && state == CellState::X) {
    grid[pos.y][pos.x].state = CellState::X;
  } else if(grid[pos.y][pos.x].state == CellState::Empty && state == CellState::O) {
    grid[pos.y][pos.x].state = CellState::O;
  }
}

//Pointer interactivity
void RecInteract(Grid& grid, Vector2 pointer, Player& player) {
  auto hover = GetCollisionHover(grid, pointer);
  if(hover.has_value()) {
    CellPos Cps = hover.value();

    Rectangle HoveredRects = grid[Cps.y][Cps.x].rects;
    DrawRectangleLinesEx(HoveredRects, 10, BLUE);
    if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
      ChangeState(*hover, grid, CellState::O);
      player.alreadyMarked = true;
    }
  }
}

//Opponent/Simple AI
/*------------------------------------------------*/

//Checks valid positions for mark placement
std::optional<CellPos> CheckValidMarkPos(const Grid& grid) {
  for(size_t y = 0; y < grid.size(); y++) {
    for(size_t x = 0; x < grid.size(); x++) {
      if(grid[y][x].state == CellState::Empty) {
        return CellPos { y, x };
      }
    }
  }
  return std::nullopt;
}


//AI position function
void Opponent(Grid& grid, Enemy& enemy) {
  CellState cellMark = CellState::X;
  auto cellMarkPos = CheckValidMarkPos(grid);

  if(cellMarkPos.has_value()) ChangeState(*cellMarkPos, grid, cellMark);
  enemy.alreadyMarked = true;
}

void gameTurn(Player& player, Enemy& enemy) {
  if(enemy.alreadyMarked == true) {
    enemy.mark = CanMark::cannotMark;
    enemy.alreadyMarked = false;

    player.mark = CanMark::canMark;
  }
  if(player.alreadyMarked == true) {
    player.mark = CanMark::cannotMark;
    player.alreadyMarked = false;

    enemy.mark = CanMark::canMark;
  }
}

//function that checks if there is a win
void winCondition(const Grid& grid, Enemy& enemy, Player& player) {
  //Checks player mark horizontally
  if(grid[0][0].state == CellState::O && grid[0][1].state == CellState::O && grid[0][2].state == CellState::O) player.hasWon = true;
  if(grid[1][0].state == CellState::O && grid[1][1].state == CellState::O && grid[1][2].state == CellState::O) player.hasWon = true;
  if(grid[2][0].state == CellState::O && grid[2][1].state == CellState::O && grid[2][2].state == CellState::O) player.hasWon = true;

  //Checks player mark vertically
  if(grid[0][0].state == CellState::O && grid[1][0].state == CellState::O && grid[2][0].state == CellState::O) player.hasWon = true;
  if(grid[0][1].state == CellState::O && grid[1][1].state == CellState::O && grid[2][1].state == CellState::O) player.hasWon = true;
  if(grid[0][2].state == CellState::O && grid[1][2].state == CellState::O && grid[2][2].state == CellState::O) player.hasWon = true;

  //Checks player mark diagonally
  if(grid[0][0].state == CellState::O && grid[1][1].state == CellState::O && grid[2][2].state == CellState::O) player.hasWon = true;
  if(grid[0][2].state == CellState::O && grid[1][1].state == CellState::O && grid[2][0].state == CellState::O) player.hasWon = true;

  //Checks enemy mark horizontally
  if(grid[0][0].state == CellState::X && grid[0][1].state == CellState::X && grid[0][2].state == CellState::X) enemy.hasWon = true;
  if(grid[1][0].state == CellState::X && grid[1][1].state == CellState::X && grid[1][2].state == CellState::X) enemy.hasWon = true;
  if(grid[2][0].state == CellState::X && grid[2][1].state == CellState::X && grid[2][2].state == CellState::X) enemy.hasWon = true;

  //Checks enemy mark vertically
  if(grid[0][0].state == CellState::X && grid[1][0].state == CellState::X && grid[2][0].state == CellState::X) enemy.hasWon = true;
  if(grid[0][1].state == CellState::X && grid[1][1].state == CellState::X && grid[2][1].state == CellState::X) enemy.hasWon = true;
  if(grid[0][2].state == CellState::X && grid[1][2].state == CellState::X && grid[2][2].state == CellState::X) enemy.hasWon = true;

  //Checks enemy mark diagonally
  if(grid[0][0].state == CellState::X && grid[1][1].state == CellState::X && grid[2][2].state == CellState::X) enemy.hasWon = true;
  if(grid[0][2].state == CellState::X && grid[1][1].state == CellState::X && grid[2][0].state == CellState::X) enemy.hasWon = true;

}

int main() {
  const int ScreenWidth = 800;
  const int ScreenHeight = 450;

  int halfScreenWidth = ScreenWidth / 2;
  int halfScreenHeight = ScreenHeight / 2;

  InitWindow(ScreenWidth, ScreenHeight, "Tic-Tac-Toe");

  Grid grid;
  GameState gameState = GameState::Playing;
  Player player;
  Enemy enemy;

  CreateGrid(grid);
  player.mark = CanMark::cannotMark;
  enemy.mark = CanMark::canMark;

  while(!WindowShouldClose()) {
    BeginDrawing();
    Vector2 pointer = GetMousePosition();
    ClearBackground(BLACK);
    DrawText("Tic-Tac-Toe", halfScreenWidth - 60, halfScreenHeight - 200, 20, GRAY);
    //Rectangle gameButton = DrawGameStartButton(halfScreenWidth, halfScreenHeight, grid);

    DrawRecGrid(grid);
    gameTurn(player, enemy);
    if(player.mark == CanMark::canMark) {
        RecInteract(grid, pointer, player);
    }
    if(enemy.mark == CanMark::canMark) {
        Opponent(grid, enemy);
    }
    DrawSymbol(grid);
    winCondition(grid, enemy, player);

    if(player.hasWon == true) {
      DrawText("Player has Won", halfScreenWidth, halfScreenHeight, 200, BLUE);
    }
    if(enemy.hasWon == true) {
      DrawText("Enemey has Won", halfScreenWidth, halfScreenHeight, 200, BLUE);
    }

    EndDrawing(); 
  }
  CloseWindow();

}
