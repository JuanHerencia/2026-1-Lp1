#include "raylib.h"
#include <math.h>
float XMIN = -20.0f, XMAX = 20.0f, YMIN = -10.0f, YMAX = 10.0f;
float difx = 0.01f;

typedef float (*FuncPtr)(float);

float fx(float x) {
    if (fabsf(x) < 1e-6f) return 1.0f;
    return 4*sinf(x) / x;
}

int main(void) {
    const int screenWidth = 1000;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "y = sen(x) / x");
    SetTargetFPS(60);

    float zoom = 35.0f;
    const float zoomStep = 1.1f;

    FuncPtr f = fx;

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_KP_ADD) || IsKeyPressed(KEY_EQUAL)) {
            zoom *= zoomStep;
        }
        if (IsKeyPressed(KEY_KP_SUBTRACT) || IsKeyPressed(KEY_MINUS)) {
            zoom /= zoomStep;
            if (zoom < 5.0f) zoom = 5.0f;
        }

        BeginDrawing();
        ClearBackground(BLACK);

        int cx = screenWidth / 2;
        int cy = screenHeight / 2;

        for (int x = XMIN; x <= XMAX; x += 2) {
            int sx = cx + (int)(x * zoom);
            DrawLine(sx, 0, sx, screenHeight, GRAY);
            DrawText(TextFormat("%d", x), sx - (int)XMAX, cy + (int)YMAX - 4, (int)YMAX + 4, LIGHTGRAY);
        }

        for (int y = YMIN; y <= YMAX; y += 2) {
            int sy = cy - (int)(y * zoom);
            DrawLine(0, sy, screenWidth, sy, GRAY);
            if (y != 0) DrawText(TextFormat("%d", y), cx + (int)XMAX - 4, sy - 8, (int)YMAX + 4, LIGHTGRAY);
        }

        DrawLine(0, cy, screenWidth, cy, WHITE);
        DrawLine(cx, 0, cx, screenHeight, WHITE);

        DrawText("Zoom con + y -", 20, 20, 20, RAYWHITE);

        float prevX = XMIN;
        float prevY = f(prevX);

        for (float x = XMIN + difx; x <= XMAX; x += difx) {
            float y = f(x);

            int x1 = cx + (int)(prevX * zoom);
            int y1 = cy - (int)(prevY * zoom);
            int x2 = cx + (int)(x * zoom);
            int y2 = cy - (int)(y * zoom);

            if (isfinite(prevY) && isfinite(y)) {
                DrawLineEx((Vector2){(float)x1, (float)y1}, (Vector2){(float)x2, (float)y2}, 2.0f, GREEN);
            }

            prevX = x;
            prevY = y;
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}