#ifndef SCORE_H
#define SCORE_H

#include "raylib.h"

// Define correto do nome do arquivo de score
#define SCORE_FILE "top_score.txt"

// O score é o tempo, deve ser do tipo double
double LoadTopScore(void);
void saveTopScore(double newscore);

#endif