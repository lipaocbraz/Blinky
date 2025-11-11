#ifndef SCENE_H
#define SCENE_H
#include "raylib.h"

typedef struct Scene
{
    Texture2D map1;

} Scene;

// Declaração de Funções da lib aqui
void DrawScene(Scene *scene);
void InitScene(Scene *scene, const char *imagePath);
void UnloadScene(Scene *scene);
// Fim de funções

#endif