#ifndef SCENE_H
#define SCENE_H
#define TILE_SIZE 16
#define HEIGHT 20
#define WIDTH 40
#define WINDOW_HEIGHT (HEIGHT * TILE_SIZE)
#define WINDOW_WIDTH (WIDTH * TILE_SIZE)

// Declaração de Funções da lib aqui
void drawscene();
void InitScene();
void UnloadScene();
// Fim de funções

#endif