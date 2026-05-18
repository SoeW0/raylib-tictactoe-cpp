#include "raylib.h"
#include <array>
#include <optional>

constexpr int CELLHEIGHT = 3;
constexpr int CELLWIDTH = 3;

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
  int y;
  int x;
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
  for(int col = 0; col < CELLHEIGHT; col++) {
    for(int row = 0; row < CELLWIDTH; row++) {
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
void RecInteract(Grid& grid, Vector2 pointer) {
  auto hover = GetCollisionHover(grid, pointer);
  if(hover.has_value()) {
    CellPos Cps = hover.value();

    Rectangle HoveredRects = grid[Cps.y][Cps.x].rects;
    DrawRectangleLinesEx(HoveredRects, 10, BLUE);
    if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) ChangeState(*hover, grid, CellState::X);
    if(IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) ChangeState(*hover, grid, CellState::O);
  }
}

int main() {
  const int ScreenWidth = 800;
  const int ScreenHeight = 450;

  int halfScreenWidth = ScreenWidth / 2;
  int halfScreenHeight = ScreenHeight / 2;

  InitWindow(ScreenWidth, ScreenHeight, "Tic-Tac-Toe");

  Grid grid;

  CreateGrid(grid);


  while(!WindowShouldClose()) {
    BeginDrawing();
    Vector2 pointer = GetMousePosition();
    ClearBackground(BLACK);
    DrawText("Tic-Tac-Toe", halfScreenWidth - 60, halfScreenHeight - 200, 20, GRAY);

    DrawRecGrid(grid);
    RecInteract(grid, pointer);
    DrawSymbol(grid);

    EndDrawing(); 
  }
  CloseWindow();

}
