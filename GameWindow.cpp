#include "GameWindow.h"

bool draw = false;
int window = 1;
const char *title = "Final Project 108034022 & 108034035";

ALLEGRO_DISPLAY* display = NULL;
ALLEGRO_SAMPLE *song = NULL;
ALLEGRO_SAMPLE_INSTANCE *sample_instance;

static ALLEGRO_DISPLAY *screen;
static char const *filename;
ALLEGRO_EVENT_QUEUE *queue;
ALLEGRO_EVENT event;
ALLEGRO_TIMER *timer;
ALLEGRO_VIDEO *video;

void video_display(ALLEGRO_VIDEO *video)
{
    ALLEGRO_BITMAP *frame = al_get_video_frame(video);
    if(!frame)
        return;

    al_draw_scaled_bitmap(frame,
                          0, 0,
                          al_get_bitmap_width(frame),
                          al_get_bitmap_height(frame),
                          0, 0,
                          al_get_display_width(screen),
                          al_get_display_height(screen),
                          0
                          );
    al_flip_display();
}
void init_video()
{
    al_init();
    al_init_video_addon();
    al_install_audio();
    timer = al_create_timer(1.0 / 500);
    screen = al_create_display(1600, 1000);

    al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);
    filename = "start.ogv";
    printf("reading video...\n");
    video = al_open_video(filename);

    if(video)
        printf("read video successfully");
    else
        printf("fail to read video");

    queue = al_create_event_queue();
    ALLEGRO_EVENT_SOURCE *temp = al_get_video_event_source(video);
    al_register_event_source(queue, al_get_video_event_source(video));
    al_register_event_source(queue, al_get_display_event_source(screen));
    al_register_event_source(queue, al_get_timer_event_source(timer));
}
void video_begin()
{
    al_reserve_samples(1);
    al_start_video(video, al_get_default_mixer());
    al_start_timer(timer);
}
void destroy_video()
{
    al_destroy_display(screen);
    al_destroy_event_queue(queue);
}

int Game_establish()
{
    int msg = 0;

    //window = 9;
    //judge_next_window = 910;

    game_init();
    game_begin();

    while(msg != GAME_TERMINATE){
        msg = game_run();
        if(msg == GAME_TERMINATE)
            printf("Game over\n");
    }

    game_destroy();
    return 0;
}

void game_init()
{
    printf("Game Initializing...\n");
    al_init();
    al_install_audio();
    al_init_acodec_addon();

    display = al_create_display(WIDTH, HEIGHT);
    event_queue = al_create_event_queue();

    al_set_window_position(display, 0, 0);
    al_set_window_title(display, title);
    al_init_primitives_addon();
    al_init_font_addon(); // initialize the font addon
    al_init_ttf_addon(); // initialize the ttf (True Type Font) addon
    al_init_image_addon(); // initialize the image addon
    al_init_acodec_addon(); // initialize acodec addon
    al_install_keyboard(); // install keyboard event
    al_install_mouse();    // install mouse event
    al_install_audio();    // install audio event
    al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);

    al_register_event_source(event_queue, al_get_display_event_source( display ));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());
    fps  = al_create_timer( 1.0 / FPS );
    al_register_event_source(event_queue, al_get_timer_event_source( fps ));
    printf("loading icon\n");
    ALLEGRO_BITMAP *icon = al_load_bitmap("./image/icon.png");
    printf("load icon successfully\n");
    al_set_display_icon(display, icon);
}

void game_begin()
{
    song = al_load_sample("./sound/music.mp3");
    al_reserve_samples(20);
    sample_instance = al_create_sample_instance(song);
    al_set_sample_instance_playmode(sample_instance, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(sample_instance, al_get_default_mixer());
    al_set_sample_instance_gain(sample_instance, 0) ;
    al_play_sample_instance(sample_instance);
    al_start_timer(fps);
    menu_init();
}

void game_update()
{
    if(judge_next_window == 16)
        if(window == 1){
            menu_destroy();
            ready_init();
            judge_next_window = 0;
            window = 6;
        }
    if(judge_next_window == 62)
        if(window == 6){
            ready_destroy();
            game_scene_init();
            judge_next_window = 0;
            window = 2;

            //al_flush_event_queue(event_queue);
            key_state[ALLEGRO_KEY_W] = false;
            key_state[ALLEGRO_KEY_A] = false;
            key_state[ALLEGRO_KEY_S] = false;
            key_state[ALLEGRO_KEY_D] = false;
            key_state[ALLEGRO_KEY_SPACE] = false;
        }
    if(judge_next_window == 27)
        if( window == 2 ){
            game_scene_destroy();
            leveltwo_init();
            judge_next_window = 0;
            window = 7;

            //al_flush_event_queue(event_queue);
            key_state[ALLEGRO_KEY_W] = false;
            key_state[ALLEGRO_KEY_A] = false;
            key_state[ALLEGRO_KEY_S] = false;
            key_state[ALLEGRO_KEY_D] = false;
            key_state[ALLEGRO_KEY_SPACE] = false;
        }
    if(judge_next_window == 74)
        if( window == 7 ){
            leveltwo_destroy();
            game_scene_init2();
            judge_next_window = 0;
            window = 4;

            //al_flush_event_queue(event_queue);
            key_state[ALLEGRO_KEY_W] = false;
            key_state[ALLEGRO_KEY_A] = false;
            key_state[ALLEGRO_KEY_S] = false;
            key_state[ALLEGRO_KEY_D] = false;
            key_state[ALLEGRO_KEY_SPACE] = false;
        }
    if(judge_next_window == 49)
        if( window == 4 ){
            game_scene_destroy2();
            levelthree_init();
            judge_next_window = 0;
            window = 9;

            //al_flush_event_queue(event_queue);
            key_state[ALLEGRO_KEY_W] = false;
            key_state[ALLEGRO_KEY_A] = false;
            key_state[ALLEGRO_KEY_S] = false;
            key_state[ALLEGRO_KEY_D] = false;
            key_state[ALLEGRO_KEY_SPACE] = false;
        }
    if(judge_next_window == 910)
        if(window == 9){
            levelthree_destroy();
            game_scene_init3();
            judge_next_window = 0;
            window = 10;

            //al_flush_event_queue(event_queue);
            key_state[ALLEGRO_KEY_W] = false;
            key_state[ALLEGRO_KEY_A] = false;
            key_state[ALLEGRO_KEY_S] = false;
            key_state[ALLEGRO_KEY_D] = false;
            key_state[ALLEGRO_KEY_SPACE] = false;
        }
    if(judge_next_window == 81)
        if( window == 8 ){
            win_destroy();
            menu_init();
            judge_next_window = 0;
            window = 1;

            //al_flush_event_queue(event_queue);
            key_state[ALLEGRO_KEY_W] = false;
            key_state[ALLEGRO_KEY_A] = false;
            key_state[ALLEGRO_KEY_S] = false;
            key_state[ALLEGRO_KEY_D] = false;
            key_state[ALLEGRO_KEY_SPACE] = false;
        }
    if(judge_next_window == 1053)
        if(window == 10){
            game_scene_destroy3();
            printf("1\n");
            fail_scene3_init();
            printf("2\n");
            judge_next_window = 0;
            window = 53;

            //al_flush_event_queue(event_queue);
            key_state[ALLEGRO_KEY_W] = false;
            key_state[ALLEGRO_KEY_A] = false;
            key_state[ALLEGRO_KEY_S] = false;
            key_state[ALLEGRO_KEY_D] = false;
            key_state[ALLEGRO_KEY_SPACE] = false;
        }
    if(judge_next_window == 108)
        if(window == 10){
            game_scene_destroy3();
            win_init();
            judge_next_window = 0;
            window = 8;

            //al_flush_event_queue(event_queue);
            key_state[ALLEGRO_KEY_W] = false;
            key_state[ALLEGRO_KEY_A] = false;
            key_state[ALLEGRO_KEY_S] = false;
            key_state[ALLEGRO_KEY_D] = false;
            key_state[ALLEGRO_KEY_SPACE] = false;
        }
    if(judge_next_window == 531)
        if(window == 53){
            fail_scene3_destroy();
            menu_init();
            judge_next_window = 0;
            window = 1;
        }
    if(judge_next_window == 251)
        if( window == 2 ){
            game_scene_destroy();
            fail_scene1_init();
            judge_next_window = 0;
            window = 51;

            //al_flush_event_queue(event_queue);
            key_state[ALLEGRO_KEY_W] = false;
            key_state[ALLEGRO_KEY_A] = false;
            key_state[ALLEGRO_KEY_S] = false;
            key_state[ALLEGRO_KEY_D] = false;
            key_state[ALLEGRO_KEY_SPACE] = false;
        }
    if(judge_next_window == 511)
        if( window == 51 ){
            fail_scene1_destroy();
            menu_init();
            judge_next_window = 0;
            window = 1;
        }
    if(judge_next_window == 452)
        if( window == 4 ){
            game_scene_destroy2();
            fail_scene2_init();
            judge_next_window = 0;
            window = 52;

            //al_flush_event_queue(event_queue);
            key_state[ALLEGRO_KEY_W] = false;
            key_state[ALLEGRO_KEY_A] = false;
            key_state[ALLEGRO_KEY_S] = false;
            key_state[ALLEGRO_KEY_D] = false;
            key_state[ALLEGRO_KEY_SPACE] = false;
        }
    if(judge_next_window == 521)
        if( window == 52 ){
            fail_scene2_destroy();
            menu_init();
            judge_next_window = 0;
            window = 1;
        }
    if(judge_next_window == 999)
        if( window == 1 ){
            menu_destroy();
            judge_next_window = 0;
            window = 1;
        }
    if(judge_next_window == 13)
        if( window == 1 ){
            menu_destroy();
            operation_init();
            judge_next_window = 0;
            window = 3;
        }
    if(judge_next_window == 31)
        if( window == 3 ){
            operation_destroy();
            menu_init();
            judge_next_window = 0;
            window = 1;
        }

    if(window == 2){
        character_update();
        monster_update(1);
        time_update(1);
        blood_update(1);

        //al_flush_event_queue(event_queue);
    }
    if(window == 4){
        character_update();
        monster_update(2);
        time_update(2);
        blood_update(2);
    }
    if(window == 10){
        character_update();
        boss_update();
        monster_update(3);
        time_update(3);
        blood_update(3);

        //al_flush_event_queue(event_queue);
    }
    //al_flush_event_queue(event_queue);

}

int process_event()
{
    ALLEGRO_EVENT event;
    al_wait_for_event(event_queue, &event);

    if(window == 1)
        menu_process(event);
    if(window == 2){
        character_process(event);
        monster_process(event, 1);
        time_process(event);
        blood_process(event);
    }
    if(window == 3)
        operation_process(event);
    if(window == 4){
        character_process(event);
        monster_process(event, 2);
        time_process(event);
        blood_process(event);
    }
    if(window == 51)
        fail_scene1_process(event);
    if(window == 52)
        fail_scene2_process(event);
    if(window == 53)
        fail_scene3_process(event);
    if(window == 6)
        ready_process(event);
    if(window == 7)
        leveltwo_process(event);
    if(window == 8)
        win_process(event);
    if(window == 9)
        levelthree_process(event);
    if(window == 10){
        character_process(event);
        boss_process(event);
        monster_process(event, 3);
        time_process(event);
        blood_process(event);
    }

    if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        return GAME_TERMINATE;
    if(event.type == ALLEGRO_EVENT_TIMER)
        if(event.timer.source == fps)
            draw = true;

    if(draw)
        game_update();
    return 0;
}

void game_draw()
{
    if(window == 1)
        menu_draw();
    else if(window == 2)
        game_scene_draw();
    else if(window == 3)
        operation_draw();
    else if(window == 4)
        game_scene_draw2();
    else if(window == 51)
        fail_scene1_draw();
    else if(window == 52)
        fail_scene2_draw();
    else if(window == 53)
        fail_scene3_draw();
    else if(window == 6)
        ready_draw();
    else if(window == 7)
        leveltwo_draw();
    else if(window == 8)
        win_draw();
    else if(window == 9)
        levelthree_draw();
    else if(window == 10)
        game_scene_draw3();

    al_flip_display();
}

int game_run()
{
    int error = 0;
    if(draw){
        game_draw();
        draw = false;
    }
    if(!al_is_event_queue_empty(event_queue))
        error = process_event();


    return error;
}

void game_destroy()
{
    al_destroy_event_queue(event_queue);
    al_destroy_display(display);

    menu_destroy();
    ready_destroy();
    game_scene_destroy();
    leveltwo_destroy();
    levelthree_destroy();
    game_scene_destroy2();
    game_scene_destroy3();
    win_destroy();
    operation_destroy();
    fail_scene1_destroy();
    fail_scene2_destroy();
    fail_scene3_destroy();
    character_destroy();
    monster_destroy(3);
    boss_destroy();
    time_destroy();
    blood_destroy();
    heal_destroy();
}
