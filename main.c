#include <raylib.h>
#include <scene.h>

int main(void)
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Hello Raylib");
    SetTargetFPS(60);

    InitScene();

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        drawscene();
        EndDrawing();
    }

    UnloadScene();
    CloseWindow();
    return 0;
}
