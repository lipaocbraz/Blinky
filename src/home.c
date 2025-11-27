#include <stdio.h>
#include <string.h>
#include "raylib.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#define BACKGROUND_COLOR (Color){34, 40, 49, 255}   // Azul escuro
#define BUTTON_FRAME_COLOR (Color){70, 52, 38, 255} // Marrom escuro
#define BUTTON_BG_COLOR (Color){44, 48, 55, 255}    // Cinza escuro
#define TEXT_COLOR (Color){190, 180, 160, 255}      // Bege claro
#define HOVER_COLOR (Color){255, 255, 255, 255}     // Branco

#define TITLE_FONT_SIZE 60
#define BUTTON_FONT_SIZE 30
#define BUTTON_PADDING 20
#define BUTTON_SPACING 30

typedef struct
{
    Rectangle rect;
    const char *text;
    Color color;
    int fontSize;
} Button;

Button startButton;
Button scoresButton;

Rectangle CreateCenteredButton(int totalWidth, int totalHeight, int buttonWidth, int buttonHeight, int yOffset)
{
    return (Rectangle){
        (totalWidth - buttonWidth) / 2.0f,
        (totalHeight / 2.0f) + yOffset,
        buttonWidth,
        buttonHeight};
}

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "BLINKY - Menu Principal");
    SetTargetFPS(60);

    int buttonWidth = 300;
    int buttonHeight = 60;

    startButton.text = "START GAME";
    startButton.fontSize = BUTTON_FONT_SIZE;
    startButton.rect = CreateCenteredButton(SCREEN_WIDTH, SCREEN_HEIGHT, buttonWidth, buttonHeight, -BUTTON_SPACING / 2 - buttonHeight);

    scoresButton.text = "TOP SCORES";
    scoresButton.fontSize = BUTTON_FONT_SIZE;
    scoresButton.rect = CreateCenteredButton(SCREEN_WIDTH, SCREEN_HEIGHT, buttonWidth, buttonHeight, BUTTON_SPACING / 2);

    while (!WindowShouldClose())
    {
        Vector2 mousePoint = GetMousePosition();

        startButton.color = TEXT_COLOR;
        scoresButton.color = TEXT_COLOR;

        if (CheckCollisionPointRec(mousePoint, startButton.rect))
        {
            startButton.color = HOVER_COLOR;
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                printf("--- Jogo BLINKY Iniciado! ---\n");
            }
        }

        if (CheckCollisionPointRec(mousePoint, scoresButton.rect))
        {
            scoresButton.color = HOVER_COLOR;
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                printf("--- Tela de Scores Acessada! ---\n");
            }
        }

        BeginDrawing();

        ClearBackground(BACKGROUND_COLOR);

        const char *titleText = "BLINKY";
        int titleTextWidth = MeasureText(titleText, TITLE_FONT_SIZE);
        DrawText(titleText, (SCREEN_WIDTH - titleTextWidth) / 2, 50, TITLE_FONT_SIZE, TEXT_COLOR);

        DrawRectangleRec(startButton.rect, BUTTON_FRAME_COLOR);
        DrawRectangle(startButton.rect.x + BUTTON_PADDING / 2, startButton.rect.y + BUTTON_PADDING / 2,
                      startButton.rect.width - BUTTON_PADDING, startButton.rect.height - BUTTON_PADDING,
                      BUTTON_BG_COLOR);

        int startTextWidth = MeasureText(startButton.text, startButton.fontSize);
        DrawText(startButton.text,
                 startButton.rect.x + (startButton.rect.width - startTextWidth) / 2,
                 startButton.rect.y + (startButton.rect.height - startButton.fontSize) / 2,
                 startButton.fontSize, startButton.color);

        DrawRectangleRec(scoresButton.rect, BUTTON_FRAME_COLOR);
        DrawRectangle(scoresButton.rect.x + BUTTON_PADDING / 2, scoresButton.rect.y + BUTTON_PADDING / 2,
                      scoresButton.rect.width - BUTTON_PADDING, scoresButton.rect.height - BUTTON_PADDING,
                      BUTTON_BG_COLOR); // Fundo

        int scoresTextWidth = MeasureText(scoresButton.text, scoresButton.fontSize);
        DrawText(scoresButton.text,
                 scoresButton.rect.x + (scoresButton.rect.width - scoresTextWidth) / 2,
                 scoresButton.rect.y + (scoresButton.rect.height - scoresButton.fontSize) / 2,
                 scoresButton.fontSize, scoresButton.color);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
