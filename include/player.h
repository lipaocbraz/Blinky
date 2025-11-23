#ifndef PLAYER_H
#define PLAYER_H
#include <raylib.h>
#include "scene.h"
#include "enemy.h" 

typedef struct Player
{
    Texture2D texture;
    Vector2 position;
    float speed;

    float Xhitbox;   // Largura da hitbox
    float Yhitbox;  // Altura da hitbox

    Rectangle rectangleHitbox; // Hitbox do jogador
} Player;

bool CheckPlayerEnemyCollision(Player* player, Enemy* enemy);
void initPlayer(Player *p, const char *texturePath, Vector2 startPos);
void UpdatePlayer(Player *p, Scene *scene);
void drawPlayer(Player *p);
void unloadPlayer(Player *p);

#endif