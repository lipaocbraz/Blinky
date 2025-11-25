#include <raylib.h>
#include <scene.h>
#include "game.h"
#include "player.h"
#include "enemy.h"
#include "item.h"
#include <math.h> // Para fminf

// Sempre que precisar compilar para gerar um novo executável com as alterações, o comando é:
// gcc main.c src/*.c -I include -o blinky.exe -lraylib -lopengl32 -lgdi32 -lwinmm
// MARGEM DE ERRO DA FUNÇÃO DE MAPEAMENTO DE PIXELS: X=~-36px, Y=~-36px (monitor 24 polegadas)

int main(void)
{

    // Configurações da Janela
    int WINDOW_WIDTH = GetMonitorWidth(0);
    int WINDOW_HEIGHT = GetMonitorHeight(0);

    // A janela é iniciada com currentScreen = TITLE. Ao entrar no loop, os dois casos TITLE do switch são
    // acionados sequencialmente, até que o jogador pressione ENTER, mudando currentScreen para GAMEPLAY.
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Blinky");
    GameScreen currentScreen = TITLE;
    SetTargetFPS(60);
    Scene map1;
    int cliques = 1, coletas = 1;

    // Definição dos objetos do cenário (players, inimigos, itens, armas, etc.)
    Player hero;

    Enemy enemy1;
    Enemy enemy2;
    Enemy enemy3;
    Enemy enemy4;

    Item keyItem1;
    Item keyItem2;
    Item keyItem3;
    enemy2.color = PURPLE;

    bool showDebug = true;

    while (!WindowShouldClose())
    {
        switch (currentScreen)
        {

        case TITLE:
        {

            if (IsKeyPressed(KEY_ENTER))
            {
                currentScreen = GAMEPLAY;
                InitScene(&map1, "assets/Cenario_medieval.png");
                initPlayer(&hero, "assets/player.png", (Vector2){1573.0f, 189.0f});

                TraceLog(LOG_INFO, "JOGO: Cena de Jogo iniciada.");

                // Inimigo[1]
                InitEnemy(&enemy1, (Vector2){221.0f, 466.0f}, 100.0f, "assets/ghost.jpg"); 
                AddWaypoint(&enemy1, (Vector2){422.0f, 633.0f}); 
                AddWaypoint(&enemy1, (Vector2){628.0f, 772.0f}); 
                AddWaypoint(&enemy1, (Vector2){864.0f, 858.0f}); 
                AddWaypoint(&enemy1, (Vector2){1125.0f, 914.0f}); 
                AddWaypoint(&enemy1, (Vector2){1295.0f, 849.0f}); 
                AddWaypoint(&enemy1, (Vector2){1509.0f, 691.0f}); 
                AddWaypoint(&enemy1, (Vector2){1633.0f, 660.0f}); 

                // Inimigo[2]
                InitEnemy(&enemy2, (Vector2){1370.0f, 310.0f}, 80.0f, "assets/ghost.jpg"); 
                AddWaypoint(&enemy2, (Vector2){1255.0f, 397.0f}); 
                AddWaypoint(&enemy2, (Vector2){1147.0f, 448.0f}); 
                AddWaypoint(&enemy2, (Vector2){1331.0f, 522.0f}); 
                AddWaypoint(&enemy2, (Vector2){1211.0f, 451.0f}); 
                AddWaypoint(&enemy2, (Vector2){1077.0f, 412.0f}); 
                AddWaypoint(&enemy2, (Vector2){953.0f, 352.0f}); 
                AddWaypoint(&enemy2, (Vector2){959.0f, 211.0f}); 

                // Inimigo[3]
                InitEnemy(&enemy3, (Vector2){916.0f, 298.0f}, 80.0f, "assets/ghost.jpg"); 
                AddWaypoint(&enemy3, (Vector2){761.0f, 391.0f}); 
                AddWaypoint(&enemy3, (Vector2){673.0f, 461.0f}); 
                AddWaypoint(&enemy3, (Vector2){608.0f, 389.0f}); 
                AddWaypoint(&enemy3, (Vector2){608.0f, 482.0f}); 
                AddWaypoint(&enemy3, (Vector2){503.0f, 566.0f}); 
                AddWaypoint(&enemy3, (Vector2){419.0f, 654.0f}); 
                AddWaypoint(&enemy3, (Vector2){534.0f, 722.0f}); 

                // Inimigo[4]
                InitEnemy(&enemy4, (Vector2){1516.0f, 692.0f}, 80.0f, "assets/ghost.jpg"); 
                AddWaypoint(&enemy4, (Vector2){1419.0f, 596.0f}); 
                AddWaypoint(&enemy4, (Vector2){1300.0f, 487.0f});
                AddWaypoint(&enemy4, (Vector2){1559.0f, 682.0f});
                AddWaypoint(&enemy4, (Vector2){1749.0f, 685.0f});
                AddWaypoint(&enemy4, (Vector2){1851.0f, 585.0f});
                AddWaypoint(&enemy4, (Vector2){1863.0f, 498.0f});

                // Item (chave)
                InitItem(&keyItem1, "assets/keyItem.png", (Vector2){1800.0f, 500.0f});
                InitItem(&keyItem2, "assets/keyItem.png", (Vector2){955.0f, 215.0f});
                InitItem(&keyItem3, "assets/keyItem.png", (Vector2){1045.0f, 782.0f});

                TraceLog(LOG_INFO, "Inimigos inicializados.");
            }
        }
        case GAMEPLAY:
        {
            UpdatePlayer(&hero, &map1);
            UpdateEnemy(&enemy1, GetFrameTime());
            UpdateEnemy(&enemy2, GetFrameTime());
            UpdateEnemy(&enemy3, GetFrameTime());
            UpdateEnemy(&enemy4, GetFrameTime());

            // 🔨 Captura de clique do mouse para mapeamento de pixels!!
            Vector2 screenMouse = GetMousePosition();

            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                TraceLog(LOG_INFO, "%i. Coordenadas do Mapa: X: %.0f, Y: %.0f", cliques, screenMouse.x, screenMouse.y);
                cliques++;
            }

            // Verifica colisão do jogador com o item (chave)
            if (CheckItemCollision(&keyItem1, hero.rectangleHitbox, &hero))
            {
                TraceLog(LOG_INFO, "JOGO: Jogador coletou %i chaves!", coletas);
            }
            if (CheckItemCollision(&keyItem2, hero.rectangleHitbox, &hero))
            {
                TraceLog(LOG_INFO, "JOGO: Jogador coletou %i chaves!", coletas);
            }
            if (CheckItemCollision(&keyItem3, hero.rectangleHitbox, &hero))
            {
                TraceLog(LOG_INFO, "JOGO: Jogador coletou %i chaves!", coletas);
            }

            // Colisões com inimigos
            if (CheckPlayerEnemyCollision(&hero, &enemy1))
            {
                TraceLog(LOG_INFO, "Player colidiu com inimigo!");
                currentScreen = ENDING;
            }
            else if (CheckPlayerEnemyCollision(&hero, &enemy2))
            {
                TraceLog(LOG_INFO, "Player colidiu com inimigo!");
                currentScreen = ENDING;
            }
            else if (CheckPlayerEnemyCollision(&hero, &enemy3))
            {
                TraceLog(LOG_INFO, "Player colidiu com inimigo!");
                currentScreen = ENDING;
            }
            else if (CheckPlayerEnemyCollision(&hero, &enemy4))
            {
                TraceLog(LOG_INFO, "Player colidiu com inimigo!");
                currentScreen = ENDING;
            }
        }

        case ENDING:
        {
            if (IsKeyPressed(KEY_P))
            {
                UnloadScene(&map1);
            }
        }

            BeginDrawing();
            ClearBackground(BLACK);

            // Aqui temos a renderização de cada tela do jogo de fato
            switch (currentScreen)
            {
            case TITLE:
            {
                int currentW = GetScreenWidth();
                int currentH = GetScreenHeight();

                const char *titulo = "MEU JOGO BLINKY";
                int fontSizeTitulo = 40;

                const char *instrucao = "Pressione ENTER para JOGAR";
                int fontSizeInstrucao = 20;

                // 1. Centralização do Título:
                // Pos X = (Metade da Tela) - (Metade da Largura do Texto)
                int xTitulo = currentW / 2 - MeasureText(titulo, fontSizeTitulo) / 2;
                int yTitulo = currentH / 4;

                DrawText(titulo, xTitulo, yTitulo, fontSizeTitulo, DARKBLUE);

                // 2. Centralização da Instrução:
                int xInstrucao = currentW / 2 - MeasureText(instrucao, fontSizeInstrucao) / 2;
                int yInstrucao = currentH / 2;

                DrawText(instrucao, xInstrucao, yInstrucao, fontSizeInstrucao, BLACK);
            }
            break;

            // O segundo mapa deve ser adicionado aqui
            case GAMEPLAY:
            {
                DrawScene(&map1);
                drawPlayer(&hero);
                DrawEnemy(&enemy1, showDebug);
                DrawEnemy(&enemy2, showDebug);
                DrawEnemy(&enemy3, showDebug);
                DrawEnemy(&enemy4, showDebug);
                DrawItem(&keyItem1);
                DrawItem(&keyItem2);
                DrawItem(&keyItem3);
            }
            break;

            case ENDING:
            {
                int currentW = GetScreenWidth();
                int currentH = GetScreenHeight();

                const char *titulo = "GAME OVER";
                int fontSizeTitulo = 40;

                const char *instrucao = "APERTE 'DELETE' PARA SAIR";
                int fontSizeInstrucao = 20;

                // 1. Centralização do Título:
                // Pos X = (Metade da Tela) - (Metade da Largura do Texto)
                int xTitulo = currentW / 2 - MeasureText(titulo, fontSizeTitulo) / 2;
                int yTitulo = currentH / 4;

                DrawText(titulo, xTitulo, yTitulo, fontSizeTitulo, RED);
            }
            break;
            }

            EndDrawing();
        }
    }
    if (currentScreen == GAMEPLAY)
    {
        UnloadScene(&map1);
        unloadPlayer(&hero);
    }

    double score = GetTime();
    // Adicionar escrita em arquivo de score aqui

    CloseWindow();
    return 0;
}
