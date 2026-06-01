#include "raylib.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define W 1280
#define H 720
#define G 5.0f

typedef struct {
    Vector3 pos;
    Vector3 vel;
    float mass;
    float radius;
    Color color;
} Body;

static float frand(float a, float b) {
    return a + (b - a) * (float)rand() / (float)RAND_MAX;
}

static Vector3 vadd(Vector3 a, Vector3 b) { return (Vector3){a.x + b.x, a.y + b.y, a.z + b.z}; }
static Vector3 vsub(Vector3 a, Vector3 b) { return (Vector3){a.x - b.x, a.y - b.y, a.z - b.z}; }
static Vector3 vmul(Vector3 a, float s) { return (Vector3){a.x * s, a.y * s, a.z * s}; }
static float vlen(Vector3 a) { return sqrtf(a.x*a.x + a.y*a.y + a.z*a.z); }

static void apply_gravity(Body *b, int n, float dt) {
    Vector3 acc[3] = {{0}};
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            Vector3 d = vsub(b[j].pos, b[i].pos);
            float dist = vlen(d) + 0.25f;
            float inv = 1.0f / (dist * dist * dist);
            Vector3 dir = vmul(d, inv);
            acc[i] = vadd(acc[i], vmul(dir, G * b[j].mass));
            acc[j] = vsub(acc[j], vmul(dir, G * b[i].mass));
        }
    }
    for (int i = 0; i < n; i++) {
        b[i].vel = vadd(b[i].vel, vmul(acc[i], dt));
        b[i].pos = vadd(b[i].pos, vmul(b[i].vel, dt));
    }
}

int main(void) {
    srand((unsigned)time(NULL));
    InitWindow(W, H, "Tres cuerpos gravitatorios con raylib");
    SetTargetFPS(60);

    Camera3D camera = {0};
    camera.position = (Vector3){ 0.0f, 55.0f, 90.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    float side = frand(18.0f, 34.0f);
    float h = side * sqrtf(3.0f) * 0.5f;
    float z0 = frand(-8.0f, 8.0f);

    Body b[3] = {
        { .pos = (Vector3){ -side*0.5f, 0.0f, z0 }, .vel = (Vector3){ frand(-0.2f,0.2f), 0, frand(-0.2f,0.2f) }, .mass = frand(6.0f, 18.0f), .radius = frand(1.4f, 3.2f), .color = RED },
        { .pos = (Vector3){  side*0.5f, 0.0f, z0 }, .vel = (Vector3){ frand(-0.2f,0.2f), 0, frand(-0.2f,0.2f) }, .mass = frand(6.0f, 18.0f), .radius = frand(1.4f, 3.2f), .color = GREEN },
        { .pos = (Vector3){  0.0f,      0.0f, z0 + h }, .vel = (Vector3){ frand(-0.2f,0.2f), 0, frand(-0.2f,0.2f) }, .mass = frand(6.0f, 18.0f), .radius = frand(1.4f, 3.2f), .color = BLUE }
    };

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        apply_gravity(b, 3, dt);

        BeginDrawing();
        ClearBackground((Color){18, 18, 22, 255});

        BeginMode3D(camera);
        DrawGrid(30, 4.0f);

        for (int i = 0; i < 3; i++) {
            DrawSphere(b[i].pos, b[i].radius, b[i].color);
            DrawSphereWires(b[i].pos, b[i].radius, 12, 12, BLACK);
        }

        DrawLine3D(b[0].pos, b[1].pos, GRAY);
        DrawLine3D(b[1].pos, b[2].pos, GRAY);
        DrawLine3D(b[2].pos, b[0].pos, GRAY);

        EndMode3D();

        DrawText("Tres cuerpos gravitatorios", 20, 20, 24, RAYWHITE);
        DrawText(TextFormat("M1=%.1f R1=%.1f", b[0].mass, b[0].radius), 20, 55, 20, RAYWHITE);
        DrawText(TextFormat("M2=%.1f R2=%.1f", b[1].mass, b[1].radius), 20, 80, 20, RAYWHITE);
        DrawText(TextFormat("M3=%.1f R3=%.1f", b[2].mass, b[2].radius), 20, 105, 20, RAYWHITE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}