#include "game.h"
#include "player.h"
#include "enemy.h"
#include "item.h"

typedef struct {
    Player hero;

    Enemy enemy1;
    Enemy enemy2;
    Enemy enemy3;
    Enemy enemy4;

    Item keyItem1;
    Item keyItem2;
    Item keyItem3;
    Item exit;
} entityState;

entityState iniciandoEntidades() {
    entityState state;
    state.exit.isDoor = true;
    state.enemy2.color = PURPLE;

    return state;
}
