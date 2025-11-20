#include <raylib.h>
#include <scene.h>
#include "game.h"
#include "player.h"
#include "enemy.h"

// Sempre que precisar compilar para gerar um novo executável com as alterações, o comando é:
// gcc main.c src/*.c -I include -o blinky.exe -lraylib -lopengl32 -lgdi32 -lwinmm
 

int main(void)
{

    // Configurações da Janela

    int WINDOW_WIDTH = GetMonitorWidth(0);
    int WINDOW_HEIGHT = GetMonitorHeight(0);

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Blinky");
    GameScreen currentScreen = TITLE;
    SetTargetFPS(60);
    Scene map1;
    
    //Definição dos objetos do cenário (players, inimigos, itens, armas, etc.)
    Player hero;
    
    Enemy enemy1;
    Enemy enemy2;
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
                initPlayer(&hero, "assets/player.png");
                
                TraceLog(LOG_INFO, "JOGO: Cena de Jogo iniciada.");

                //Inimigos[1]
                InitEnemy(&enemy1, (Vector2){235.0f, 431.0f}, 100.0f, "assets/ghost.jpg");
                AddWaypoint(&enemy1, (Vector2){235.0f, 431.0f});
                AddWaypoint(&enemy1, (Vector2){506.0f, 579.0f});
                AddWaypoint(&enemy1, (Vector2){519.0f, 646.0f});
                AddWaypoint(&enemy1, (Vector2){990.0f, 826.0f});
                AddWaypoint(&enemy1, (Vector2){1241.0f, 636.0f});
                AddWaypoint(&enemy1, (Vector2){1376.0f, 642.0f});

                //Inimigos[2]
                InitEnemy(&enemy2, (Vector2){400, 200}, 80.0f, "assets/ghost.jpg");
                AddWaypoint(&enemy2, (Vector2){600, 200});
                AddWaypoint(&enemy2, (Vector2){600, 400});
                AddWaypoint(&enemy2, (Vector2){400, 400});
                
                TraceLog(LOG_INFO, "Inimigos inicializados.");
            }
        }
        case GAMEPLAY:
        {
            UpdatePlayer(&hero, &map1);
            UpdateEnemy(&enemy1, GetFrameTime());
            UpdateEnemy(&enemy2, GetFrameTime());
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

            case GAMEPLAY:
            {
                DrawScene(&map1);
                drawPlayer(&hero);
                DrawEnemy(&enemy1, showDebug);
                DrawEnemy(&enemy2, showDebug);
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


//------------------------------------------------------------------------------------
// ------------------------MAPEADOR DE PIXELS EM TELA CHEIA---------------------------
//------------------------------------------------------------------------------------

// #include "raylib.h"
// #include <math.h> // Para fminf

// // --- CONFIGURAÇÃO DA IMAGEM ---
// #define BACKGROUND_IMAGE_PATH "assets/Cenario_medieval.png"

// // --- Configurações Iniciais ---
// // Usamos a resolução do monitor (como você fez na sua main original)
// const int MONITOR_ID = 0;

// int main(void)
// {
//     // 1. Inicialização da Janela e Tela Cheia
//     int screenWidth = GetMonitorWidth(MONITOR_ID);
//     int screenHeight = GetMonitorHeight(MONITOR_ID);

//     InitWindow(screenWidth, screenHeight, "Mapeador de Waypoints Autônomo - Raylib");
//     //ToggleFullscreen(); 
    
//     SetTargetFPS(60); 

//     // 2. Carregar a Textura
//     Texture2D mapTexture = LoadTexture(BACKGROUND_IMAGE_PATH);
    
//     if (mapTexture.id == 0)
//     {
//         TraceLog(LOG_ERROR, "ERRO: Não foi possível carregar o mapa em %s", BACKGROUND_IMAGE_PATH);
//         // Se falhar, use um tamanho padrão para evitar crash
//         mapTexture.width = 100;
//         mapTexture.height = 100;
//     }

//     // 3. Loop Principal
//     while (!WindowShouldClose())
//     {
//         // --- VARIÁVEIS DE CÁLCULO DE ESCALA (replicando a lógica do DrawScene) ---
        
//         float currentScreenWidth = (float)GetScreenWidth();
//         float currentScreenHeight = (float)GetScreenHeight();

//         float mapWidth = (float)mapTexture.width;
//         float mapHeight = (float)mapTexture.height;

//         // Calcula o fator de escala (Garante que o mapa inteiro caiba na tela)
//         float scaleX = currentScreenWidth / mapWidth;
//         float scaleY = currentScreenHeight / mapHeight;
//         float scale = fminf(scaleX, scaleY);
        
//         float scaledWidth = mapWidth * scale;
//         float scaledHeight = mapHeight * scale;

//         // Calcula o offset para centralizar o mapa
//         float offsetX = (currentScreenWidth - scaledWidth) * 0.5f;
//         float offsetY = (currentScreenHeight - scaledHeight) * 0.5f;

//         // --- CÁLCULO DAS COORDENADAS DO MOUSE MAPEADAS ---
//         Vector2 screenMouse = GetMousePosition();
        
//         // 1. Remove o OFFSET (tira a tarja)
//         Vector2 mapRelative = {
//             screenMouse.x - offsetX,
//             screenMouse.y - offsetY
//         };
        
//         // 2. Reverte a ESCALA
//         Vector2 mapCoords = {
//             mapRelative.x / scale,
//             mapRelative.y / scale
//         };

//         // -----------------------------------------------------------------------
//         // DESENHO
//         // -----------------------------------------------------------------------
//         BeginDrawing();

//         ClearBackground(BLACK); // Fundo preto para as tarjas

//         // Desenha o mapa (com escala e centralização)
//         DrawTexturePro(
//             mapTexture, 
//             (Rectangle){ 0.0f, 0.0f, mapWidth, mapHeight }, // Source: Imagem inteira
//             (Rectangle){ offsetX, offsetY, scaledWidth, scaledHeight }, // Dest: Na tela
//             (Vector2){ 0.0f, 0.0f },
//             0.0f,
//             WHITE
//         );

//         // --- Desenho das Coordenadas Mapeadas ---
        
//         // Verifica se o mouse está DENTRO da área do mapa escalado (ignora a tarja)
//         bool isInsideMap = (screenMouse.x >= offsetX && screenMouse.x < (offsetX + scaledWidth) &&
//                             screenMouse.y >= offsetY && screenMouse.y < (offsetY + scaledHeight));

//         const char* coordText = TextFormat(
//             "MAPA COORDENADA: X: %.0f, Y: %.0f (Escala: %.2f)", 
//             mapCoords.x, 
//             mapCoords.y,
//             scale
//         );
        
//         Color textColor = isInsideMap ? YELLOW : RED;
        
//         DrawText(coordText, 10, 10, 20, textColor);
        
//         // Debug: Ponto no mouse (na tela)
//         DrawCircleV(screenMouse, 4, WHITE);
        
//         EndDrawing();
//     }

//     // Descarregamento
//     UnloadTexture(mapTexture); 
//     CloseWindow();        

//     return 0;
// }