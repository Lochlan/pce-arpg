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
    sword_x = 100;
    sword_y = 100;
    spr_addr_sword = SPR_ADDR__SWORD + 0x100;
    joy1_dpad = 0;

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
    load_vram(SPR_ADDR__SWORD, spr_sword, 0x200);

    set_sprpal(PAL_NUM__HERO, pal_hero);
    set_sprpal(PAL_NUM__SWORD, pal_sword);

    /* hero sprite */
    spr_set(SPR_NUM__HERO);
    spr_x(hero_x);
    spr_y(hero_y);
    spr_pattern(spr_addr_hero);
    spr_ctrl(SIZE_MAS|FLIP_MAS, SZ_32x32|NO_FLIP);
    spr_pal(PAL_NUM__HERO);
    spr_pri(1);

    /* sword sprite */
    spr_set(SPR_NUM__SWORD);
    spr_x(sword_x);
    spr_y(sword_y);
    spr_pattern(spr_addr_sword);
    spr_ctrl(SIZE_MAS|FLIP_MAS, SZ_16x16|NO_FLIP);
    spr_pal(PAL_NUM__SWORD);
    spr_pri(0);

    /* font */
    set_font_color(1, 0);
    set_font_pal(0);
    load_default_font();

    satb_update();
    vsync();

    /*******************************************************************************
        GAME LOOP
    *******************************************************************************/
    for(;;) {
        joy1 = joy(0);
        joy1a = joytrg(0);
        old_spr_addr_hero = spr_addr_hero;
        old_spr_addr_sword = spr_addr_sword;

        /* d-pad input */
        #asm
            lda         _joy1
            lsr4
            sta         _joy1_dpad
            bne         movement_input
            jmp         no_movement_input
        movement_input:
        #endasm
        if (joy1 & JOY_UP) hero_y--;
        else if (joy1 & JOY_DOWN) hero_y++;

        if (joy1 & JOY_LEFT) hero_x--;
        else if (joy1 & JOY_RGHT) hero_x++;

        if (frame % 8 == 0) hero_walk_state++;
        #asm
            ldx         _joy1_dpad
            ;// lower nibble of _spr_addr_hero already zeroed
            lda         tbl_hero_spr_addr,X
            sta         _spr_addr_hero+1
        no_movement_input:
        #endasm

        /* sword */
        if (joy1 & JOY_UP) {
            if (joy1 & JOY_LEFT) {
                spr_addr_sword = SPR_ADDR__SWORD + 0x1C0;
            } else if (joy1 & JOY_RGHT) {
                spr_addr_sword = SPR_ADDR__SWORD + 0x40;
            } else {
                spr_addr_sword = SPR_ADDR__SWORD;
            }
        } else if (joy1 & JOY_DOWN) {
            if (joy1 & JOY_LEFT) {
                spr_addr_sword = SPR_ADDR__SWORD + 0x140;
            } else if (joy1 & JOY_RGHT) {
                spr_addr_sword = SPR_ADDR__SWORD + 0xC0;
            } else {
                spr_addr_sword = SPR_ADDR__SWORD + 0x100;
            }
        } else if (joy1 & JOY_LEFT) {
            spr_addr_sword = SPR_ADDR__SWORD + 0x180;
        } else if (joy1 & JOY_RGHT) {
            spr_addr_sword = SPR_ADDR__SWORD + 0x80;
        }

        /* a/b input */
        if (joy1 & JOY_A) {
            spr_addr_hero_modifier = 0x300;
            if (spr_addr_hero != old_spr_addr_hero) {
                if (frame % 4) {
                    spr_addr_hero = old_spr_addr_hero;
                } else {
                    if (!(joy1a & JOY_A)) {
                        spr_addr_hero = old_spr_addr_hero + 0x400;
                        if (spr_addr_hero > 0x6C00) spr_addr_hero = 0x5000;
                    }
                }
            }
        } else if (joy1 & JOY_B) {
            spr_addr_hero_modifier = 0x300;
            if (spr_addr_hero != old_spr_addr_hero) {
                if (frame % 4) {
                    spr_addr_hero = old_spr_addr_hero;
                } else {
                    if (!(joy1a & JOY_B)) {
                        spr_addr_hero = old_spr_addr_hero - 0x400;
                        if (spr_addr_hero < 0x5000) spr_addr_hero = 0x6C00;
                    }
                }
            }
        } else {
            /* hero direction walk animation*/
            if (hero_walk_state == 1) {
                spr_addr_hero_modifier = 0x100;
            } else if (hero_walk_state == 3) {
                spr_addr_hero_modifier = 0x200;
            } else{
                spr_addr_hero_modifier = 0;
            }
        }

        spr_set(SPR_NUM__HERO);
        spr_pattern(spr_addr_hero + spr_addr_hero_modifier);
        spr_x(hero_x);
        spr_y(hero_y);

        spr_set(SPR_NUM__SWORD);
        spr_pattern(spr_addr_sword);
        spr_x(sword_x);
        spr_y(sword_y);

        hero_walk_state = hero_walk_state % 4;
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
