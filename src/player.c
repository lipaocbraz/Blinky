#include "player.h"
#include "raylib.h"

bool collisionpixel(Image *map, float x, float y);

void initPlayer(Player *p, const char *texturePath)
{

    p->texture = LoadTexture(texturePath);

    p->speed = 1.7f;

    p->position.x = (float)GetScreenWidth() / 2.0f - (float)p->texture.width / 2.0f;
    p->position.y = (float)GetScreenHeight() / 2.0f - (float)p->texture.height / 2.0f;

    p->width = 200.0f;  
    p->height = 200.0f;  

    TraceLog(LOG_INFO, "PLAYER: Heroi inicializado.");
}

// Certifique-se de que playerWidth e playerHeight estão definidos ou são 32 e 32.
const float playerWidth = 32.0f;
const float playerHeight = 32.0f;

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

    // --- Colisão Horizontal ---

    // 1. Ponto de Colisão na TELA (Base central do personagem)
    float screenCollisionX = newX + playerWidth / 2.0f;
    float screenCollisionY = p->position.y + playerHeight;

    // 2. CONVERSÃO: TELA -> IMAGEM DE COLISÃO
    float imageX = (screenCollisionX - scene->offsetMap.x) / scene->mapScale;
    float imageY = (screenCollisionY - scene->offsetMap.y) / scene->mapScale;

    // Colisão Horizontal: Verifica o novo X com o Y convertido
    if (!collisionpixel(&scene->collision_image, imageX, imageY))
    {
        p->position.x = newX;
    }

    // --- Colisão Vertical ---

    // 1. Ponto de Colisão na TELA (Base central do personagem, nova Y)
    screenCollisionX = p->position.x + playerWidth / 2.0f; // X atual
    screenCollisionY = newY + playerHeight;                // Novo Y

    // 2. CONVERSÃO: TELA -> IMAGEM DE COLISÃO
    imageX = (screenCollisionX - scene->offsetMap.x) / scene->mapScale;
    imageY = (screenCollisionY - scene->offsetMap.y) / scene->mapScale;

    // Colisão Vertical: Verifica o X atual com o novo Y convertido
    if (!collisionpixel(&scene->collision_image, imageX, imageY))
    {
        p->position.y = newY;
    }
}

void drawPlayer(Player *p)
{
    DrawTextureV(p->texture, p->position, WHITE);
    // --- ADICIONE ESTE CÓDIGO DE DEBUG ---
    const float playerHeight = 32.0f; // Assumindo 32
    const float playerWidth = 32.0f;  // Assumindo 32

    // Calcula o ponto de colisão que o UpdatePlayer está mirando (Base central)
    float debugX = p->position.x + playerWidth / 2.0f;
    float debugY = p->position.y + playerHeight;

    // Desenha um pequeno círculo vermelho no ponto exato de colisão
    DrawCircle((int)debugX, (int)debugY, 3, RED);
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