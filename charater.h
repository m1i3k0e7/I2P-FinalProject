#include "global.h"

void character_init();
void character_process(ALLEGRO_EVENT event);
void character_update();
void character_draw();
void character_destroy();

void monster_init(int s);
void monster_process(ALLEGRO_EVENT event, int s);
void monster_update(int s);
void monster_draw(int s);
void monster_destroy(int s);

void time_init();
void time_process(ALLEGRO_EVENT event);
void time_update(int s);
void time_draw();
void time_destroy();

void blood_init();
void blood_process(ALLEGRO_EVENT event);
void blood_update(int s);
void blood_draw();
void blood_destroy();

void boss_init();
void boss_process(ALLEGRO_EVENT event);
void boss_update();
void boss_draw();
void boss_destroy();

void heal_init();
void heal_draw();
void heal_destroy();

void sword_init();
void sword_draw();
void sword_destroy();
