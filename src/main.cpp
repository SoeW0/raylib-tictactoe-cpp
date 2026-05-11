#include "raylib.h"
#include <array>
#include <optional>

constexpr int SCREENWIDTH = 800;
constexpr int SCREENHEIGHT = 450;

int main() {
  int halfScreenWidth = SCREENWIDTH / 2;
  int halfScreenHeight = SCREENHEIGHT / 2;

  InitWindow(SCREENWIDTH, SCREENHEIGHT, "Tic-Tac-Toe");
  BeginDrawing();

  while(!WindowShouldClose()) {
    ClearBackground(RAYWHITE);
    DrawText("Hello World", halfScreenWidth, halfScreenHeight, 10, GRAY);

    EndDrawing(); 
  }

}
