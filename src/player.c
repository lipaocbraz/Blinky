#include "player.h"
#include "raylib.h"
#define MAIN_XHITBOX 46
#define MAIN_YHITBOX 48
const float playerXhitbox_DEBUG = 200.0f;
const float playerYhitbox_DEBUG = 200.0f;

void initPlayer(Player *p, const char *texturePath, Vector2 startPos)
{
    p->texture = LoadTexture(texturePath);
    p->speed = 1.5f;

    p->position = startPos;
    p->keysCollected = 0;

    p->Xhitbox = MAIN_XHITBOX;
    p->Yhitbox = MAIN_YHITBOX;

    p->rectangleHitbox = (Rectangle){p->position.x, p->position.y, p->Xhitbox, p->Yhitbox};

    TraceLog(LOG_INFO, "PLAYER: Heroi inicializado.");
}

void UpdatePlayer(Player *p, Scene *scene)
{
    float newX = p->position.x;
    float newY = p->position.y;

    // --- CÁLCULO DO NOVO PONTO ---
    // (Seu código de movimento, permanece o mesmo)
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))
        newX += p->speed;
    else if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))
        newX -= p->speed;
    if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S))
        newY += p->speed;
    else if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W))
        newY -= p->speed;

    if (!CheckSceneCollision(scene, (Vector2){newX, newY}))
    {
        p->position = p->position;
        TraceLog(LOG_INFO, "PLAYER: Colisão detectada. Movimento bloqueado.");
        return;
    }
    else
    {
        p->position.x = newX;
        p->position.y = newY;
    }

    p->rectangleHitbox = (Rectangle){p->position.x, p->position.y, p->Xhitbox, p->Yhitbox};
}
void drawPlayer(Player *p)
{
    DrawTextureV(p->texture, p->position, WHITE);

    // 🔨 Calcula o ponto de colisão que o UpdatePlayer está mirando (Base central)
    float debugX = p->position.x + p->Xhitbox / 2.0f;
    float debugY = p->position.y + p->Yhitbox / 2.0f;

    // 🔨 Desenha um pequeno círculo vermelho no ponto exato de colisão
    DrawCircle((int)debugX, (int)debugY, 3, RED);
}

void unloadPlayer(Player *p)
{
    UnloadTexture(p->texture);
    TraceLog(LOG_INFO, "Heroi descarregado");
}
