#include <raylib.h>

int main(void)
{
    InitWindow(800, 450, "Hello Raylib");

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Ola Raylib no macOS!", 190, 200, 20, LIGHTGRAY);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
