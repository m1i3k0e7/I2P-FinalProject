#include "scene.h"

ALLEGRO_FONT *font = NULL;
ALLEGRO_BITMAP *background = NULL;
ALLEGRO_BITMAP *setting = NULL;
ALLEGRO_BITMAP *img = NULL;
ALLEGRO_BITMAP *img_start = NULL;
ALLEGRO_BITMAP *topic = NULL;
ALLEGRO_BITMAP *failscene1 = NULL;
ALLEGRO_BITMAP *failscene2 = NULL;
ALLEGRO_BITMAP *failscene3 = NULL;
ALLEGRO_BITMAP *ready = NULL;
ALLEGRO_BITMAP *leveltwo = NULL;
ALLEGRO_BITMAP *levelthree = NULL;
ALLEGRO_BITMAP *win = NULL;

ALLEGRO_SAMPLE_INSTANCE *menu_sound;
ALLEGRO_SAMPLE *menu_sample = NULL;

ALLEGRO_SAMPLE_INSTANCE *operation_sound;
ALLEGRO_SAMPLE *operation_sample = NULL;

ALLEGRO_SAMPLE_INSTANCE *fail1_sound;
ALLEGRO_SAMPLE *fail1_sample = NULL;

ALLEGRO_SAMPLE_INSTANCE *fail2_sound;
ALLEGRO_SAMPLE *fail2_sample = NULL;

ALLEGRO_SAMPLE_INSTANCE *fail3_sound;
ALLEGRO_SAMPLE *fail3_sample = NULL;

ALLEGRO_SAMPLE_INSTANCE *gamescene1_sound;
ALLEGRO_SAMPLE *gamescene1_sample = NULL;

ALLEGRO_SAMPLE_INSTANCE *gamescene2_sound;
ALLEGRO_SAMPLE *gamescene2_sample = NULL;

ALLEGRO_SAMPLE_INSTANCE *gamescene3_sound;
ALLEGRO_SAMPLE *gamescene3_sample = NULL;

ALLEGRO_SAMPLE_INSTANCE *ready_sound;
ALLEGRO_SAMPLE *ready_sample = NULL;

ALLEGRO_SAMPLE_INSTANCE *leveltwo_sound;
ALLEGRO_SAMPLE *leveltwo_sample = NULL;

ALLEGRO_SAMPLE_INSTANCE *levelthree_sound;
ALLEGRO_SAMPLE *levelthree_sample = NULL;

ALLEGRO_SAMPLE_INSTANCE *win_sound;
ALLEGRO_SAMPLE *win_sample = NULL;

void menu_init()
{
    font = al_load_ttf_font("./font/pirulen.ttf", 12, 0);

    printf("loading background and buttom\n");
    img = al_load_bitmap("./image/background.png");
    img_start = al_load_bitmap("./image/buttom.png");
    topic = al_load_bitmap("./image/title.png");
    printf("load back buttom and topic successfully\n");

    menu_sample = al_load_sample("./sound/menu_sound.wav");
    menu_sound  = al_create_sample_instance(menu_sample);
    al_set_sample_instance_playmode(menu_sound, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(menu_sound, al_get_default_mixer());
    al_set_sample_instance_gain(menu_sound, 3) ;
}
void menu_process(ALLEGRO_EVENT event)
{
    if( event.type == ALLEGRO_EVENT_KEY_UP ){
        if( event.keyboard.keycode == ALLEGRO_KEY_ENTER )
            judge_next_window = 16;
        else if ( event.keyboard.keycode == ALLEGRO_KEY_O )
            judge_next_window = 13;
        else if ( event.keyboard.keycode == ALLEGRO_KEY_ESCAPE )
            judge_next_window = 999;
    }
}
void menu_draw()
{
    al_clear_to_color(al_map_rgb(100,100,100));
    al_draw_text(font, al_map_rgb(255,255,255), WIDTH/4, HEIGHT*3/4 , ALLEGRO_ALIGN_CENTRE, "Press 'Enter' to start");
    al_draw_rectangle(WIDTH/4, 1000, WIDTH*3/4, 1100, al_map_rgb(255, 255, 255), 2);
    al_draw_bitmap(img, 0, 0, 0);
    al_draw_bitmap(img_start, 500, 650, 0);
    al_draw_bitmap(topic, 218, 200, 0);

    al_play_sample_instance(menu_sound);
}
void menu_destroy()
{
    al_destroy_font(font);
    al_destroy_sample_instance(menu_sound);
}

void ready_init()
{
    printf("loading ready1\n");
    ready = al_load_bitmap("./image/ready1.png");
    printf("load ready1 successfully\n");

    ready_sample = al_load_sample("./sound/ready_sound.wav");
    ready_sound  = al_create_sample_instance(ready_sample);
    al_set_sample_instance_playmode(ready_sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(ready_sound, al_get_default_mixer());
}
void ready_process(ALLEGRO_EVENT event)
{
    if( event.type == ALLEGRO_EVENT_KEY_UP )
        if( event.keyboard.keycode == ALLEGRO_KEY_ENTER ){
            judge_next_window = 62;
        }
}
int do_ready_sound = 0;
void ready_draw()
{
    al_draw_bitmap(ready, 0, 0, 0);

    if(!do_ready_sound){
        al_play_sample_instance(ready_sound);
        do_ready_sound++;
    }
}
void ready_destroy()
{
    al_destroy_bitmap(ready);
    do_ready_sound = 0;
    al_destroy_sample_instance(ready_sound);
}

void game_scene_init()
{
    printf("gamescene init\n");
    character_init();
    heal_init();
    monster_init(1);
    time_init();
    blood_init();
    sword_init();
    printf("loading stage1\n");
    background = al_load_bitmap("./image/stage1.jpg");
    printf("load stage1 successfully\n");
    gamescene1_sample = al_load_sample("./sound/gamescene1_sound.mp3");
    gamescene1_sound  = al_create_sample_instance(gamescene1_sample);
    al_set_sample_instance_playmode(gamescene1_sound, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(gamescene1_sound, al_get_default_mixer());
    al_set_sample_instance_gain(gamescene1_sound, 1) ;
}
void game_scene_draw()
{
    al_draw_bitmap(background, 0, 0, 0);
    time_draw();
    monster_draw(1);
    heal_draw();
    sword_draw();
    blood_draw();
    character_draw();
    //al_flip_display();

    al_play_sample_instance(gamescene1_sound);
}
void game_scene_destroy()
{
    al_destroy_bitmap(background);
    character_destroy();
    time_destroy();
    blood_destroy();
    monster_destroy(1);
    al_destroy_sample_instance(gamescene1_sound);
}

void leveltwo_init()
{
    printf("loading ready2\n");
    leveltwo = al_load_bitmap("./image/ready2.png");
    printf("load ready2 successfully\n");

    leveltwo_sample = al_load_sample("./sound/ready_sound.wav");
    leveltwo_sound  = al_create_sample_instance(leveltwo_sample);
    al_set_sample_instance_playmode(leveltwo_sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(leveltwo_sound, al_get_default_mixer());
}
void leveltwo_process(ALLEGRO_EVENT event)
{
    if( event.type == ALLEGRO_EVENT_KEY_UP )
        if( event.keyboard.keycode == ALLEGRO_KEY_ENTER )
            judge_next_window = 74;
}
int do_leveltwo_sound = 0;
void leveltwo_draw()
{
    al_draw_bitmap(leveltwo, 0, 0, 0);

    if(!do_leveltwo_sound){
        al_play_sample_instance(leveltwo_sound);
        do_leveltwo_sound++;
    }
}
void leveltwo_destroy()
{
    al_destroy_bitmap(leveltwo);
    do_leveltwo_sound = 0;
    al_destroy_sample_instance(leveltwo_sound);
}

void levelthree_init()
{
    printf("loading ready3\n");
    levelthree = al_load_bitmap("./image/ready3.png");
    printf("load ready3 successfully\n");
    levelthree_sample = al_load_sample("./sound/ready_sound.wav");
    levelthree_sound = al_create_sample_instance(levelthree_sample);
    al_set_sample_instance_playmode(levelthree_sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(levelthree_sound, al_get_default_mixer());
}
void levelthree_process(ALLEGRO_EVENT event)
{
    if(event.type == ALLEGRO_EVENT_KEY_UP)
        if( event.keyboard.keycode == ALLEGRO_KEY_ENTER )
            judge_next_window = 910;
}
int do_levelthree_sound = 0;
void levelthree_draw()
{
    al_draw_bitmap(levelthree, 0, 0, 0);

    if(!do_levelthree_sound){
        al_play_sample_instance(levelthree_sound);
        do_levelthree_sound++;
    }
}
void levelthree_destroy()
{
    al_destroy_bitmap(levelthree);
    do_levelthree_sound = 0;
    al_destroy_sample_instance(levelthree_sound);
}

void game_scene_init2()
{
    character_init();
    monster_init(2);
    time_init();
    blood_init();
    heal_init();
    sword_init();
    printf("loading gamescene2\n");
    background = al_load_bitmap("./image/stage2.png");
    printf("load gamescene2 successfully");

    gamescene2_sample = al_load_sample("./sound/gamescene2_sound.mp3");
    gamescene2_sound  = al_create_sample_instance(gamescene2_sample);
    al_set_sample_instance_playmode(gamescene2_sound, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(gamescene2_sound, al_get_default_mixer());
    al_set_sample_instance_gain(gamescene2_sound, 1);
}
void game_scene_draw2()
{
    al_draw_bitmap(background, 0, 0, 0);
    time_draw();
    monster_draw(2);
    blood_draw();
    heal_draw();
    sword_draw();
    character_draw();
    //al_flip_display();

    al_play_sample_instance(gamescene2_sound);
}
void game_scene_destroy2()
{
    al_destroy_bitmap(background);
    character_destroy();
    time_destroy();
    blood_destroy();
    monster_destroy(2);
    al_destroy_sample_instance(gamescene2_sound);
}

void game_scene_init3()
{
    character_init();
    monster_init(3);
    time_init();
    boss_init();
    blood_init();
    heal_init();
    sword_init();
    printf("loading gamescene3\n");
    background = al_load_bitmap("./image/stage3.png");
    printf("load gamescene3 successfully\n");

    gamescene3_sample = al_load_sample("./sound/gamescene3_sound .wav");
    gamescene3_sound  = al_create_sample_instance(gamescene3_sample);
    al_set_sample_instance_playmode(gamescene3_sound, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(gamescene3_sound, al_get_default_mixer());
    al_set_sample_instance_gain(gamescene3_sound, 1) ;
}
void game_scene_draw3()
{
    al_draw_bitmap(background, 0, 0, 0);
    time_draw();
    monster_draw(3);
    blood_draw();
    boss_draw();
    heal_draw();
    sword_draw();
    character_draw();

    al_play_sample_instance(gamescene3_sound);
    //al_flip_display();
}
void game_scene_destroy3()
{
    al_destroy_bitmap(background);
    character_destroy();
    time_destroy();
    blood_destroy();
    monster_destroy(3);
    printf("g5\n");
    boss_destroy();
    printf("g6\n");

    al_destroy_sample_instance(gamescene3_sound);
    printf("g7\n");
}

void win_init()
{
    printf("loading win\n");
    win = al_load_bitmap("./image/win.png");
    printf("load win successfully");

    win_sample = al_load_sample("./sound/win_sound.wav");
    win_sound  = al_create_sample_instance(win_sample);
    al_set_sample_instance_playmode(win_sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(win_sound, al_get_default_mixer());
}
void win_process(ALLEGRO_EVENT event)
{
    if( event.type == ALLEGRO_EVENT_KEY_UP )
        if( event.keyboard.keycode == ALLEGRO_KEY_ENTER )
            judge_next_window = 81;
}
int do_win_sound = 0;
void win_draw()
{
    al_draw_bitmap(win, 0, 0, 0);

    if(!do_win_sound){
        al_play_sample_instance(win_sound);
        do_win_sound++;
    }
}
void win_destroy()
{
    al_destroy_bitmap(win);
    do_win_sound = 0;
    al_destroy_sample_instance(win_sound);
}

void operation_init()
{
    printf("loading operation\n");
    setting = al_load_bitmap("./image/operation_background.png");
    printf("load operation successfully\n");
    operation_sample = al_load_sample("./sound/menu_sound.wav");
    operation_sound  = al_create_sample_instance(operation_sample);
    al_set_sample_instance_playmode(operation_sound, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(operation_sound, al_get_default_mixer());
    al_set_sample_instance_gain(operation_sound, 3) ;
}
void operation_process(ALLEGRO_EVENT event)
{
    if( event.type == ALLEGRO_EVENT_KEY_UP )
        if( event.keyboard.keycode == ALLEGRO_KEY_TAB )
            judge_next_window = 31;
}
void operation_draw()
{
    al_draw_bitmap(setting, 0, 0, 0);
    al_play_sample_instance(operation_sound);
}
void operation_destroy()
{
    al_destroy_bitmap(setting);
    al_destroy_sample_instance(operation_sound);
}

void fail_scene1_init()
{
    printf("loading failscene1\n");
    failscene1 = al_load_bitmap("./image/failed_scene1.png");
    printf("load failscene1 successfully\n");

    fail1_sample = al_load_sample("./sound/fail_sound.wav");
    fail1_sound  = al_create_sample_instance(fail1_sample);
    al_set_sample_instance_playmode(fail1_sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(fail1_sound, al_get_default_mixer());
}
void fail_scene1_process(ALLEGRO_EVENT event)
{
    if( event.type == ALLEGRO_EVENT_KEY_UP )
        if( event.keyboard.keycode == ALLEGRO_KEY_ENTER )
            judge_next_window = 511;
}
int do_fail1_sound = 0;
void fail_scene1_draw()
{
    al_draw_bitmap(failscene1, 0, 0, 0);

    if(!do_fail1_sound){
        al_play_sample_instance(fail1_sound);
        do_fail1_sound++;
    }
}
void fail_scene1_destroy()
{
    al_destroy_bitmap(failscene1);
    do_fail1_sound = 0;
    al_destroy_sample_instance(fail1_sound);
}

void fail_scene2_init()
{
    printf("loading failscene2\n");
    failscene2 = al_load_bitmap("./image/failed_scene2.png");
    printf("load failscene2 successfully\n");

    fail2_sample = al_load_sample("./sound/fail_sound.wav");
    fail2_sound  = al_create_sample_instance(fail2_sample);
    al_set_sample_instance_playmode(fail2_sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(fail2_sound, al_get_default_mixer());
    al_set_sample_instance_gain(fail2_sound, 2);
}
void fail_scene2_process(ALLEGRO_EVENT event)
{
    if(event.type == ALLEGRO_EVENT_KEY_UP)
        if(event.keyboard.keycode == ALLEGRO_KEY_ENTER)
            judge_next_window = 521;
}
int do_fail2_sound = 0;
void fail_scene2_draw()
{
    al_draw_bitmap(failscene2, 0, 0, 0);
    if(!do_fail2_sound){
        al_play_sample_instance(fail2_sound);
        do_fail2_sound++;
    }
}
void fail_scene2_destroy()
{
    al_destroy_bitmap(failscene2);
    do_fail2_sound = 0;
    al_destroy_sample_instance(fail2_sound);
}

void fail_scene3_init()
{
    printf("loading failscene3\n");
    failscene3 = al_load_bitmap("./image/failed_scene3.png");
    printf("load failscene3 successfully\n");

    fail3_sample = al_load_sample("./sound/fail_sound.wav");
    fail3_sound = al_create_sample_instance(fail3_sample);
    al_set_sample_instance_playmode(fail3_sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(fail3_sound, al_get_default_mixer());
    al_set_sample_instance_gain(fail3_sound, 2) ;
}
void fail_scene3_process(ALLEGRO_EVENT event)
{
    if( event.type == ALLEGRO_EVENT_KEY_UP )
        if( event.keyboard.keycode == ALLEGRO_KEY_ENTER )
            judge_next_window = 531;
}
int do_fail3_sound = 0;
void fail_scene3_draw()
{
    al_draw_bitmap(failscene3, 0, 0, 0);
    if(!do_fail3_sound){
        al_play_sample_instance(fail3_sound);
        do_fail3_sound = 1;
    }
}
void fail_scene3_destroy()
{
    al_destroy_bitmap(failscene3);
    do_fail3_sound = 0;
    al_destroy_sample_instance(fail3_sound);
}
