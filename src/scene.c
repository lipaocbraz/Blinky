#include <scene.h>
#include <raylib.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

void InitScene(Scene *scene, const char imagePath)
{
    scene->map1 = LoadTexture(imagePath);
}

void drawscene(Scene *scene)
{
    Drawtexture(scene->map1, 0, 0, WHITE);
}

void UnloadScene(Scene *scene)
{
    UnloadTexture(scene->map1);
}
