#include "global.h"

const float FPS = 60.0;
const int WIDTH = 1600;
const int HEIGHT = 1000;
int level3_mon_cnt = 0;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_TIMER *fps = NULL;
bool key_state[ALLEGRO_KEY_MAX] = {false};
int judge_next_window = 0;
