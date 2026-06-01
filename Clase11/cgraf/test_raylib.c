#include "raylib.h"

int main() {
    InitWindow(400, 300, "Gráficos en C");
    
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Hola", 50, 50, 20, DARKBLUE);
        DrawLine(30, 250, 370, 250, GREEN);
        DrawRectangle(100, 100, 150, 80, RAYWHITE);
        DrawRectangleLines(100, 100, 150, 80, RED);
        DrawCircle(250, 150, 50, BLUE);
        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}