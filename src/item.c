#include "player.h"
#include "raylib.h"
#include "item.h"
#define ITEM_XHITBOX 100
#define ITEM_YHITBOX 100


void InitItem(Item* item, const char* texturePath, Vector2 position)
{
    item->texture = LoadTexture(texturePath);
    item->position = position;
    item->Xhitbox = ITEM_XHITBOX;
    item->Yhitbox = ITEM_YHITBOX;
    item->collected = false;

    TraceLog(LOG_INFO, "ITEM: Item inicializado em (X: %.0f, Y: %.0f).", position.x, position.y);
}

void DrawItem(Item* item)
{
    if (!item->collected)
    {
        DrawTexture(item->texture, (int)item->position.x, (int)item->position.y, WHITE);
    }
}

bool CheckItemCollision(Item* item, Rectangle playerRect, Player* player)
{
    if (item->collected)
        return false;

    Rectangle itemRect = {
        item->position.x,
        item->position.y,
        item->Xhitbox,
        item->Yhitbox
    };

    if (CheckCollisionRecs(playerRect, itemRect))
    {
        item->collected = true;
        TraceLog(LOG_INFO, "ITEM: Item coletado em (X: %.0f, Y: %.0f).", item->position.x, item->position.y);
        item->collected = true;
        player->keysCollected += 1;
        return true;
    }

    return false;
}
