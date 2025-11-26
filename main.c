// Arquivo: main.c (AJUSTADO)

#include <raylib.h>
#include <scene.h>
#include "game.h"
#include "player.h"
#include "enemy.h"
#include "item.h"
#include <math.h> // Para fminf
#include <time.h>
#include <float.h> // Necessário para DBL_MAX
#include "score.h" // Alterado de <score.h> para "score.h" para garantir o include correto
#include <string.h>
#include <stdio.h>

// Sempre que precisar compilar para gerar um novo executável com as alterações, o comando é:
// gcc main.c src/*.c -I include -I /opt/homebrew/include -o blinky.exe -L /opt/homebrew/lib -lraylib -std=c99
// MARGEM DE ERRO DA FUNÇÃO DE MAPEAMENTO DE PIXELS: X=~-36px, Y=~-36px (monitor 24 polegadas)

// Variáveis do usuário (Nomes mantidos)
double start_time = 0.0;
bool scoreCalculated = false; // Flag para garantir que o tempo só seja medido uma vez
char scoreText[64];
char recordText[64];

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
    int cliques = 1;

    // REMOVIDO: clock_t inicio, fim; double segundos; (Substituído por start_time e GetTime())

    // Definição dos objetos do cenário (players, inimigos, itens, armas, etc.)
    Player hero;

    Enemy enemy1;
    Enemy enemy2;
    Enemy enemy3;
    Enemy enemy4;

    Item keyItem1;
    Item keyItem2;
    Item keyItem3;
    Item exit;

    exit.isDoor = true;
    enemy2.color = PURPLE;

    bool showDebug = true;

    while (!WindowShouldClose())
    {
        // =========================================================================
        // 1. BLOC O DE ATUALIZAÇÃO (UPDATE)
        // =========================================================================
        switch (currentScreen)
        {

        case TITLE:
        {

            if (IsKeyPressed(KEY_ENTER))
            {
                currentScreen = GAMEPLAY;
                InitScene(&map1, "assets/Cenario_medieval.png");
                InitItem(&exit, "assets/exitRotation.png", (Vector2){1070.0f, 964.0f});
                initPlayer(&hero, "assets/player.png", (Vector2){573.0f, 500.0f});

                TraceLog(LOG_INFO, "JOGO: Cena de Jogo iniciada.");

                // Inicio timer
                start_time = GetTime();
                scoreCalculated = false;

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
        break;

        case GAMEPLAY:
        {
            // O update do player foi corrigido em player.c para funcionar!
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
                TraceLog(LOG_INFO, "JOGO: Jogador coletou %i chaves!", hero.keysCollected);
            }
            if (CheckItemCollision(&keyItem2, hero.rectangleHitbox, &hero))
            {
                TraceLog(LOG_INFO, "JOGO: Jogador coletou %i chaves!", hero.keysCollected);
            }
            if (CheckItemCollision(&keyItem3, hero.rectangleHitbox, &hero))
            {
                TraceLog(LOG_INFO, "JOGO: Jogador coletou %i chaves!", hero.keysCollected);
            }

            if (hero.keysCollected >= 3)
            {
                if (CheckItemCollision(&exit, hero.rectangleHitbox, &hero))
                {
                    TraceLog(LOG_INFO, "JOGO: Jogador coletou a saída e venceu o jogo!");
                    currentScreen = WINNING;
                }
            }

            // Colisões com inimigos (Simplificado para uma única verificação)
            if (CheckPlayerEnemyCollision(&hero, &enemy1) ||
                CheckPlayerEnemyCollision(&hero, &enemy2) ||
                CheckPlayerEnemyCollision(&hero, &enemy3) ||
                CheckPlayerEnemyCollision(&hero, &enemy4))
            {
                TraceLog(LOG_INFO, "Player colidiu com inimigo!");
                currentScreen = LOSING;
            }
        }
        break;

        case LOSING:
        case WINNING: // Aplica a lógica de score para ambas as telas
        {
            if (!scoreCalculated)
            {
                // Variável do usuário 'start_time' mantida
                double finaltime = GetTime() - start_time;

                // Funções do score agora usam double
                saveNewScore(finaltime);

                // Variáveis de texto do usuário 'scoreText' e 'recordText' mantidas
                snprintf(scoreText, 64, "Seu tempo: %.3f segundos", finaltime);

                snprintf(recordText, 64, "Ranking Atualizado!");

                scoreCalculated = true; // Flag ativada
                TraceLog(LOG_INFO, "SCORE: Tempo final calculado: %.3f", finaltime);
            }

            if (IsKeyPressed(KEY_DELETE) || IsKeyPressed(KEY_P))
            {
                // A ação de Unload é feita fora do loop principal, após o switch
                break; // Sai do case.
            }
        }
        break;

        } // Fim do switch de UPDATE

        // =========================================================================
        // 2. BLOC O DE DESENHO (DRAW) - CORRIGIDO: Fora do switch de UPDATE
        // =========================================================================
        BeginDrawing();
        ClearBackground(RAYWHITE); // Limpa a tela

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
            int xTitulo = currentW / 2 - MeasureText(titulo, fontSizeTitulo) / 2;
            int yTitulo = currentH / 4;

            DrawText(titulo, xTitulo, yTitulo, fontSizeTitulo, DARKBLUE);

            // 2. Centralização da Instrução:
            int xInstrucao = currentW / 2 - MeasureText(instrucao, fontSizeInstrucao) / 2;
            int yInstrucao = currentH / 2;

            DrawText(instrucao, xInstrucao, yInstrucao, fontSizeInstrucao, BLACK);
        }
        break;

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

            if (hero.keysCollected >= 3)
            {
                DrawItem(&exit);
                TraceLog(LOG_INFO, "Porta a mostra!!");
            }

            // NOVO: DESENHO DO TIMER CENTRALIZADO
            double segundos = GetTime() - start_time;
            char timerText[64];
            snprintf(timerText, 64, "Tempo: %.3f s", segundos);

            int fontSize = 30;
            int textWidth = MeasureText(timerText, fontSize);
            int xPos = (GetScreenWidth() / 2) - (textWidth / 2);
            int yPos = 20; // Perto do topo

            DrawText(timerText, xPos, yPos, fontSize, LIME);
        }
        break;

        case LOSING:
        {
            int currentW = GetScreenWidth();
            int currentH = GetScreenHeight();

            const char *titulo = "GAME OVER";
            int fontSizeTitulo = 40;
            const char *instrucao = "APERTE 'DELETE' PARA SAIR ou 'P' para o Título";
            int fontSizeInstrucao = 20;

            // 1. Centralização do Título:
            int xTitulo = currentW / 2 - MeasureText(titulo, fontSizeTitulo) / 2;
            int yTitulo = currentH / 4;

            DrawText(titulo, xTitulo, yTitulo, fontSizeTitulo, RED);

            // 2. Exibição do Score (Variável do usuário 'scoreText')
            int fontSizeScore = 30;
            int xScore = currentW / 2 - MeasureText(scoreText, fontSizeScore) / 2;
            int yScore = currentH / 2;
            DrawText(scoreText, xScore, yScore, fontSizeScore, RED);

            // 3. Exibição do Recorde (Variável do usuário 'recordText')
            int fontSizeRecorde = 25;
            int xRecorde = currentW / 2 - MeasureText(recordText, fontSizeRecorde) / 2;
            int yRecorde = currentH / 2 + 50;
            DrawText(recordText, xRecorde, yRecorde, fontSizeRecorde, GOLD);

            // 4. Instrução
            int xInstrucao = currentW / 2 - MeasureText(instrucao, fontSizeInstrucao) / 2;
            int yInstrucao = currentH - 50;
            DrawText(instrucao, xInstrucao, yInstrucao, fontSizeInstrucao, WHITE);
        }
        break;

        case WINNING:
        {
            int currentW = GetScreenWidth();
            int currentH = GetScreenHeight();

            const char *titulo = "VOCÊ ESCAPOU!!";
            int fontSizeTitulo = 40;
            const char *instrucao = "APERTE 'DELETE' PARA SAIR ou 'P' para o Título";
            int fontSizeInstrucao = 20;

            // 1. Centralização do Título:
            int xTitulo = currentW / 2 - MeasureText(titulo, fontSizeTitulo) / 2;
            int yTitulo = currentH / 4;

            DrawText(titulo, xTitulo, yTitulo, fontSizeTitulo, GREEN);

            // 2. Exibição do Score (Variável do usuário 'scoreText')
            int fontSizeScore = 30;
            int xScore = currentW / 2 - MeasureText(scoreText, fontSizeScore) / 2;
            int yScore = currentH / 2;
            DrawText(scoreText, xScore, yScore, fontSizeScore, WHITE);

            // 3. Exibição do Recorde (Variável do usuário 'recordText')
            int fontSizeRecorde = 25;
            int xRecorde = currentW / 2 - MeasureText(recordText, fontSizeRecorde) / 2;
            int yRecorde = currentH / 2 + 50;
            DrawText(recordText, xRecorde, yRecorde, fontSizeRecorde, GOLD);

            // 4. Instrução
            int xInstrucao = currentW / 2 - MeasureText(instrucao, fontSizeInstrucao) / 2;
            int yInstrucao = currentH - 50;
            DrawText(instrucao, xInstrucao, yInstrucao, fontSizeInstrucao, WHITE);
        }
        break;

        } // Fim do switch de DRAW

        EndDrawing();

        // -------------------------------------------------------------------------
        // Ação de Unload/Fechar (Apenas após o jogo terminar)
        // -------------------------------------------------------------------------

        if (currentScreen == LOSING || currentScreen == WINNING)
        {
            if (IsKeyPressed(KEY_DELETE))
            {
                // Sai do loop principal
                break;
            }
            if (IsKeyPressed(KEY_P))
            {
                // Faz unload dos assets antes de voltar para o Título
                UnloadScene(&map1);
                unloadPlayer(&hero);
                // Unload de inimigos, itens, etc. (adicione se necessário)
                currentScreen = TITLE;
            }
        }
    } // Fim do while (!WindowShouldClose())

    CloseWindow();
    return 0;
}