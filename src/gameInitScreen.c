#include "game.h"
#include "player.h"
#include "enemy.h"
#include "item.h"
#include "raylib.h"

typedef struct {
    GameScreen currentScreen;
    Scene map1;
    bool showDebug;
    int cliques;
} screenState;

screenState iniciandoGame() {
    screenState state;
    state.currentScreen = TITLE;
    state.cliques = 1;
    state.showDebug = true;

    int WINDOW_WIDTH = GetMonitorWidth(0);
    int WINDOW_HEIGHT = GetMonitorHeight(0);

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "blinky");
    SetTargetFPS(60);

    return state;
}
