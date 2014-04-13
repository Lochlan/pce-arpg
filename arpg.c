/*
 * Lochlan's ARPG
 * (c) 2014 Lochlan McIntosh
 */

#include "huc.h"
#include "arpg.h"

run_game() {

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
    spr_pattern(SPR_ADDR__HERO_U);
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

        spr_set(SPR_NUM__HERO);

        if(joy1 & JOY_UP) {
            spr_pattern(SPR_ADDR__HERO_U);
        } else if(joy1 & JOY_RGHT) {
            spr_pattern(SPR_ADDR__HERO_R);
        } else if(joy1 & JOY_DOWN) {
            spr_pattern(SPR_ADDR__HERO_D);
        } else if(joy1 & JOY_LEFT) {
            spr_pattern(SPR_ADDR__HERO_L);
        }

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
