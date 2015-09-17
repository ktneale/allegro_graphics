/*
 * Written by Kevin Neale (C) 2015.
 *
 * Type:  A simple bouncing ball which changes colour when it changes direction.
 */

#include <allegro.h>
#include <cstdlib>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_COLOURS 3

struct color_t {
    int r;
    int g;
    int b;
};

//Globals
int ball_x = 320;
int ball_y = 240;

int ball_tempX = 320;
int ball_tempY = 240;

int color_index = 0;

time_t secs;    //The seconds on the system clock will be stored here
                //this will be used as the seed for srand()

int dir;    //This will keep track of the circles direction
            //1= up and left, 2 = down and left, 3 = up and right, 4 = down and right

BITMAP *buffer; //This will be our temporary bitmap for double buffering

color_t colors[NUM_COLOURS] = {{255,0,0},{0,255,0},{0,0,255}};


void move_ball(){

    ball_tempX = ball_x;
    ball_tempY = ball_y;

    if (dir == 1 && ball_x > 10 && ball_y > 10) {
        if( ball_x == 11) {
            color_index!=(NUM_COLOURS-1) ? color_index++ :  color_index = 0;
            dir = rand()% 2 + 3;
        } else { 
            --ball_x;
            --ball_y;
        }
    } else if (dir == 2 && ball_x > 10 && ball_y < 470) {
        if( ball_x == 11) {
            color_index!=(NUM_COLOURS-1) ? color_index++ :  color_index = 0;
            dir = rand()% 2 + 3;
        } else {  
            --ball_x;
            ++ball_y;
        }
    } else if (dir == 3 && ball_x < 630 && ball_y > 10) {
        if( ball_x == 629) {
            color_index!=(NUM_COLOURS-1) ? color_index++ :  color_index = 0;
            dir = rand()% 2 + 1;
        } else {
            ++ball_x;
            --ball_y;
        }
    } else if (dir == 4 && ball_x < 630 && ball_y < 470) {
        if( ball_x == 629) {
            color_index!=(NUM_COLOURS-1) ? color_index++ :  color_index = 0;
            dir = rand()% 2 + 1;
        } else {
            ++ball_x;
            ++ball_y;
        }
    } else {
        if (dir == 1 || dir == 3)    ++dir;
        else if (dir == 2 || dir == 4)    --dir;
        color_index!=(NUM_COLOURS-1) ? color_index++ :  color_index = 0;
    }
    
    acquire_screen();
    circlefill ( buffer, ball_tempX, ball_tempY,10, makecol(0,0,0));
    circlefill ( buffer, ball_x, ball_y, 10, makecol(colors[color_index].r,
                                                     colors[color_index].g,
                                                     colors[color_index].b));
    draw_sprite( screen, buffer, 0, 0);
    release_screen();
    
    rest(5);
}    

void init(){
 
    acquire_screen();
    circlefill ( buffer, ball_x, ball_y, 10, makecol( 255, 0, 0));
    draw_sprite( screen, buffer, 0, 0);
    release_screen();
    
    time(&secs);
    srand( (unsigned int)secs);
    dir = rand() % 4 + 1;
            
}    

int main(){

    allegro_init();
    install_keyboard();
    set_color_depth(16);
    set_gfx_mode( GFX_AUTODETECT, 640, 480, 0, 0);
    
    buffer = create_bitmap( 640, 480); 
    
    init();
    
    while( !key[KEY_ESC]){
        move_ball();;
        usleep(2000);
    }
    
    return 0;

}
