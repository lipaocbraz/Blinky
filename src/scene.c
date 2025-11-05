#include <scene.h>
#include <raylib.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

int map[HEIGHT][WIDTH] = {
    {0, 1, 0, 2, 3, 0, 1, 0, 2, 3, 0, 1, 0, 2, 3, 0, 1, 0, 2, 3, 0, 1, 0, 2, 3, 0, 1, 0, 2, 3, 0, 1, 0, 2, 30, 1, 0, 2, 3},
    {1, 0, 3, 0, 1, 2, 0, 3, 0, 1, 2, 0, 3, 0, 1, 2, 0, 3, 0, 1, 2, 0, 3, 0, 1, 2, 0, 3, 0, 1, 2, 0, 3, 0, 1, 2, 0, 3, 0, 1},
    {0, 2, 1, 0, 3, 0, 2, 1, 0, 3, 0, 2, 1, 0, 3, 0, 2, 1, 0, 3, 0, 2, 1, 0, 3, 0, 2, 1, 0, 3, 0, 2, 1, 0, 3, 0, 2, 1, 0, 3},
    {3, 0, 1, 2, 0, 3, 0, 1, 2, 0, 3, 0, 1, 2, 0, 3, 0, 1, 2, 0, 3, 0, 1, 2, 0, 3, 0, 1, 2, 0, 3, 0, 1, 2, 0, 3, 0, 1, 2, 0},
    {0, 3, 0, 1, 2, 0, 3, 0, 1, 2, 0, 3, 0, 1, 2, 0, 3, 0, 1, 2, 0, 3, 0, 1, 2, 0, 3, 0, 1, 2, 0, 3, 0, 1, 2, 0, 3, 0, 1, 2},
    {1, 0, 2, 0, 3, 1, 0, 2, 0, 3, 1, 0, 2, 0, 3, 1, 0, 2, 0, 3, 1, 0, 2, 0, 3, 1, 0, 2, 0, 3, 1, 0, 2, 0, 3, 1, 0, 2, 0, 3},
    {0, 3, 1, 0, 2, 0, 3, 1, 0, 2, 0, 3, 1, 0, 2, 0, 3, 1, 0, 2, 0, 3, 1, 0, 2, 0, 3, 1, 0, 2, 0, 3, 1, 0, 2, 0, 3, 1, 0, 2},
    {2, 0, 3, 1, 0, 2, 0, 3, 1, 0, 2, 0, 3, 1, 0, 2, 0, 3, 1, 0, 2, 0, 3, 1, 0, 2, 0, 3, 1, 0, 2, 0, 3, 1, 0, 2, 0, 3, 1, 0},
    {0, 1, 0, 2, 3, 0, 1, 0, 2, 3, 0, 1, 0, 2, 3, 0, 1, 0, 2, 3, 0, 1, 0, 2, 3, 0, 1, 0, 2, 3, 0, 1, 0, 2, 3, 0, 1, 0, 2, 3},
    {1, 0, 3, 0, 1, 2, 0, 3, 0, 1, 2, 0, 3, 0, 1, 2, 0, 3, 0, 1, 2, 0, 3, 0, 1, 2, 0, 3, 0, 1, 2, 0, 3, 0, 1, 2, 0, 3, 0, 1},
    {0, 2, 1, 5, 7, 7, 7, 1, 0, 3, 0, 2, 1, 0, 3, 0, 2, 1, 0, 3, 0, 2, 1, 0, 3, 0, 2, 1, 0, 3, 0, 2, 1, 0, 3, 0, 2, 1, 0, 3},
    {3, 0, 1, 10, 0, 3, 0, 1, 2, 0, 3, 0, 1, 2, 0, 3, 0, 1, 2, 0, 3, 0, 1, 2, 0, 3, 0, 1, 2, 0, 3, 0, 1, 2, 0, 3, 0, 1, 2, 0},
    {0, 3, 0, 10, 2, 0, 3, 0, 1, 2, 0, 3, 0, 1, 2, 0, 3, 0, 1, 2, 0, 3, 0, 1, 2, 0, 3, 0, 1, 2, 0, 3, 0, 1, 2, 0, 3, 0, 1, 2},
    {7, 7, 7, 9, 3, 1, 0, 2, 0, 3, 1, 0, 2, 0, 3, 1, 0, 2, 0, 3, 1, 0, 2, 0, 3, 1, 0, 2, 0, 3, 1, 0, 2, 0, 3, 1, 0, 2, 0, 3},
    {0, 3, 1, 0, 2, 0, 3, 1, 0, 2, 0, 3, 1, 0, 2, 0, 3, 1, 0, 2, 0, 3, 1, 0, 2, 0, 3, 1, 0, 2, 0, 3, 1, 0, 2, 0, 3, 1, 0, 2},
    {2, 0, 3, 1, 0, 2, 0, 3, 1, 0, 2, 0, 3, 1, 0, 2, 0, 3, 1, 0, 2, 0, 3, 1, 0, 2, 0, 3, 1, 0, 2, 0, 3, 1, 0, 2, 0, 3, 1, 0},
    {0, 1, 0, 2, 3, 0, 1, 0, 2, 3, 0, 1, 0, 2, 3, 0, 1, 0, 2, 3, 0, 1, 0, 2, 3, 0, 1, 0, 2, 3, 0, 1, 0, 2, 3, 0, 1, 0, 2, 3},
    {1, 0, 3, 0, 1, 2, 0, 3, 0, 1, 2, 0, 3, 0, 1, 2, 0, 3, 0, 1, 2, 0, 3, 0, 1, 2, 0, 3, 0, 1, 2, 0, 3, 0, 1, 2, 0, 3, 0, 1},
    {0, 2, 1, 0, 3, 0, 2, 1, 0, 3, 0, 2, 1, 0, 3, 0, 2, 1, 0, 3, 0, 2, 1, 0, 3, 0, 2, 1, 0, 3, 0, 2, 1, 0, 3, 0, 2, 1, 0, 3},
    {3, 0, 1, 2, 0, 3, 0, 1, 2, 0, 3, 0, 1, 2, 0, 3, 0, 1, 2, 0, 3, 0, 1, 2, 0, 3, 0, 1, 2, 0, 3, 0, 1, 2, 0, 3, 0, 1, 2, 0}};

static Texture2D floor_0;
static Texture2D floor_1;
static Texture2D floor_2;
static Texture2D floor_3;
static Texture2D flowers;
static Texture2D street_0;
static Texture2D street_1;
static Texture2D street_2;
static Texture2D street_3;
static Texture2D street_4;
static Texture2D street_5;

void InitScene()
{
    floor_0 = LoadTexture("assets/sprints/Default/tiles/tile_0000.png");
    floor_1 = LoadTexture("assets/sprints/Default/tiles/tile_0017.png");
    floor_2 = LoadTexture("assets/sprints/Default/tiles/tile_0019.png");
    floor_3 = LoadTexture("assets/sprints/Default/tiles/tile_0051.png");
    flowers = LoadTexture("assets/sprints/Default/tiles/tile_0068.png");
    street_0 = LoadTexture("assets/sprints/Default/tiles/tile_0085.png");
    street_1 = LoadTexture("assets/sprints/Default/tiles/tile_0086.png");
    street_2 = LoadTexture("assets/sprints/Default/tiles/tile_0087.png");
    street_3 = LoadTexture("assets/sprints/Default/tiles/tile_0102.png");
    street_4 = LoadTexture("assets/sprints/Default/tiles/tile_0103.png");
    street_5 = LoadTexture("assets/sprints/Default/tiles/tile_0104.png");
}

void drawscene()
{
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            Texture2D tile;
            switch (map[i][j])
            {
            case 0:
                tile = floor_0;
                break;
            case 1:
                tile = floor_1;
                break;
            case 2:
                tile = floor_2;
                break;
            case 3:
                tile = floor_3;
                break;
            case 4:
                tile = flowers;
                break;
            case 5:
                tile = street_0;
                break;
            case 6:
                tile = street_1;
                break;
            case 7:
                tile = street_2;
                break;
            case 8:
                tile = street_3;
                break;
            case 9:
                tile = street_4;
                break;
            case 10:
                tile = street_5;
                break;
            }
            DrawTexture(tile, j * TILE_SIZE, i * TILE_SIZE, WHITE);
        }
    }
}

void UnloadScene()
{
    UnloadTexture(floor_0);
    UnloadTexture(floor_1);
    UnloadTexture(floor_2);
    UnloadTexture(floor_3);
}
