#ifndef PLAYER_H
#define PLAYER_H
#include <raylib.h>

typedef struct Player
{
    Texture2D texture;
    Vector2 position;
    float speed;
} Player;

void initPlayer(Player *p, const char *texturePath);
void updatePlayer(Player *p);
void drawPlayer(Player *p);
void unloadPlayer(Player *p);

#endif