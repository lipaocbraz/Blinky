# 👻 Blinky: O Jogo de Fuga no Labirinto

Este é um projeto de jogo 2D simples desenvolvido em **C** utilizando a biblioteca **Raylib**. O objetivo é um jogo de fuga com elementos de labirinto, coleta de chaves e inimigos (fantasmas) patrulhando.

-----

## 🎯 Apresentação do Jogo

**Blinky** é um jogo de visão superior (*top-down*) em que o jogador (o herói) deve navegar por um labirinto, **coletar três chaves** e alcançar a porta de saída. O jogador deve completar a tarefa antes que seja pego por um dos fantasmas inimigos ou antes que o tempo se esgote.

### 🕹️ Funcionalidades Principais

  * **Sistema de Estados:** Gerencia as transições entre TÍTULO, MENU (`HOME`), JOGABILIDADE (`GAMEPLAY`), DERROTA (`LOSING`) e VITÓRIA (`WINNING`).
  * **Colisão por Pixels:** Utiliza uma imagem de mapa de colisão (preto e branco) para garantir precisão no movimento do jogador.
  * **Patrulha de Inimigos:** Inimigos (fantasmas) seguem rotas predefinidas de *waypoints*.
  * **Coleta de Itens:** O jogador deve coletar chaves. A porta de saída é liberada apenas após a coleta de todas as chaves.
  * **Controle de Tempo (Score):** O tempo de jogo é rastreado e o recorde (*Top Score*) é salvo em arquivo.
  * **Resolução Dinâmica:** O jogo se adapta à resolução do monitor do usuário (modo janela maximizada ou tela cheia).

### 🧭 Controles

| Ação | Tecla |
| :--- | :--- |
| **Movimento** | `W`, `A`, `S`, `D` ou Setas |
| **Voltar/Sair** | `DELETE` ou `P` (nas telas finais) |
| **Debug** | `F1` (Alterna a visualização de hitboxes e waypoints) |

-----

## 🛠️ Instruções de Compilação e Uso

Este projeto requer a biblioteca **Raylib** instalada no seu sistema para compilar e linkar corretamente.

### ⚙️ Pré-requisitos

  * **Compilador C:** GCC (GNU Compiler Collection) ou equivalente.
  * **Raylib:** Biblioteca gráfica [Raylib](https://www.raylib.com/).

### 💻 Compilação

Para compilar o projeto em ambientes baseados em Unix (Linux/macOS, ou WSL) ou Windows (com MinGW/GCC), execute o seguinte comando no diretório raiz do projeto:

```bash
# O comando a seguir inclui as flags comuns para C99 e linkagem com Raylib
# ATENÇÃO: Os caminhos de -I (include) e -L (library) podem precisar de ajuste
# conforme a sua instalação específica da Raylib.
gcc main.c src/*.c -I include -I /opt/homebrew/include -o blinky.exe -L /opt/homebrew/lib -lraylib -std=c99
```

> **Nota:** Se você estiver no Windows usando Raylib, as flags de linkagem podem ser mais complexas, como `-lraylib -lopengl32 -lgdi32 -lwinmm`. Verifique a documentação da sua instalação Raylib.

### ▶️ Execução

Após a compilação, execute o binário gerado:

```bash
./blinky.exe
```

-----

## 🧑‍💻 Detalhes de Implementação

A arquitetura do jogo é baseada em módulos (arquivos `.c` e `.h`) para separar as responsabilidades das entidades e funcionalidades.

### 📂 Estrutura de Arquivos

| Arquivo/Módulo | Responsabilidade |
| :--- | :--- |
| `main.c` | **Loop Principal** do jogo e controle da Máquina de Estados (`GameScreen`). |
| `scene.c`/`scene.h` | Gerenciamento do mapa, escalabilidade e, principalmente, a **Lógica de Colisão por Pixels**. |
| `player.c`/`player.h` | Controle de movimento do herói, atualização de posição e detecção de colisão com o mapa. |
| `enemy.c`/`enemy.h` | Lógica de movimentação dos fantasmas, Patrulha por *Waypoints* e colisão com o jogador. |
| `item.c`/`item.h` | Gerenciamento de chaves e da porta de saída, incluindo a lógica de coleta. |
| `score.c`/`score.h` | Persistência e ordenação do **Top Score** em arquivo. |
| `gameInit*.c`/`gameInit*.h` | Funções de inicialização de variáveis globais, tela e entidades. |

### 🧠 Destaques do Código

#### 1\. Colisão de Alta Precisão (`scene.c`)

O sistema de colisão traduz as coordenadas de tela do jogador para as coordenadas de um mapa de colisão interno (imagem P\&B). A colisão ocorre se a cor do pixel for preta, garantindo que o jogador só possa andar em áreas brancas.

$$
\text{mapPos}_x = \frac{\text{screenPos}_x - \text{offsetMap}_x}{\text{mapScale}}
$$

```c
// scene.c: Verificando se o pixel é preto (colisão)
Color pixel = scene->collision_pixels[pixelEntityPosY * scene->collision_image.width + pixelEntityPosX];

// Se for preto (RGB(0,0,0)), é colisão.
if (pixel.r == 0 && pixel.g == 0 && pixel.b == 0)
    return true; 
```

#### 2\. Patrulha Orientada por Waypoints (`enemy.c`)

Inimigos seguem uma lista predefinida de `Vector2` (waypoints). A função `UpdateEnemy` usa o `Raymath` (`Vector2Normalize` e `Vector2Distance`) para mover o inimigo em direção ao próximo ponto da rota.

```c
// enemy.c: Movimento para o Waypoint
Vector2 target = enemy->waypoints[enemy->currentWaypoint];
Vector2 direction = Vector2Normalize(Vector2Subtract(target, enemy->position));

enemy->position.x += direction.x * enemy->speed * GetFrameTime();
enemy->position.y += direction.y * enemy->speed * GetFrameTime();
```

#### 3\. Escalabilidade e Adaptação à Tela (`gameInitEntities.c`, `scene.c`)

Para suportar diferentes resoluções de monitor, todas as posições estáticas de entidades (início do jogador, waypoints, itens) são definidas para uma resolução base (e.g., 1920x1080) e ajustadas dinamicamente usando a função `AdjustPosition` e `CalculateMap`.

```c
// gameInitEntities.c: Ajusta a posição absoluta baseada na escala atual da tela
Vector2 AdjustPosition(float x, float y) {
    float scaleX = GetScreenWidth() / 1920.0f;
    float scaleY = GetScreenHeight() / 1080.0f;
    
    return (Vector2){x * scaleX, y * scaleY};
}
```
