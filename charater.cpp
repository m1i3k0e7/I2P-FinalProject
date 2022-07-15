#include "charater.h"
#include <stdlib.h>
#include <math.h>

enum {STOP = 0, MOVE, ATK};

int monatk;

typedef struct character
{
    int x, y;
    int width, height;
    bool dir;
    int state;
    ALLEGRO_BITMAP *img_move[6];
    ALLEGRO_BITMAP *img_atk[4];
    ALLEGRO_SAMPLE_INSTANCE *atk_Sound;
    int anime;
    int anime_time;
    int strengthen;
}Character;

Character chara;
ALLEGRO_SAMPLE *sample = NULL;

void character_init()
{
    for(int i=1; i<=6; i++){
        char temp[50];
        sprintf(temp, "./image/char_move%d.png", i);
        printf("loading char_move%d\n", i);
        chara.img_move[i-1] = al_load_bitmap(temp);
        printf("load char_move%d successfully\n", i);
    }
    for(int i=1; i<=4; i++){
        char temp[50];
        sprintf(temp, "./image/char_atk%d.png", i);
        printf("loading char_atk%d\n", i);
        chara.img_atk[i-1] = al_load_bitmap(temp);
        printf("load char_atk%d successfully\n", i);
    }

    sample = al_load_sample("./sound/atk_sound.wav");
    chara.atk_Sound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(chara.atk_Sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(chara.atk_Sound, al_get_default_mixer());

    chara.width = al_get_bitmap_width(chara.img_move[0]);
    chara.height = al_get_bitmap_height(chara.img_move[0]);
    chara.x = WIDTH/2;
    chara.y = HEIGHT * 2/3;
    chara.dir = false;
    chara.strengthen = 0;

    chara.state = STOP;
    chara.anime = 0;
    chara.anime_time = 30;
}
void character_process(ALLEGRO_EVENT event)
{
    if(event.type == ALLEGRO_EVENT_TIMER){
        if(event.timer.source == fps){
            chara.anime++;
            chara.anime %= chara.anime_time;
        }
    }
    else if(event.type == ALLEGRO_EVENT_KEY_DOWN){
        key_state[event.keyboard.keycode] = true;
        chara.anime = 0;
    }
    else if(event.type == ALLEGRO_EVENT_KEY_UP){
        key_state[event.keyboard.keycode] = false;
    }
}
void character_update()
{
    if(key_state[ALLEGRO_KEY_W]){
        if(chara.y >= 450)
            chara.y -= 5;
        chara.state = MOVE;
    }
    else if(key_state[ALLEGRO_KEY_A]){
        chara.dir = false;
        chara.x -= 5;
        chara.state = MOVE;
    }
    else if(key_state[ALLEGRO_KEY_S]){
        chara.y += 5;
        chara.state = MOVE;
    }
    else if(key_state[ALLEGRO_KEY_D]){
        chara.dir = true;
        chara.x += 5;
        chara.state = MOVE;
    }
    else if(key_state[ALLEGRO_KEY_SPACE]){
        chara.state = ATK;
    }
    else if(chara.anime == chara.anime_time-1){
        chara.anime = 0;
        chara.state = STOP;
    }
    else if(chara.anime == 0)
    {
        chara.state = STOP;
    }
}
void character_draw()
{
    if(chara.state == STOP){
        if(!chara.dir)
            al_draw_bitmap(chara.img_move[3], chara.x-97, chara.y-64, 0);
        else
            al_draw_bitmap(chara.img_move[0], chara.x-97, chara.y-64, 0);
    }
    else if(chara.state == MOVE){
        if(!chara.dir)
            if(chara.anime < chara.anime_time/2)
                al_draw_bitmap(chara.img_move[4], chara.x-77, chara.y-78, 0);
            else
                al_draw_bitmap(chara.img_move[5], chara.x-88, chara.y-81, 0);
        else
            if(chara.anime < chara.anime_time/2)
                al_draw_bitmap(chara.img_move[1], chara.x-77, chara.y-78, 0);
            else
                al_draw_bitmap(chara.img_move[2], chara.x-88, chara.y-81, 0);
    }
    else if(chara.state == ATK){
        if(!chara.dir)
            if(chara.anime < chara.anime_time/2){
                al_play_sample_instance(chara.atk_Sound);
                al_draw_bitmap(chara.img_atk[2], chara.x-87, chara.y-97, 0);
            }
            else
                al_draw_bitmap(chara.img_atk[3], chara.x-126, chara.y-56, 0);
        else
            if(chara.anime < chara.anime_time/2){
                al_play_sample_instance(chara.atk_Sound);
                al_draw_bitmap(chara.img_atk[0], chara.x-114, chara.y-87, 0);
            }
            else
                al_draw_bitmap(chara.img_atk[1], chara.x-126, chara.y-56, 0);
    }
}
void character_destroy()
{
    for(int i=0; i<6; i++)
        al_destroy_bitmap(chara.img_move[i]);
    for(int i=0; i<4; i++)
        al_destroy_bitmap(chara.img_atk[i]);
    al_destroy_sample_instance(chara.atk_Sound);
}

typedef struct Monster
{
    int x, y;
    int dir;
    int state;
    int exist;
    int time;
    int anime;
    int anime_time;
    int exist_time;
    int monstertime;
    int tp;
}Monster;

Monster mon[20];
Monster mon2[20];
Monster mon3[20];
ALLEGRO_BITMAP *img_mon[4];

void monster_init(int s)
{
    srand(time(NULL));
    if(s == 1)
        for(int i=0; i<10; i++){
            mon[i].x = rand() % 1500;
            mon[i].y = rand() % (800 - 450 + 1) + 450;
            mon[i].exist = 0;
            mon[i].time = 0;
            mon[i].monstertime = rand() % 2000;
            mon[i].exist_time = 700;
            mon[i].tp = i % 2;
            mon[i].anime = 0;
            mon[i].anime_time = 30;
            printf("loading monster\n");
            img_mon[0] = al_load_bitmap("./image/monster1.png");
            img_mon[1] = al_load_bitmap("./image/monster2.png");
            img_mon[2] = al_load_bitmap("./image/monster3.png");
            img_mon[3] = al_load_bitmap("./image/monster4.png");
            printf("load monster successfully\n");
        }
    else if(s == 2)
        for(int i=0; i<15; i++){
            mon2[i].x = rand() % 1500;
            mon2[i].y = rand() % (750 - 450 + 1) + 450;
            mon2[i].exist = 0;
            mon2[i].time = 0;
            mon2[i].monstertime = rand() % 2000;
            mon2[i].exist_time = 700;
            mon2[i].tp = i % 2;
            mon2[i].anime = 0;
            mon2[i].anime_time = 30;
            printf("loading rock\n");
            img_mon[0] = al_load_bitmap("./image/rock1.png");
            img_mon[1] = al_load_bitmap("./image/rock2.png");
            img_mon[2] = al_load_bitmap("./image/rock3.png");
            img_mon[3] = al_load_bitmap("./image/rock4.png");
            printf("load rock successfully\n");
        }
}
void monster_process(ALLEGRO_EVENT event, int s)
{
    if(event.type == ALLEGRO_EVENT_TIMER)
        if(event.timer.source == fps){
            if(s == 1){
                for(int i=0; i<10; i++){
                    mon[i].time++;
                    if(mon[i].exist == 1){
                        mon[i].anime++;
                        mon[i].anime %= mon[i].anime_time;
                    }
                }
            }
            else if(s == 2){
                for(int i=0; i<15; i++){
                    mon2[i].time++;
                    if(mon2[i].exist == 1){
                        mon2[i].anime++;
                        mon2[i].anime %= mon2[i].anime_time;
                    }
                }
            }
        }
}
void monster_update(int s)
{
    if(s == 1){
        for(int i=0; i<10; i++){
            if(mon[i].exist == 0 && mon[i].time == mon[i].monstertime){
                mon[i].exist = 1;
                mon[i].monstertime = 0;
            }
            if(mon[i].time > 3600)
                mon[i].exist = 0;

            int a = 0, b = 0;
            if(mon[i].tp == 0){
                a = 1;
                b = 0;
            }
            else if(mon[i].tp == 1){
                a = -1;
                b = 0;
            }

            if(mon[i].x + a > 1500)
                mon[i].tp = 1;
            else if(mon[i].x + a < 100)
                mon[i].tp = 0;

            mon[i].x += a;
            mon[i].y += b;
        }
    }
    else if(s == 2){
        for(int i=0; i<15; i++){
            if(mon2[i].exist == 0 && mon2[i].time == mon2[i].monstertime){
                mon2[i].exist = 1;
                mon2[i].monstertime = 0;
            }
            if(mon2[i].time > 3600)
                mon2[i].exist = 0;

            int a = 0, b = 0;
            if(mon2[i].tp == 0){
                a = 2;
                b = 0;
            }
            else if(mon2[i].tp == 1){
                a = -2;
                b = 0;
            }

            if(mon2[i].x + a > 1500)
                mon2[i].tp = 1;
            else if(mon2[i].x + a < 100)
                mon2[i].tp = 0;

            mon2[i].x += a;
            mon2[i].y += b;
        }
    }
}
void monster_draw(int s)
{
    if(s == 1){
        for(int i=0; i<10; i++){
            if(mon[i].exist == 1 && mon[i].time < 3600){
                if(!mon[i].tp){
                    if(mon[i].anime < chara.anime_time/2)
                        al_draw_bitmap(img_mon[0], mon[i].x-146, mon[i].y-75, 0);
                    else
                        al_draw_bitmap(img_mon[1], mon[i].x-142, mon[i].y-76, 0);
                }
                else{
                    if(mon[i].anime < chara.anime_time/2)
                        al_draw_bitmap(img_mon[2], mon[i].x-146, mon[i].y-75, 0);
                    else
                        al_draw_bitmap(img_mon[3], mon[i].x-142, mon[i].y-76, 0);
                }
            }
        }
    }
    else if(s == 2){
        for(int i=0; i<15; i++){
            if(mon2[i].exist == 1 && mon2[i].time < 3600){
                if(!mon2[i].tp){
                    if(mon2[i].anime < chara.anime_time/2)
                        al_draw_bitmap(img_mon[0], mon2[i].x-95, mon2[i].y-94, 0);
                    else
                        al_draw_bitmap(img_mon[1], mon2[i].x-122, mon2[i].y-96, 0);
                }
                else{
                    if(mon2[i].anime < chara.anime_time/2)
                        al_draw_bitmap(img_mon[2], mon2[i].x-95, mon2[i].y-94, 0);
                    else
                        al_draw_bitmap(img_mon[3], mon2[i].x-122, mon2[i].y-96, 0);
                }
            }
        }
    }
    else if(s == 3){
        for(int i=0; i<level3_mon_cnt; i++){
            int a = 0, b = 0;
            if(mon3[i].tp == 0){
                a = 2;
                b = 0;
            }
            else if(mon3[i].tp == 1){
                a = -2;
                b = 0;
            }
            else if(mon3[i].tp == 2){
                a = 0;
                b = 2;
            }
            else if(mon3[i].tp == 3){
                a = 0;
                b = -2;
            }

            if(mon3[i].x + a > 1500)
                mon3[i].tp = 1;
            else if(mon3[i].x + a < 100)
                mon3[i].tp = 0;
            else if(mon3[i].y + b > 900)
                mon3[i].tp = 3;
            else if(mon3[i].y + b < 0)
                mon3[i].tp = 2;

            if(mon3[i].exist == 1){
                al_draw_bitmap(img_mon[0], mon3[i].x + a - 45, mon3[i].y + b - 45, 0);
                mon3[i].x += a;
                mon3[i].y += b;
            }
        }
    }
}
void monster_destroy(int s)
{
    if(s == 3)
        al_destroy_bitmap(img_mon[0]);
    else
        for(int i=0; i<4; i++)
            al_destroy_bitmap(img_mon[i]);
}

typedef struct Heal
{
    int x, y;
    int exist;
    ALLEGRO_BITMAP *img;
    ALLEGRO_SAMPLE_INSTANCE *sound;
}Heal;

Heal heal;

void heal_init()
{
    heal.x = heal.y = 0;
    heal.exist = 0;
    heal.img = al_load_bitmap("./image/heal.png");
    sample = al_load_sample("./sound/crystal_sound.wav");
    heal.sound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(heal.sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(heal.sound, al_get_default_mixer());

}

void heal_draw()
{
    if(heal.exist)
        al_draw_bitmap(heal.img, heal.x-35, heal.y-43, 0);
}

void heal_destroy()
{
    al_destroy_bitmap(heal.img);
}

typedef struct Sword
{
    int x, y;
    int exist;
    ALLEGRO_BITMAP *img;
    ALLEGRO_SAMPLE_INSTANCE *sound;
}Sword;

Sword sword;

void sword_init()
{
    sword.x = sword.y = 0;
    sword.exist = 0;
    sword.img = al_load_bitmap("./image/sword.png");
    sample = al_load_sample("./sound/crystal_sound.wav");
    sword.sound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(sword.sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(sword.sound, al_get_default_mixer());
}

void sword_draw()
{
    if(sword.exist)
        al_draw_bitmap(sword.img, sword.x-35, sword.y-33, 0);
}

void sword_destroy()
{
    al_destroy_bitmap(sword.img);
}

typedef struct Boss
{
    int x, y;
    int dir;
    int hp;
    int speed;
    int born[5];
    int exist;
    int tp;
    int anime;
    int anime_time;
    int time;
    int attack;
    int atk_cnt;
    double init_x_cnt;
    double init_y_cnt;
    ALLEGRO_BITMAP *img[10];
    ALLEGRO_SAMPLE_INSTANCE *Sound;
}Boss;

Boss boss;

void boss_init()
{
    char temp[50];
    printf("loading boss\n");
    boss.img[0] = al_load_bitmap("./image/dragon1.png");
    boss.img[1] = al_load_bitmap("./image/dragon2.png");
    boss.img[2] = al_load_bitmap("./image/dragon3.png");
    boss.img[3] = al_load_bitmap("./image/dragon4.png");
    boss.img[4] = al_load_bitmap("./image/dragon5.png");
    boss.img[5] = al_load_bitmap("./image/dragon6.png");
    boss.img[6] = al_load_bitmap("./image/dragon7.png");
    boss.img[7] = al_load_bitmap("./image/dragon8.png");
    boss.img[8] = al_load_bitmap("./image/dragon_init1.png");
    boss.img[9] = al_load_bitmap("./image/dragon_init2.png");
    printf("load boss successfully\n");

    sprintf(temp, "./image/fireball.png");
    img_mon[0] = al_load_bitmap(temp);

    ALLEGRO_SAMPLE *sample = al_load_sample("./sound/boss.wav");
    boss.Sound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(boss.Sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(boss.Sound, al_get_default_mixer());

    //boss.x = 1600 / 2;
    //boss.y = 100;

    boss.x = 100;
    boss.y = 100;
    boss.init_x_cnt = 50;
    boss.init_y_cnt = 50;

    boss.anime_time = 30;
    boss.anime = 0;
    boss.hp = 25;
    boss.speed = 30;
    boss.exist = 0;
    boss.time = 0;
    boss.attack = 0;
    boss.atk_cnt = 0;
    level3_mon_cnt = 0;

    if(boss.x - chara.x >= 0)
        boss.dir = true;
    else
        boss.dir = false;

    for(int i=0; i<5; i++)
        boss.born[i] = 1;

    al_play_sample_instance(boss.Sound);
}

void boss_process(ALLEGRO_EVENT event)
{
    if(event.type == ALLEGRO_EVENT_TIMER)
        if(event.timer.source == fps){
            boss.anime++;
            boss.anime %= boss.anime_time;
            boss.time++;
        }
}
void boss_update()
{
    if(boss.exist == 0 && boss.hp > 0)
        boss.exist = 1;
    if(boss.hp <= 0)
         boss.exist = 0;

    //printf("boss hp: %d\n", boss.hp);
    if(boss.init_y_cnt == 175 && boss.init_x_cnt == 900){
        if(!(boss.hp % 5) && boss.hp < 25)
            if(boss.born[boss.hp/5 - 1]){
                boss.attack = 1;

                al_play_sample_instance(boss.Sound);

                boss.born[boss.hp/5 - 1] = 0;
                for(int i=level3_mon_cnt; i<level3_mon_cnt+3; i++){
                    if(boss.dir){
                        mon3[i].x = boss.x - 40;
                        mon3[i].y = boss.y - 140;
                    }
                    else{
                        mon3[i].x = boss.x + 260;
                        mon3[i].y = boss.y - 140;
                    }
                    mon3[i].exist = 1;
                    mon3[i].exist_time = 700;
                    mon3[i].tp = rand() % 4;
                }
                level3_mon_cnt += 3;
            }

        double x_offset = chara.x - boss.x;
        double y_offset = chara.y - boss.y;
        double distance = sqrt(x_offset * x_offset + y_offset * y_offset);


        if(x_offset > 0)
            boss.dir = false;
        else if(x_offset < 0)
            boss.dir = true;

        if(distance != 0){
            x_offset /= distance;
            y_offset /= distance;
        }

        x_offset *= 2;
        y_offset *= 2;

        boss.x += x_offset;
        boss.y += y_offset;
    }
    else{
        if(boss.init_y_cnt < 100){
            boss.init_x_cnt += 5;
            boss.init_y_cnt += 0.25;
        }
        else{
            boss.init_x_cnt -= 5;
            boss.init_y_cnt += 2.5;

            //printf("%lf %lf\n", boss.init_x_cnt, boss.init_y_cnt);

            if(boss.init_x_cnt == 900 && boss.init_y_cnt == 175){
                boss.x = boss.init_x_cnt;
                boss.y = boss.init_y_cnt;
            }
        }
    }
}
void boss_draw()
{
    if(boss.init_x_cnt == 900 && boss.init_y_cnt == 175){
        if(!boss.attack){
            if(boss.dir)
                if(boss.anime < boss.anime_time/2)
                    al_draw_bitmap(boss.img[2], boss.x-176, boss.y - 150-176, 0);
                else
                    al_draw_bitmap(boss.img[3], boss.x-181, boss.y - 150-126, 0);
            else
                if(boss.anime < boss.anime_time/2)
                    al_draw_bitmap(boss.img[0], boss.x-176, boss.y - 150-176, 0);
                else
                    al_draw_bitmap(boss.img[1], boss.x-181, boss.y - 150-126, 0);
        }
        else{
            if(!boss.dir)
                if(boss.anime < boss.anime_time/2)
                    al_draw_bitmap(boss.img[4], boss.x-178, boss.y - 150-112, 0);
                else
                    al_draw_bitmap(boss.img[6], boss.x-173, boss.y - 150-107, 0);
            else
                if(boss.anime < boss.anime_time/2)
                    al_draw_bitmap(boss.img[5], boss.x-178, boss.y - 150-112, 0);
                else
                    al_draw_bitmap(boss.img[7], boss.x-173, boss.y - 150-107, 0);

            boss.atk_cnt++;
            if(boss.atk_cnt == 60){
                boss.attack = 0;
                boss.atk_cnt = 0;
            }
        }
    }
    else{
        if(boss.init_y_cnt < 100)
            al_draw_bitmap(boss.img[8], boss.init_x_cnt-209, boss.init_y_cnt-121, 0);
        else
            al_draw_bitmap(boss.img[9], boss.init_x_cnt-209, boss.init_y_cnt-121, 0);
    }
}
void boss_destroy()
{
    for(int i=0; i<4; i++)
        al_destroy_bitmap(boss.img[i]);
    al_destroy_sample_instance(boss.Sound);
}


ALLEGRO_FONT *font2 = NULL;
typedef struct timer
{
    int timepass;
    int gametime;
    int tmp;
}timer;

timer t;

void time_init()
{
    font2 = al_load_ttf_font("./font/pirulen.ttf", 80, 0);
    t.timepass = 0;
    t.gametime = 60;
    t.tmp = 60;
}
void time_process(ALLEGRO_EVENT event)
{
    if(event.type == ALLEGRO_EVENT_TIMER)
        if(event.timer.source == fps){
            t.timepass++;
            t.timepass %= t.gametime;
        }
}
void time_update(int s)
{
    if(s == 1){
        if(t.timepass == 59)
            t.tmp--;
        if(t.tmp == 0)
            if(monatk < 10)
                judge_next_window = 251;// 2 to 51(fail1)
            else
                judge_next_window = 27;// 2 to 7
    }
    else if(s == 2){
        if(t.timepass == 59)
            t.tmp--;
        if(t.tmp == 0)
            if(monatk < 15)
                judge_next_window = 452;// 4 to 52(fail2)
            else
                judge_next_window = 49;// 4 to 8(win)
    }
    else if(s == 3){
        if(t.timepass == 59)
            t.tmp--;
        if(t.tmp == 0)
            if(t.tmp == 0){
                if(boss.hp > 0)
                    judge_next_window = 1053;
                else
                    judge_next_window = 108;
            }
    }
}
void time_draw()
{
    if(t.tmp < 10)
        al_draw_textf(font2, al_map_rgb(238 , 75, 43), 1530, 30, ALLEGRO_ALIGN_RIGHT, "00:0%d", t.tmp);
    else if(t.tmp >= 10 && t.tmp < 60)
        al_draw_textf(font2, al_map_rgb(255, 255, 255), 1530, 30, ALLEGRO_ALIGN_RIGHT, "00:%d", t.tmp);
    else
        al_draw_textf(font2, al_map_rgb(255, 255, 255), 1530, 30, ALLEGRO_ALIGN_RIGHT, "01:00");
}
void time_destroy()
{
    al_destroy_font(font2);
}


typedef struct Blood
{
    int atktime;
    int bloodtime;
    int bloodtiming;
    ALLEGRO_SAMPLE_INSTANCE *hurt_sound;
}Blood;

Blood blood;
ALLEGRO_BITMAP *img_blood1 = NULL;
ALLEGRO_BITMAP *img_blood2 = NULL;
ALLEGRO_BITMAP *img_blood3 = NULL;
ALLEGRO_BITMAP *img_blood4 = NULL;
ALLEGRO_BITMAP *img_blood5 = NULL;
ALLEGRO_BITMAP *img_blood6 = NULL;
ALLEGRO_BITMAP *img_blood7 = NULL;
ALLEGRO_BITMAP *img_blood8 = NULL;
ALLEGRO_BITMAP *img_blood9 = NULL;
ALLEGRO_BITMAP *img_blood10 = NULL;
ALLEGRO_SAMPLE *hurt_sample = NULL;
ALLEGRO_FONT *font3 = NULL;

void blood_init()
{
    printf("loading blood\n");
    img_blood1 = al_load_bitmap("./image/1.png");
    img_blood2 = al_load_bitmap("./image/2.png");
    img_blood3 = al_load_bitmap("./image/3.png");
    img_blood4 = al_load_bitmap("./image/4.png");
    img_blood5 = al_load_bitmap("./image/5.png");
    img_blood6 = al_load_bitmap("./image/6.png");
    img_blood7 = al_load_bitmap("./image/7.png");
    img_blood8 = al_load_bitmap("./image/8.png");
    img_blood9 = al_load_bitmap("./image/9.png");
    img_blood10 = al_load_bitmap("./image/10.png");
    printf("load blood successfully\n");

    blood.atktime = 0;
    blood.bloodtime = 0;
    blood.bloodtiming = 700;
    monatk = 0;
    font3 = al_load_ttf_font("./font/pirulen.ttf", 80, 0);

    hurt_sample = al_load_sample("./sound/touch_sound.wav");
    blood.hurt_sound = al_create_sample_instance(hurt_sample);
    al_set_sample_instance_playmode(blood.hurt_sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(blood.hurt_sound, al_get_default_mixer());
}

void blood_process(ALLEGRO_EVENT event)
{
    if(event.type == ALLEGRO_EVENT_TIMER)
        if(event.timer.source == fps)
            blood.bloodtime++;
}

void blood_update(int s)
{
    srand(time(NULL));
    if(s == 1){
        if(blood.bloodtime % 60 == 0){
            if(chara.state == MOVE || chara.state == STOP){
                if((heal.y - chara.y <= 100 && heal.y - chara.y >= -100) && (heal.x - chara.x <= 100 && heal.x - chara.x >= -100) && (heal.exist == 1 && blood.atktime > 0)){
                    al_play_sample_instance(heal.sound);

                    blood.atktime--;
                    heal.exist = 0;
                }
                if((sword.y - chara.y <= 100 && sword.y - chara.y >= -100) && (sword.x - chara.x <= 100 && sword.x - chara.x >= -100) && (sword.exist == 1 && chara.strengthen == 0)){
                    al_play_sample_instance(sword.sound);
                    sword.exist = 0;
                    chara.strengthen = 1;

                    for(int i=1; i<=6; i++){
                        char temp[50];
                        sprintf(temp, "./image/char_im_move%d.png", i);
                        chara.img_move[i-1] = al_load_bitmap(temp);
                    }
                    for(int i=1; i<=4; i++){
                        char temp[50];
                        sprintf(temp, "./image/char_im_atk%d.png", i);
                        chara.img_atk[i-1] = al_load_bitmap(temp);
                    }
                }
            }
            for(int i=0; i<10; i++){
                if(mon[i].exist == 1){
                    if((chara.y - mon[i].y <= 140 && chara.y - mon[i].y >= 0) || (mon[i].y - chara.y <= 140 && mon[i].y - chara.y >= 0) && blood.bloodtime < 3600){
                        if(chara.state == ATK){
                            if((chara.x - mon[i].x < 250 && chara.x - mon[i].x >= 0 && chara.dir == false) || (mon[i].x - chara.x < 250 && mon[i].x - chara.x >= 0 && chara.dir == true)){
                                mon[i].exist = 2;
                                monatk++;

                                int gen_heal = rand() % (2 - 1 + 1) + 1;
                                if(gen_heal == 1 && heal.exist == 0){
                                    heal.x = mon[i].x + 10;
                                    heal.y = mon[i].y + 10;
                                    heal.exist = 1;
                                }

                                if(gen_heal == 2 && chara.strengthen == 0 && !sword.exist){
                                    sword.x = mon[i].x + 10;
                                    sword.y = mon[i].y + 10;
                                    sword.exist = 1;
                                }
                                if(monatk >= 10)
                                    judge_next_window = 27;

                                if(!chara.strengthen)
                                    break;
                            }
                        }
                        else if(chara.state == MOVE || chara.state == STOP){
                            if((chara.x - mon[i].x <= 130 && chara.x - mon[i].x >= -130) && (chara.y - mon[i].y <= 130 && chara.y - mon[i].y >= -130)){
                                al_play_sample_instance(blood.hurt_sound);
                                blood.atktime++;
                                printf("blood++ %d\n", blood.atktime);
                                if(blood.atktime == 9)
                                    judge_next_window = 251;

                                break;
                            }
                        }
                    }
                }
            }
        }
    }
    else if(s == 2){
        if(blood.bloodtime % 60 == 0){
            if(chara.state == MOVE || chara.state == STOP){
                if((heal.y - chara.y <= 100 && heal.y - chara.y >= -100) && (heal.x - chara.x <= 100 && heal.x - chara.x >= -100) && (heal.exist == 1 && blood.atktime > 0)){
                    al_play_sample_instance(heal.sound);

                    blood.atktime--;
                    heal.exist = 0;
                }
                if((sword.y - chara.y <= 100 && sword.y - chara.y >= -100) && (sword.x - chara.x <= 100 && sword.x - chara.x >= -100) && (sword.exist == 1 && chara.strengthen == 0)){
                    al_play_sample_instance(sword.sound);
                    sword.exist = 0;
                    chara.strengthen = 1;

                    for(int i=1; i<=6; i++){
                        char temp[50];
                        sprintf(temp, "./image/char_im_move%d.png", i);
                        chara.img_move[i-1] = al_load_bitmap(temp);
                    }
                    for(int i=1; i<=4; i++){
                        char temp[50];
                        sprintf(temp, "./image/char_im_atk%d.png", i);
                        chara.img_atk[i-1] = al_load_bitmap(temp);
                    }
                }
            }
            for(int i=0; i<15; i++){
                if(mon2[i].exist == 1){
                    if((chara.y - mon2[i].y <= 140 && chara.y - mon2[i].y >= 0) || (mon2[i].y - chara.y <= 140 && mon2[i].y - chara.y >= 0) && blood.bloodtime < 3600){
                        if(chara.state == ATK){
                            if((chara.x - mon2[i].x < 250 && chara.x - mon2[i].x >= 0 && chara.dir == false) || (mon2[i].x - chara.x < 250 && mon2[i].x - chara.x >= 0 && chara.dir == true)){
                                mon2[i].exist = 2;
                                monatk++;

                                int gen_heal = rand() % (10 - 1 + 1) + 1;
                                if(gen_heal == 1 && heal.exist == 0){
                                    heal.x = mon2[i].x;
                                    heal.y = mon2[i].y;
                                    heal.exist = 1;
                                }
                                if(gen_heal == 2 && chara.strengthen == 0 && !sword.exist){
                                    sword.x = mon2[i].x + 10;
                                    sword.y = mon2[i].y + 10;
                                    sword.exist = 1;
                                }

                                if(monatk >= 15)
                                    judge_next_window = 49;
                                if(!chara.strengthen)
                                    break;
                            }
                        }
                        else if(chara.state == MOVE || chara.state == STOP){
                            if((chara.x - mon2[i].x <= 130 && chara.x - mon2[i].x >= -130) && (chara.y - mon2[i].y <= 130 && chara.y - mon2[i].y >= -130)){
                                al_play_sample_instance(blood.hurt_sound);
                                blood.atktime++;
                                if(blood.atktime == 9)
                                    judge_next_window = 452;

                                break;
                            }
                        }
                    }
                }
            }
        }
    }
    else if(s == 3){
        if(blood.bloodtime % 60 == 0){
            if(chara.state == MOVE || chara.state == STOP){
                if((heal.y - chara.y <= 100 && heal.y - chara.y >= -100) && (heal.x - chara.x <= 100 && heal.x - chara.x >= -100) && (heal.exist == 1 && blood.atktime > 0)){
                    al_play_sample_instance(heal.sound);

                    blood.atktime--;
                    heal.exist = 0;
                }
                if((sword.y - chara.y <= 100 && sword.y - chara.y >= -100) && (sword.x - chara.x <= 100 && sword.x - chara.x >= -100) && (sword.exist == 1 && chara.strengthen == 0)){
                    al_play_sample_instance(sword.sound);
                    sword.exist = 0;
                    chara.strengthen = 1;

                    for(int i=1; i<=6; i++){
                        char temp[50];
                        sprintf(temp, "./image/char_im_move%d.png", i);
                        chara.img_move[i-1] = al_load_bitmap(temp);
                    }
                    for(int i=1; i<=4; i++){
                        char temp[50];
                        sprintf(temp, "./image/char_im_atk%d.png", i);
                        chara.img_atk[i-1] = al_load_bitmap(temp);
                    }
                }
            }
            for(int i=0; i<level3_mon_cnt; i++){
                if((chara.y - mon3[i].y < 140 && chara.y - mon3[i].y > 0) || (mon3[i].y - chara.y < 140 && mon3[i].y - chara.y > 0) && blood.bloodtime < 3600){
                    if(chara.state == ATK){
                        if((chara.x - mon3[i].x < 170 && chara.x - mon3[i].x >= 0 && chara.dir == false) || (mon3[i].x - chara.x < 170 && mon3[i].x - chara.x >= 0 && chara.dir == true)){
                            if(mon3[i].exist == 1){
                                mon3[i].exist = 2;
                                monatk++;

                                int gen_heal = rand() % (10 - 1 + 1) + 1;
                                if(gen_heal == 1 && heal.exist == 0){
                                    heal.x = mon3[i].x;
                                    heal.y = mon3[i].y;
                                    heal.exist = 1;
                                }
                                if(gen_heal == 2 && chara.strengthen == 0){
                                    sword.x = mon3[i].x + 10;
                                    sword.y = mon3[i].y + 10;
                                    sword.exist = 1;
                                }
                            }
                            if(boss.hp <= 0)
                                judge_next_window = 108;

                            if(!chara.strengthen)
                                break;
                        }
                    }
                    else if(chara.state == MOVE || chara.state == STOP){
                        if((chara.x - mon3[i].x <= 90 && chara.x - mon3[i].x >= -90) && (chara.y - mon3[i].y <= 90 && chara.y - mon3[i].y >= -90)){
                            if(mon3[i].exist == 1){
                                al_play_sample_instance(blood.hurt_sound);
                                //blood.atktime++;
                                if(blood.atktime == 9)
                                    judge_next_window = 1053;
                            }
                        }
                    }
                }
            }
            if(chara.y - boss.y < 200 && boss.y - chara.y > -200){
                if(chara.state == ATK){
                    if(chara.x - boss.x < 200 && boss.x - chara.x > -200){
                        if(boss.hp)
                            boss.hp -= 5;
                        if(boss.hp <= 0)
                            judge_next_window = 108;
                    }
                }
                else if(chara.state == MOVE || chara.state == STOP){
                    if((chara.x - boss.x <= 120 && chara.x - boss.x >= 0) || (boss.x - chara.x <= 120 && boss.x - chara.x >= 0)){
                        al_play_sample_instance(blood.hurt_sound);
                        //blood.atktime += 2;
                        if(blood.atktime >= 9)
                            judge_next_window = 1053;
                    }
                }
            }
        }
    }
}
void blood_draw()
{
    if(blood.bloodtime < 3600)
        if(blood.atktime == 0)
            al_draw_bitmap(img_blood10, 1200, 120, 0);
        else if(blood.atktime == 1)
            al_draw_bitmap(img_blood9, 1200, 120, 0);
        else if(blood.atktime == 2)
            al_draw_bitmap(img_blood8, 1200, 120, 0);
        else if(blood.atktime == 3)
            al_draw_bitmap(img_blood7, 1200, 120, 0);
        else if(blood.atktime == 4)
            al_draw_bitmap(img_blood6, 1200, 120, 0);
        else if(blood.atktime == 5)
            al_draw_bitmap(img_blood5, 1200, 120, 0);
        else if(blood.atktime == 6)
            al_draw_bitmap(img_blood4, 1200, 120, 0);
        else if(blood.atktime == 7)
            al_draw_bitmap(img_blood3, 1200, 120, 0);
        else if(blood.atktime == 8)
            al_draw_bitmap(img_blood2, 1200, 120, 0);
        else if(blood.atktime == 9)
            al_draw_bitmap(img_blood1, 1200, 120, 0);
    if(blood.bloodtime < 3601)
        al_draw_textf(font3, al_map_rgb(255, 255, 255), 70, 30, ALLEGRO_ALIGN_LEFT, "%d", monatk);
}
void blood_destroy()
{
    al_destroy_bitmap(img_blood1);
    al_destroy_bitmap(img_blood2);
    al_destroy_bitmap(img_blood3);
    al_destroy_bitmap(img_blood4);
    al_destroy_bitmap(img_blood5);
    al_destroy_bitmap(img_blood6);
    al_destroy_bitmap(img_blood7);
    al_destroy_bitmap(img_blood8);
    al_destroy_bitmap(img_blood9);
    al_destroy_bitmap(img_blood10);
    al_destroy_font(font3);
    al_destroy_sample_instance(blood.hurt_sound);
}

