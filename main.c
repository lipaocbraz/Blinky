#include <raylib.h>
#include <scene.h>
#include "game.h"

int main(void)
{
    int WINDOW_WIDTH = GetMonitorWidth(0);
    int WINDOW_HEIGHT = GetMonitorHeight(0);

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Blinky");
    GameScreen currentScreen = TITLE;
    SetTargetFPS(60);
    Scene map1;

    ClearBackground(RAYWHITE);
    while (!WindowShouldClose())
    {
        switch (currentScreen)
        {

        case TITLE:
        {
            if (IsKeyPressed(KEY_ENTER))
            {
                currentScreen = GAMEPLAY;
                InitScene(&map1, "assets/map1.png");
            }
        }
        case GAMEPLAY:
        {
            if (IsKeyPressed(KEY_Q))
            {
                currentScreen = TITLE;
                UnloadScene(&map1);
            }
        }
        case ENDING:
        {
            if (IsKeyPressed(KEY_BACKSPACE))
                break;
        }

            BeginDrawing();
            switch (currentScreen)
            {
            case TITLE:
            {
                DrawText("Blinky", WINDOW_WIDTH / 2 - MeasureText("Blinky the Ghost", 40) / 2, WINDOW_HEIGHT / 4, 40, DARKPURPLE);
                DrawText("Pressione ENTER para JOGAR", WINDOW_WIDTH / 2 - MeasureText("Pressione ENTER para JOGAR", 20) / 2, WINDOW_HEIGHT / 2, 20, BLACK);
            }
            break;
            case GAMEPLAY:
            {
                DrawScene(&map1);
            }
            case ENDING:
            {
                DrawText("GAME OVER!", WINDOW_WIDTH / 2 - MeasureText("GAME OVER!", 40) / 2, WINDOW_HEIGHT / 2, 40, RED);
            }
            break;
            }

            EndDrawing();
        }
    }
    if (currentScreen == GAMEPLAY)
    {
        UnloadScene(&map1);
    }
    CloseWindow();
    return 0;
}
