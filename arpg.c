/*
 * Lochlan's ARPG
 * (c) 2014 Lochlan McIntosh
 */

#include "huc.h"
#include "arpg.h"

run_game() {
    /* init variables */
    frame = 0;
    hero_walk_state = 0;
    spr_addr_hero = SPR_ADDR__HERO_D;

     /* init sprites */
    init_satb();
    load_vram(SPR_ADDR__HERO_U, spr_hero_u, 0x400);
    load_vram(SPR_ADDR__HERO_UR, spr_hero_ur, 0x400);
    load_vram(SPR_ADDR__HERO_R, spr_hero_r, 0x400);
    load_vram(SPR_ADDR__HERO_DR, spr_hero_dr, 0x400);
    load_vram(SPR_ADDR__HERO_D, spr_hero_d, 0x400);
    load_vram(SPR_ADDR__HERO_DL, spr_hero_dl, 0x400);
    load_vram(SPR_ADDR__HERO_L, spr_hero_l, 0x400);
    load_vram(SPR_ADDR__HERO_UL, spr_hero_ul, 0x400);
    set_sprpal(PAL_NUM__HERO, pal_hero);

    /* hero sprite */
    spr_set(SPR_NUM__HERO);
    spr_x(hero_x);
    spr_y(hero_y);
    spr_pattern(spr_addr_hero);
    spr_ctrl(SIZE_MAS|FLIP_MAS, SZ_32x32|NO_FLIP);
    spr_pal(PAL_NUM__HERO);
    spr_pri(1);

    /* font */
    set_font_color(1, 0);
    set_font_pal(1);
    load_default_font();

    satb_update();
    vsync();

    /*******************************************************************************
        GAME LOOP
    *******************************************************************************/
    for(;;) {
        joy1 = joy(0);
        joy1a = joytrg(0);


        if(joy1 & JOY_UP) {
            if (frame % 8 == 0) {
                hero_walk_state++;
            }
            spr_addr_hero = SPR_ADDR__HERO_U;
        } else if(joy1 & JOY_RGHT) {
            if (frame % 8 == 0) {
                hero_walk_state++;
            }
            spr_addr_hero = SPR_ADDR__HERO_R;
        } else if(joy1 & JOY_DOWN) {
            if (frame % 8 == 0) {
                hero_walk_state++;
            }
            spr_addr_hero = SPR_ADDR__HERO_D;
        } else if(joy1 & JOY_LEFT) {
            if (frame % 8 == 0) {
                hero_walk_state++;
            }
            spr_addr_hero = SPR_ADDR__HERO_L;
        }

        if(joy1 & JOY_B) {
            hero_swing = 0x300;
        } else {
            hero_swing = 0;
        }


        if (hero_walk_state == 1) {
            spr_addr_hero_modifier = 0x100;
        } else if (hero_walk_state == 3) {
            spr_addr_hero_modifier = 0x200;
        } else{
            spr_addr_hero_modifier = 0;
        }

        hero_walk_state = hero_walk_state % 4;

        spr_set(SPR_NUM__HERO);
        spr_pattern(spr_addr_hero + spr_addr_hero_modifier);

        frame++;

        satb_update();
        vsync();
    }
}

clear_display() {
    disp_off();
    cls();
    disp_on();
}

main() {
    clear_display();
    run_game();
}
