#ifndef ENTITY_H
#define ENTITY_H

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

    bool isInitiated;
} entityState;

/**
 * @brief Inicializa o estado de todas as entidades do jogo.
 * @return entityState inicializada.
 */
entityState iniciandoEntidades();
bool iniciandoInimigos(entityState *entityState);

#endif 