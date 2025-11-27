#include "enemy.h"
#include "raylib.h"
#include "player.h"
#define MAIN_XHITBOX 32
#define MAIN_YHITBOX 27
#define MAIN_HEIGHT 32 //56
#define MAIN_WIDTH 32 //56

// 0.03f - Muito rápido (33 FPS de animação)
// 0.05f - Rápido (20 FPS de animação)
// 0.08f - Normal (12.5 FPS de animação)
// 0.15f - Devagar (6.6 FPS de animação)
// 0.25f - Muito devagar (4 FPS de animação)

// Inicializa um inimigo com vários assets diferentes para animação, velocidade e posição inicial
void InitEnemy(Enemy *enemy, Vector2 startPos, float speed, const char *firstFramePath)
{
    // Largura e altura definidos na constante do cabeçalho da classe
    enemy->position = startPos;
    enemy->velocity = (Vector2){0, 0};
    enemy->speed = speed;
    enemy->Xhitbox = MAIN_XHITBOX;
    enemy->Yhitbox = MAIN_YHITBOX;
    enemy->active = true;
    enemy->color = WHITE;
    enemy->spriteHeight = MAIN_HEIGHT;
    enemy->spriteWidth = MAIN_WIDTH;
    
    //Frames, movimentação e sprites
    enemy->frameQtd = 12;
    enemy->currentFrameIndex = 0;
    enemy->currentFrameSheetLine = 0;
    enemy->frameTime = 0.05f;
    enemy->frameTimer = 0.0f;
    enemy->flipX = false;
    enemy->texture = LoadTexture(firstFramePath);
    enemy->movingForward = true;
    enemy->framePosition = 
    
    // Primeiro waypoint é a posição inicial
    enemy->waypoints[0] = startPos;
    enemy->waypointCount = 1;
    enemy->waypointCount = 0;
    enemy->currentWaypoint = 0;
}

void AddWaypoint(Enemy *enemy, Vector2 waypoint)
{
    if (enemy->waypointCount < MAX_WAYPOINTS)
    {
        enemy->waypoints[enemy->waypointCount] = waypoint;
        enemy->waypointCount++;
    }
}

// void UpdateEnemy(Enemy* enemy, CollisionMap* colMap, float deltaTime)
void UpdateEnemy(Enemy *enemy, float deltaTime)
{

    if (!enemy->active || enemy->waypointCount < 2)
        return;

    // Pega o waypoint alvo
    Vector2 target = enemy->waypoints[enemy->currentWaypoint];

    // Calcula direção até o waypoint
    Vector2 direction = {
        target.x - enemy->position.x,
        target.y - enemy->position.y};

    float distance = sqrtf(direction.x * direction.x + direction.y * direction.y);

    // Se chegou perto do waypoint, avança para o próximo
    if (distance < 5.0f)
    {
        if (enemy->movingForward)
        {
            enemy->currentWaypoint++;
            if (enemy->currentWaypoint >= enemy->waypointCount)
            {
                enemy->currentWaypoint = enemy->waypointCount - 2;
                enemy->movingForward = false;
            }
        }
        else
        {
            enemy->currentWaypoint--;
            if (enemy->currentWaypoint < 0)
            {
                enemy->currentWaypoint = 1;
                enemy->movingForward = true;
            }
        }
        return;
    }

    // Se passou tempo suficiente (frameTime), troca de sprite
    enemy->frameTimer += deltaTime;
    if (enemy->frameTimer >= enemy->frameTime)
    {
        enemy->frameTimer = 0.0f;        
        enemy->currentFrameIndex++;
    }

    // Normaliza a direção
    direction.x /= distance;
    direction.y /= distance;

    // Calcula nova posição
    Vector2 newPosition = {
        enemy->position.x + direction.x * enemy->speed * deltaTime,
        enemy->position.y + direction.y * enemy->speed * deltaTime};

    // Cria retângulo para testar colisão
    Rectangle newRect = {
        newPosition.x,
        newPosition.y,
        enemy->Xhitbox,
        enemy->Yhitbox};

    DrawRectangleLinesEx(newRect, 10, GREEN);

    // Atualiza a linha do frameSheet na qual o inimigo se encontra
    if(enemy->currentFrameIndex/5 == 1){
        enemy->currentFrameSheetLine++;
    }
    else if(enemy->currentFrameIndex/11==1){
        enemy->currentFrameSheetLine++;
    }
    if(enemy->currentFrameIndex > enemy->frameQtd)
    {
        enemy->currentFrameIndex = 0;  // Volta para o primeiro sprite
        enemy->currentFrameSheetLine=0;
    }

    enemy->position = newPosition;
    enemy->velocity = (Vector2){direction.x * enemy->speed, direction.y * enemy->speed};
}

void DrawEnemy(Enemy *enemy, bool debug)
{
    Vector2 framePosition = function_line_frameSheet(enemy);

    if (!enemy->active)
        return;

    // Desenha o inimigo
    Rectangle spriteRectangle = {
        framePosition.x,
        framePosition.y,           
        enemy->spriteWidth,    
        enemy->spriteHeight   
    };
    
    DrawTextureRec(enemy->texture, spriteRectangle, enemy->position, WHITE);

    // 🔨Desenha borda (Hitbox de debug)
    Rectangle hitbox = {
        enemy->position.x,
        enemy->position.y,
        enemy->Xhitbox,
        enemy->Yhitbox};
    DrawRectangleLinesEx(hitbox, 2, RED);

    // 🔨 Debug: desenha rota de patrulha
    if (debug && enemy->waypointCount > 0)
    {
        Vector2 target = enemy->waypoints[enemy->currentWaypoint];
        DrawLineEx(
            (Vector2){enemy->position.x + enemy->Xhitbox / 2, enemy->position.y + enemy->Yhitbox / 2},
            target,
            2, YELLOW);

        // Desenha waypoints
        for (int i = 0; i < enemy->waypointCount; i++)
        {
            DrawCircleV(enemy->waypoints[i], 5, ORANGE);
            if (i == enemy->currentWaypoint)
            {
                DrawCircleV(enemy->waypoints[i], 8, YELLOW);
            }
        }

        // Desenha linhas entre waypoints
        for (int i = 0; i < enemy->waypointCount - 1; i++)
        {
            DrawLineEx(enemy->waypoints[i], enemy->waypoints[i + 1], 1, ORANGE);
        }
    }

}

bool CheckPlayerEnemyCollision(Player *player, Enemy *enemy)
{
    if (!enemy->active)
        return false;

    // Envolve as posições e tamanhos dos elementos (hitbox != sprite)
    Rectangle playerRect = {
        player->position.x,
        player->position.y,
        player->Xhitbox,
        player->Yhitbox};

    Rectangle enemyRect = {
        enemy->position.x,
        enemy->position.y,
        enemy->Xhitbox,
        enemy->Yhitbox};

    return CheckCollisionRecs(playerRect, enemyRect);
}

Vector2 function_line_frameSheet(Enemy *enemy){

    Vector2 frameSheetMatrix[10][10], framePosition;
    int squareSize = 32; //Lado do quadrado

    //A cada 6 frames, mais 56 nos eixos X e Y
    int spritePositionX = 16 + 64*enemy->currentFrameIndex;
    int spritePositionY = 16 + 64*enemy->currentFrameSheetLine;

    return framePosition = (Vector2) {spritePositionX, spritePositionY};
}
