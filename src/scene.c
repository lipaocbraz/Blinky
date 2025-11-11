#include <scene.h>
#include <raylib.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>

void InitScene(Scene *scene, const char *imagePath)
{
    scene->map1 = LoadTexture(imagePath);
}

void DrawScene(Scene *scene)
{
    // 1. Obtém as dimensões atuais da tela
    float screenWidth = (float)GetScreenWidth();
    float screenHeight = (float)GetScreenHeight();

    // 2. Obtém as dimensões da imagem do mapa (apenas para o sourceRec)
    float mapWidth = (float)scene->map1.width;
    float mapHeight = (float)scene->map1.height;

    // 3. Define o retângulo de ORIGEM (Source) - A Imagem Inteira
    // Pega a imagem inteira.
    Rectangle sourceRec = {0.0f, 0.0f, mapWidth, mapHeight};

    // 4. Define o retângulo de DESTINO (Destination) - A Tela Inteira
    // Desenha a imagem na tela, indo de (0, 0) até a largura/altura da tela.
    // ISTO CAUSA A DEFORMAÇÃO.
    Rectangle destRec = {
        0.0f,
        0.0f,
        screenWidth,
        screenHeight};

    // 5. Desenha a textura
    DrawTexturePro(scene->map1, sourceRec, destRec, (Vector2){0, 0}, 0.0f, WHITE);
}

void UnloadScene(Scene *scene)
{
    UnloadTexture(scene->map1);
}
