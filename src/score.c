#include <raylib.h>
#include <stdio.h>
#include <float.h> // ADICIONADO: Necessário para DBL_MAX
#include "score.h"

// Função para carregar o menor tempo (Top Score)
double LoadTopScore(void)
{
    FILE *file = fopen(SCORE_FILE, "r"); // CORRIGIDO: Agora SCORE_FILE funciona
    double top_score = DBL_MAX;

    if (file != NULL)
    {
        if (fscanf(file, "%lf", &top_score) != 1)
        {
            top_score = DBL_MAX;
        }
        fclose(file);
    }

    return top_score;
}

// Função para salvar o novo menor tempo (se for melhor que o atual)
void saveTopScore(double new_score)
{
    double current_top_score = LoadTopScore();

    if (new_score < current_top_score)
    {
        FILE *file = fopen(SCORE_FILE, "w");
        if (file != NULL)
        {
            fprintf(file, "%.3f", new_score);
            fclose(file);
            TraceLog(LOG_INFO, "SCORE: Novo Recorde Salvo: %.3f segundos.", new_score);
        }
        else
        {
            TraceLog(LOG_ERROR, "SCORE: Falha ao abrir o arquivo de score para escrita.");
        }
    }
    else
    {
        TraceLog(LOG_INFO, "SCORE: Tempo atual (%.3f) nao superou o recorde (%.3f).", new_score, current_top_score);
    }
}