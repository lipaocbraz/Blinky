#include "player.h"
#include "raylib.h"

bool collisionpixel(Image *map, float x, float y);

void initPlayer(Player *p, const char *texturePath)
{

    p->texture = LoadTexture(texturePath);

    p->speed = 1.7f;

    p->position.x = (float)GetScreenWidth() / 2.0f - (float)p->texture.width / 2.0f;
    p->position.y = (float)GetScreenHeight() / 2.0f - (float)p->texture.height / 2.0f;

    TraceLog(LOG_INFO, "PLAYER: Heroi inicializado.");
}

void UpdatePlayer(Player *p, Scene *scene)
{
    float newX = p->position.x;
    float newY = p->position.y;

    // --- Cálculo do Novo Ponto ---
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))
        newX += p->speed;
    else if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))
        newX -= p->speed;
    if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S))
        newY += p->speed;
    else if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W))
        newY -= p->speed;

    // --- Colisão Horizontal ---
    // Verifica o novo ponto X com a posição Y atual (ou um ponto de colisão específico no sprite)
    if (!collisionpixel(&scene->collision_image, newX, p->position.y))
    {
        p->position.x = newX; // Movimento permitido
    }

    // --- Colisão Vertical ---
    // Verifica a posição X atual com o novo ponto Y
    if (!collisionpixel(&scene->collision_image, p->position.x, newY))
    {
        p->position.y = newY; // Movimento permitido
    }
}

void drawPlayer(Player *p)
{
    DrawTextureV(p->texture, p->position, WHITE);
}

void unloadPlayer(Player *p)
{
    UnloadTexture(p->texture);
    TraceLog(LOG_INFO, "Heroi descarregado");
}

bool collisionpixel(Image *map, float x, float y)
{
    int px = (int)x;
    int py = (int)y;

    if (px < 0 || px >= map->width || py < 0 || py >= map->height)
    {
        return true;
    }

    Color pixelcolor = GetImageColor(*map, px, py);

    return (pixelcolor.r == 0 && pixelcolor.g == 0 && pixelcolor.b == 0);
}