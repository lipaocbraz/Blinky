#include <raylib.h>
#include <stdio.h>
#include <stdlib.h> // Para qsort
#include <float.h>
#include "score.h"

// Comparador para qsort:
// Ordena em ordem DECRESCENTE (do maior tempo para o menor).
int compareScores(const void *a, const void *b)
{
    double scoreA = *(const double *)a;
    double scoreB = *(const double *)b;

    if (scoreA < scoreB)
        return 1; // B vem antes de A
    if (scoreA > scoreB)
        return -1; // A vem antes de B
    return 0;      // A e B são iguais
}

// Carrega os scores existentes do arquivo
void LoadScoreList(double scores[], int *count)
{
    FILE *file = fopen(SCORE_FILE, "r");
    *count = 0;

    if (file != NULL)
    {
        while (*count < MAX_SCORES && fscanf(file, "%lf", &scores[*count]) == 1)
        {
            (*count)++;
        }
        fclose(file);
    }
}

// Salva a lista de scores de volta no arquivo
void saveScoreList(double scores[], int count)
{
    FILE *file = fopen(SCORE_FILE, "w");

    if (file != NULL)
    {
        for (int i = 0; i < count; i++)
        {
            fprintf(file, "============== %.3f ==============\n", scores[i]);
        }
        fclose(file);
    }
    else
    {
        TraceLog(LOG_ERROR, "SCORE: Falha ao abrir o arquivo para escrita.");
    }
}

// Função principal para salvar e ordenar o novo score
void saveNewScore(double new_score)
{
    double scores[MAX_SCORES + 1]; // +1 para acomodar o novo score temporariamente
    int count;

    // 1. Carrega os scores existentes
    LoadScoreList(scores, &count);

    // 2. Adiciona o novo score
    if (count < MAX_SCORES)
    {
        scores[count] = new_score;
        count++;
    }
    else
    {
        // Se a lista está cheia (MAX_SCORES), verifica se o novo score é maior que o último.
        // Temporariamente adiciona o novo score ao final da lista de scores
        scores[MAX_SCORES] = new_score;
        count = MAX_SCORES + 1;
    }

    // 3. Ordena toda a lista (incluindo o novo score, se couber)
    qsort(scores, count, sizeof(double), compareScores);

    // 4. Limita a lista ao TOP MAX_SCORES (se a lista excedeu o limite)
    if (count > MAX_SCORES)
    {
        count = MAX_SCORES;
    }

    // 5. Salva a lista ordenada
    saveScoreList(scores, count);
    TraceLog(LOG_INFO, "SCORE: Novo tempo (%.3f) adicionado e lista reordenada (MAIOR para MENOR).", new_score);
}