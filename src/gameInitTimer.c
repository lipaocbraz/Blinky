#include "gameInitTimer.h"
#include <stdlib.h>

timerState newTimerState(void){
    timerState state;

    state.start_time = 0.0;
    state.scoreCalculated = false; // Flag para garantir que o tempo só seja medido uma vez

    return state;
}
