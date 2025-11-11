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
                currentScreen = ENDING;
            }
        }
        case ENDING:
        {
            if (IsKeyPressed(KEY_P))
            {
                UnloadScene(&map1);
            }
        }

            BeginDrawing();
            ClearBackground(RAYWHITE);

            switch (currentScreen)
            {
            case TITLE:
            {
                int currentW = GetScreenWidth();
                int currentH = GetScreenHeight();

                const char *titulo = "MEU JOGO BLINKY";
                int fontSizeTitulo = 40;

                const char *instrucao = "Pressione ENTER para JOGAR";
                int fontSizeInstrucao = 20;

                // 1. Centralização do Título:
                // Pos X = (Metade da Tela) - (Metade da Largura do Texto)
                int xTitulo = currentW / 2 - MeasureText(titulo, fontSizeTitulo) / 2;
                int yTitulo = currentH / 4;

                DrawText(titulo, xTitulo, yTitulo, fontSizeTitulo, DARKBLUE);

                // 2. Centralização da Instrução:
                int xInstrucao = currentW / 2 - MeasureText(instrucao, fontSizeInstrucao) / 2;
                int yInstrucao = currentH / 2;

                DrawText(instrucao, xInstrucao, yInstrucao, fontSizeInstrucao, BLACK);
            }
            break;

            case GAMEPLAY:
            {
                DrawScene(&map1);
            }
            break;
            case ENDING:
            {
                int currentW = GetScreenWidth();
                int currentH = GetScreenHeight();

                const char *titulo = "GAME OVER";
                int fontSizeTitulo = 40;

                const char *instrucao = "APERTE 'DELETE' PARA SAIR";
                int fontSizeInstrucao = 20;

                // 1. Centralização do Título:
                // Pos X = (Metade da Tela) - (Metade da Largura do Texto)
                int xTitulo = currentW / 2 - MeasureText(titulo, fontSizeTitulo) / 2;
                int yTitulo = currentH / 4;

                DrawText(titulo, xTitulo, yTitulo, fontSizeTitulo, RED);
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
