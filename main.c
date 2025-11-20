#include <raylib.h>
#include <scene.h>
#include "game.h"
#include "player.h"
#include "enemy.h"
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
    int cliques;
    
    //Definição dos objetos do cenário (players, inimigos, itens, armas, etc.)
    Player hero;
    
    Enemy enemy1;
    Enemy enemy2;
    Enemy enemy3;
    Enemy enemy4;
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
                //Não entendi
                currentScreen = GAMEPLAY;
                InitScene(&map1, "assets/Cenario_medieval.png");
                initPlayer(&hero, "assets/player.png");
                
                TraceLog(LOG_INFO, "JOGO: Cena de Jogo iniciada.");

                //Inimigos[1]
                InitEnemy(&enemy1, (Vector2){235.0f, 431.0f}, 100.0f, "assets/ghost.jpg");
                AddWaypoint(&enemy1, (Vector2){507.0f, 569.0f});
                AddWaypoint(&enemy1, (Vector2){520.0f, 673.0f});                
                AddWaypoint(&enemy1, (Vector2){710.0f, 743.0f});
                AddWaypoint(&enemy1, (Vector2){1115.0f, 891.0f});
                AddWaypoint(&enemy1, (Vector2){1463.0f, 656.0f});
                AddWaypoint(&enemy1, (Vector2){1634.0f, 669.0f});

                //Inimigos[2]
                InitEnemy(&enemy2, (Vector2){400, 200}, 80.0f, "assets/ghost.jpg"); 
                AddWaypoint(&enemy2, (Vector2){1372.0f, 320.0f});
                AddWaypoint(&enemy2, (Vector2){1250.0f, 421.0f});
                AddWaypoint(&enemy2, (Vector2){1141.0f, 474.0f});
                AddWaypoint(&enemy2, (Vector2){1301.0f, 571.0f});
                AddWaypoint(&enemy2, (Vector2){1193.0f, 469.0f});
                AddWaypoint(&enemy2, (Vector2){973.0f, 401.0f});
                AddWaypoint(&enemy2, (Vector2){1021.0f, 304.0f});

                //Inimigos[3]
                InitEnemy(&enemy3, (Vector2){632.0f, 276.0f}, 80.0f, "assets/ghost.jpg"); 
                AddWaypoint(&enemy3, (Vector2){918.0f, 313.0f});
                AddWaypoint(&enemy3, (Vector2){781.0f, 442.0f});
                AddWaypoint(&enemy3, (Vector2){630.0f, 535.0f});
                AddWaypoint(&enemy3, (Vector2){583.0f, 611.0f});

                //Inimigos[4]
                InitEnemy(&enemy4, (Vector2){1200.0f, 800.0f}, 80.0f, "assets/ghost.jpg");
                AddWaypoint(&enemy4, (Vector2){633.0f, 589.0f});
                AddWaypoint(&enemy4, (Vector2){664.0f, 658.0f});
                AddWaypoint(&enemy4, (Vector2){789.0f, 652.0f});

                TraceLog(LOG_INFO, "Inimigos inicializados.");
            }
        }
        case GAMEPLAY:
        {
            //Entender como funcionam essas atualizações
            UpdatePlayer(&hero, &map1);
            UpdateEnemy(&enemy1, GetFrameTime());
            UpdateEnemy(&enemy2, GetFrameTime());
            UpdateEnemy(&enemy3, GetFrameTime());
            UpdateEnemy(&enemy4, GetFrameTime());

            // Captura de clique do mouse para mapeamento de pixels!!
            // --- CÁLCULO DAS COORDENADAS DO MOUSE MAPEADAS ---
            

            if (IsKeyPressed(KEY_Q))
            {
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
    CloseWindow();
    return 0;
}
