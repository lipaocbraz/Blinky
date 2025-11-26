#ifndef SCORE_H
#define SCORE_H

#include "raylib.h"

// Define correto do nome do arquivo de score
#define SCORE_FILE "top_score.txt"
#define MAX_SCORES 10

// O score é o tempo, deve ser do tipo double
void LoadScoreList(double scores[], int *count);
void saveNewScore(double newscore);

#endif