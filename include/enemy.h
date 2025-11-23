#ifndef ENEMY_H
#define ENEMY_H

#include "raylib.h"
#include "raymath.h"
//#include "collision_map.h"

#define MAX_WAYPOINTS 10
#define MAX_ENEMIES 50

// Estrutura do inimigo
typedef struct {

    Texture2D texture;
    Vector2 position;
    Vector2 velocity;
    float speed;
    float Xhitbox;
    float Yhitbox;
    
    // Sistema de patrulha
    Vector2 waypoints[MAX_WAYPOINTS];
    int waypointCount;
    int currentWaypoint;
    bool movingForward;
    
    Rectangle currentFrame;
    int frameCount;
    int currentFrameIndex;
    float frameTime;
    float frameTimer;
    bool flipX;  // Para virar o sprite (esquerda/direita)
    
    bool active;
    Color color;
} Enemy;

// Inicializa um inimigo
void InitEnemy(Enemy* enemy, Vector2 startPos, float speed, const char* firstFramePath);

// Adiciona um ponto de patrulha ao inimigo
void AddWaypoint(Enemy* enemy, Vector2 waypoint);

// Atualiza a lógica do inimigo (movimento e patrulha) (código correto, com o objeto colMap: void UpdateEnemy(Enemy* enemy, CollisionMap* colMap, float deltaTime);)
void UpdateEnemy(Enemy* enemy, float deltaTime);

// Desenha o inimigo na tela
void DrawEnemy(Enemy* enemy, bool debug);

// Verifica colisão entre o inimigo e um retângulo
bool CheckEnemyCollision(Enemy* enemy, Rectangle rect);

#endif 