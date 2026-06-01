#include "raylib.h"
#include<stdio.h>
#include <math.h>
#include <time.h>

#define W 800
#define H 800
#define CX (W/2)
#define CY (H/2)
#define R 300.0f

static Vector2 Polar(float angleDeg, float radius) {
    float a = (angleDeg - 90.0f) * DEG2RAD;
    return (Vector2){ CX + cosf(a) * radius, CY + sinf(a) * radius };
}

static void DrawHand(float angleDeg, float length, float thickness, Color color) {
    Vector2 p = Polar(angleDeg, length);
    DrawLineEx((Vector2){CX, CY}, p, thickness, color);
}

static void DrawClockFace(void) {
    DrawCircle(CX, CY, R + 8, BLACK);
    DrawCircle(CX, CY, R, LIGHTGRAY);

    for (int i = 1; i <= 12; i++) {
        float a = i * 30.0f;
        Vector2 p = Polar(a, R - 45);
        char txt[3];
        snprintf(txt, sizeof(txt), "%d", i);
        int fs = 34;
        int tw = MeasureText(txt, fs);
        DrawText(txt, (int)(p.x - tw / 2), (int)(p.y - fs / 2), fs, BLACK);
    }

    for (int i = 0; i < 60; i++) {
        float a = i * 6.0f;
        Vector2 o = Polar(a, R);
        Vector2 inn = Polar(a, (i % 5 == 0) ? (R - 18) : (R - 10));
        DrawLineEx(o, inn, (i % 5 == 0) ? 3.0f : 1.5f, BLACK);
    }

    DrawCircle(CX, CY, 10, BLACK);
    DrawCircle(CX, CY, 4, DARKGRAY);
}

int main(void) {
    InitWindow(W, H, "Reloj analogico con raylib");
    SetTargetFPS(60);

    int lastSecond = -1;

    while (!WindowShouldClose()) {
        time_t now = time(NULL);
        struct tm *t = localtime(&now);

        if (t->tm_sec != lastSecond) {
            lastSecond = t->tm_sec;
        }

        float sec = (float)t->tm_sec;
        float min = (float)t->tm_min + sec / 60.0f;
        float hour = (float)(t->tm_hour % 12) + min / 60.0f;

        float secAngle = sec * 6.0f;
        float minAngle = min * 6.0f;
        float hourAngle = hour * 30.0f;

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawClockFace();

        DrawHand(hourAngle, R * 0.45f, 10.0f, BLUE);
        DrawHand(minAngle,  R * 0.70f, 7.0f, BLUE);
        DrawHand(secAngle,  R * 0.80f, 3.0f, RED);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}