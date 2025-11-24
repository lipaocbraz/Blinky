#ifndef ITEM_H
#define ITEM_H
#include <raylib.h>
#include "scene.h"
#include "enemy.h" 

typedef struct {
    Texture2D texture;
    Vector2 position;
    float Xhitbox;
    float Yhitbox;
    bool collected;
} Item;

// Inicializa um item
void InitItem(Item* item, const char* texturePath, Vector2 position); 

// Desenha o item na tela
void DrawItem(Item* item);

// Verifica colisão entre o item e o jogador
bool CheckItemCollision(Item* item, Rectangle playerRect, Player *player);

#endif