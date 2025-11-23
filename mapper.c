#include <raylib.h>
#include <scene.h>
#include "game.h"
#include "player.h"
#include "enemy.h"
#include <math.h> // Para fminf

// ------------------------------------------------------------------------------------
// ------------------------MAPEADOR DE PIXELS EM TELA CHEIA---------------------------
// ------------------------------------------------------------------------------------


// --- CONFIGURAÇÃO DA IMAGEM ---
#define BACKGROUND_IMAGE_PATH "assets/Cenario_medieval.png"

// --- Configurações Iniciais ---
// Usamos a resolução do monitor (como você fez na sua main original)
const int MONITOR_ID = 0;
int cliques = 1;

int main(void)
{
    // 1. Inicialização da Janela e Tela Cheia
    int screenWidth = GetMonitorWidth(MONITOR_ID);
    int screenHeight = GetMonitorHeight(MONITOR_ID);

    InitWindow(screenWidth, screenHeight, "Mapeador de Waypoints Autônomo - Raylib");
    //ToggleFullscreen(); 
    
    SetTargetFPS(60); 

    // 2. Carregar a Textura
    Texture2D mapTexture = LoadTexture(BACKGROUND_IMAGE_PATH);
    
    if (mapTexture.id == 0)
    {
        TraceLog(LOG_ERROR, "ERRO: Não foi possível carregar o mapa em %s", BACKGROUND_IMAGE_PATH);
        // Se falhar, use um tamanho padrão para evitar crash
        mapTexture.width = 100;
        mapTexture.height = 100;
    }

    // 3. Loop Principal
    while (!WindowShouldClose())
    {
        // --- VARIÁVEIS DE CÁLCULO DE ESCALA (replicando a lógica do DrawScene) ---
        
        float currentScreenWidth = (float)GetScreenWidth();
        float currentScreenHeight = (float)GetScreenHeight();

        float mapWidth = (float)mapTexture.width;
        float mapHeight = (float)mapTexture.height;

        // Calcula o fator de escala (Garante que o mapa inteiro caiba na tela)
        float scaleX = currentScreenWidth / mapWidth;
        float scaleY = currentScreenHeight / mapHeight;
        float scale = fminf(scaleX, scaleY);
        
        float scaledWidth = mapWidth * scale;
        float scaledHeight = mapHeight * scale;

        // Calcula o offset para centralizar o mapa
        float offsetX = (currentScreenWidth - scaledWidth) * 0.5f;
        float offsetY = (currentScreenHeight - scaledHeight) * 0.5f;

        // --- CÁLCULO DAS COORDENADAS DO MOUSE MAPEADAS ---
        Vector2 screenMouse = GetMousePosition();
        
        // 1. Remove o OFFSET (tira a tarja)
        Vector2 mapRelative = {
            screenMouse.x - offsetX,
            screenMouse.y - offsetY
        };
        
        // 2. Reverte a ESCALA
        Vector2 mapCoords = {
            mapRelative.x / scale,
            mapRelative.y / scale
        };

        // -----------------------------------------------------------------------
        // DESENHO
        // -----------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(BLACK); // Fundo preto para as tarjas

        // Desenha o mapa (com escala e centralização)
        DrawTexturePro(
            mapTexture, 
            (Rectangle){ 0.0f, 0.0f, mapWidth, mapHeight }, // Source: Imagem inteira
            (Rectangle){ offsetX, offsetY, scaledWidth, scaledHeight }, // Dest: Na tela
            (Vector2){ 0.0f, 0.0f },
            0.0f,
            WHITE
        );

        // --- Desenho das Coordenadas Mapeadas ---
        
        // Verifica se o mouse está DENTRO da área do mapa escalado (ignora a tarja)
        bool isInsideMap = (screenMouse.x >= offsetX && screenMouse.x < (offsetX + scaledWidth) &&
                            screenMouse.y >= offsetY && screenMouse.y < (offsetY + scaledHeight));
        
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && isInsideMap)
        {
            TraceLog(LOG_INFO, "%i. Coordenadas do Mapa: X: %.0f, Y: %.0f",cliques, mapCoords.x, mapCoords.y);
            cliques++;
        }

        const char* coordText = TextFormat(
            "MAPA COORDENADA: X: %.0f, Y: %.0f (Escala: %.2f)", 
            mapCoords.x, 
            mapCoords.y,
            scale
        );
        
        Color textColor = isInsideMap ? YELLOW : RED;
        
        DrawText(coordText, 10, 10, 20, textColor);
        
        // Debug: Ponto no mouse (na tela)
        DrawCircleV(screenMouse, 4, WHITE);
        
        EndDrawing();
    }

    // Descarregamento
    UnloadTexture(mapTexture); 
    CloseWindow();        

    return 0;
}