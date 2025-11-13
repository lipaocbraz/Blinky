#include "player.h"
#include "raylib.h"

void initPlayer(Player *p, const char *texturePath)
{

    p->texture = LoadTexture(texturePath);

    p->speed = 4.0f;

    p->position.x = (float)GetScreenWidth() / 2.0f - (float)p->texture.width / 2.0f;
    p->position.y = (float)GetScreenHeight() / 2.0f - (float)p->texture.height / 2.0f;

    TraceLog(LOG_INFO, "PLAYER: Heroi inicializado.");
}

void updatePlayer(Player *p)
{
    if (IsKeyDown(KEY_A))
    {
        p->position.x -= p->speed;
    }
    if (IsKeyDown(KEY_D))
    {
        p->position.x += p->speed;
    }
    if (IsKeyDown(KEY_W))
    {
        p->position.y -= p->speed;
    }
    if (IsKeyDown(KEY_S))
    {
        p->position.y += p->speed;
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