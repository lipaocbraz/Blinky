#ifndef SCENE_H
#define SCENE_H
#define TILE_SIZE 16
#define HEIGHT 21
#define WIDTH 42
#define WINDOW_HEIGHT (HEIGHT * TILE_SIZE)
#define WINDOW_WIDTH (WIDTH * TILE_SIZE)

// Declaração de Funções da lib aqui
void drawscene();
void InitScene();
void UnloadScene();
// Fim de funções

#endif