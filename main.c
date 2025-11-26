// Arquivo: main.c (AJUSTADO)

#include <raylib.h>
#include <scene.h>
#include "game.h"
#include "player.h"
#include "enemy.h"
#include "item.h"
#include "score.h" // Alterado de <score.h> para "score.h" para garantir o include correto
#include "gameInitScreen.h"
#include "gameInitEntities.h"
#include <math.h> // Para fminf
#include <time.h>
#include <float.h> // Necessário para DBL_MAX
#include <string.h>
#include <stdio.h>

// Sempre que precisar compilar para gerar um novo executável com as alterações, o comando é:
// gcc main.c src/*.c -I include -I /opt/homebrew/include -o blinky.exe -L /opt/homebrew/lib -lraylib -std=c99

// Variáveis do usuário (Nomes mantidos)
double start_time = 0.0;
bool scoreCalculated = false; // Flag para garantir que o tempo só seja medido uma vez
char scoreText[64];
char recordText[64];

int main(void)
{
    screenState screenState = iniciandoGame();
    entityState entityState = iniciandoEntidades();

    while (!WindowShouldClose())
    {
        // =========================================================================
        // 1. BLOCO DE ATUALIZAÇÃO (UPDATE)
        // =========================================================================
        
        switch (screenState.currentScreen)
        {

            case INITIALIZE:
                {
                        {
                            InitScene(&screenState.map1, "assets/Cenario_medieval.png");
                            entityState.isInitiated=iniciandoInimigos(&entityState);
                            
                            // Inicio timer
                            start_time = GetTime();
                            scoreCalculated = false;
                            
                            TraceLog(LOG_INFO, "Inimigos inicializados.");
                            screenState.currentScreen = TITLE;
                        }
                }
                break;

            case GAMEPLAY:
                    {
                        UpdatePlayer(&entityState.hero, &screenState.map1);
                        UpdateEnemy(&entityState.enemy1, GetFrameTime());
                        UpdateEnemy(&entityState.enemy2, GetFrameTime());
                        UpdateEnemy(&entityState.enemy3, GetFrameTime());
                        UpdateEnemy(&entityState.enemy4, GetFrameTime());

                        // 🔨 Captura de clique do mouse para mapeamento de pixels!!
                        Vector2 screenMouse = GetMousePosition();

                        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                        {
                            TraceLog(LOG_INFO, "%i. Coordenadas do Mapa: X: %.0f, Y: %.0f", screenState.cliques, screenMouse.x, screenMouse.y);
                            screenState.cliques++;
                        }
                        // 🔨

                        // Verifica colisão do jogador com o item (chave)
                        if (CheckItemCollision(&entityState.keyItem1, entityState.hero.rectangleHitbox, &entityState.hero))
                        {
                            TraceLog(LOG_INFO, "JOGO: Jogador coletou %i chaves!", entityState.hero.keysCollected);
                        }
                        if (CheckItemCollision(&entityState.keyItem2, entityState.hero.rectangleHitbox, &entityState.hero))
                        {
                            TraceLog(LOG_INFO, "JOGO: Jogador coletou %i chaves!", entityState.hero.keysCollected);
                        }
                        if (CheckItemCollision(&entityState.keyItem3, entityState.hero.rectangleHitbox, &entityState.hero))
                        {
                            TraceLog(LOG_INFO, "JOGO: Jogador coletou %i chaves!", entityState.hero.keysCollected);
                        }

                        if (entityState.hero.keysCollected >= 3)
                        {
                            if (CheckItemCollision(&entityState.exit, entityState.hero.rectangleHitbox, &entityState.hero))
                            {
                                TraceLog(LOG_INFO, "JOGO: Jogador coletou a saída e venceu o jogo!");
                                screenState.currentScreen = WINNING;
                            }
                        }

                        // Colisões com inimigos (Simplificado para uma única verificação)
                        if (CheckPlayerEnemyCollision(&entityState.hero, &entityState.enemy1) ||
                            CheckPlayerEnemyCollision(&entityState.hero, &entityState.enemy2) ||
                            CheckPlayerEnemyCollision(&entityState.hero, &entityState.enemy3) ||
                            CheckPlayerEnemyCollision(&entityState.hero, &entityState.enemy4))
                        {
                            TraceLog(LOG_INFO, "Player colidiu com inimigo!");
                            screenState.currentScreen = LOSING;
                        }
                }
                break;

            case LOSING:
            case WINNING: // Aplica a lógica de score para ambas as telas
                    {
                        if (!scoreCalculated)
                        {
                            double finaltime = GetTime() - start_time;

                            saveTopScore(finaltime);
                            double recorde = LoadTopScore();

                            snprintf(scoreText, 64, "Seu tempo: %.3f segundos", finaltime);

                            if (recorde < DBL_MAX)
                            {
                                snprintf(recordText, 64, "Recorde: %.3f segundos", recorde);
                            }
                            else
                            {
                                strcpy(recordText, "Recorde: N/A");
                            }
                            scoreCalculated = true; // Flag ativada
                            TraceLog(LOG_INFO, "SCORE: Tempo final calculado: %.3f", finaltime);
                        }

                        if (IsKeyPressed(KEY_DELETE) || IsKeyPressed(KEY_P))
                        {
                            break;
                        }
                    }
            break;

        } // Fim do switch de UPDATE

        // =========================================================================
        // 2. BLOCO DE DESENHO (DRAW) - CORRIGIDO: Fora do switch de UPDATE
        // =========================================================================

        BeginDrawing();
        ClearBackground(RAYWHITE); // Limpa a tela

        // Aqui temos a renderização de cada tela do jogo de fato
        switch (screenState.currentScreen)
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
                    if(IsKeyDown(KEY_ENTER)){
                        screenState.currentScreen=GAMEPLAY;
                    }
            }
            break;

            case GAMEPLAY:
            {
                    DrawScene(&screenState.map1);
                    drawPlayer(&entityState.hero);
                    DrawEnemy(&entityState.enemy1, screenState.showDebug);
                    DrawEnemy(&entityState.enemy2, screenState.showDebug);
                    DrawEnemy(&entityState.enemy3, screenState.showDebug);
                    DrawEnemy(&entityState.enemy4, screenState.showDebug);
                    DrawItem(&entityState.keyItem1);
                    DrawItem(&entityState.keyItem2);
                    DrawItem(&entityState.keyItem3);

                    if (entityState.hero.keysCollected >= 3)
                    {
                        DrawItem(&entityState.exit);
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

            case LOSING: // GAME OVER!!
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

            case WINNING: //VOCE VENCEU!!
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
        } 
        EndDrawing(); // Fim do switch de DRAW

        // =========================================================================
        // 2. BLOCO DE UNLOAD/FECHAR: apenas quando o jogo acabar
        // =========================================================================


        if (screenState.currentScreen == LOSING || screenState.currentScreen == WINNING)
        {
            if (IsKeyPressed(KEY_DELETE))
            {
                // Sai do loop principal
                break;
            }
            if (IsKeyPressed(KEY_P))
            {
                // Faz unload dos assets antes de voltar para o Título
                UnloadScene(&screenState.map1);
                unloadPlayer(&entityState.hero);
                // Unload de inimigos, itens, etc. (adicione se necessário)
                screenState.currentScreen = TITLE;
            }
        }
    } // Fim do while (!WindowShouldClose())

    CloseWindow();
    return 0;
}