#asm
;// Macros
lsr4    .macro
        lsr A
        lsr A
        lsr A
        lsr A
        .endm
#endasm

/* Screen resolution is 256x224 */
#define SCREEN_WIDTH 256
#define SCREEN_HEIGHT 224

#define SPR_NUM__HERO 0
#define PAL_NUM__HERO 0

/* sprite addresses */
#define SPR_ADDR__HERO_U 0x5000
#define SPR_ADDR__HERO_UR 0x5400
#define SPR_ADDR__HERO_R 0x5800
#define SPR_ADDR__HERO_DR 0x5C00
#define SPR_ADDR__HERO_D 0x6000
#define SPR_ADDR__HERO_DL 0x6400
#define SPR_ADDR__HERO_L 0x6800
#define SPR_ADDR__HERO_UL 0x6C00

#asm
SPR_ADDR__HERO_U .equ $5000
SPR_ADDR__HERO_UR .equ $5400
SPR_ADDR__HERO_R .equ $5800
SPR_ADDR__HERO_DR .equ $5C00
SPR_ADDR__HERO_D .equ $6000
SPR_ADDR__HERO_DL .equ $6400
SPR_ADDR__HERO_L .equ $6800
SPR_ADDR__HERO_UL .equ $6C00
#endasm

/* SPRITES */
#incspr(spr_hero_u, "graphics/hero.pcx", 0, 0, 2, 8);
#incspr(spr_hero_ur, "graphics/hero.pcx", 32, 0, 2, 8);
#incspr(spr_hero_r, "graphics/hero.pcx", 64, 0, 2, 8);
#incspr(spr_hero_dr, "graphics/hero.pcx", 96, 0, 2, 8);
#incspr(spr_hero_d, "graphics/hero.pcx", 128, 0, 2, 8);
#incspr(spr_hero_dl, "graphics/hero.pcx", 160, 0, 2, 8);
#incspr(spr_hero_l, "graphics/hero.pcx", 192, 0, 2, 8);
#incspr(spr_hero_ul, "graphics/hero.pcx", 224, 0, 2, 8);
#incpal(pal_hero, "graphics/hero.pcx");

/* GLOBALS */
char joy1;
char joy1a;
char joy1_dpad;
char hero_direction;
char hero_walk_state;

int frame;
int hero_x;
int hero_y;
int spr_addr_hero;
int spr_addr_hero_modifier;
int old_spr_addr_hero;
int hero_swing;

#asm
    .bank CONST_BANK
    .org $4000
tbl_hero_spr_addr:
    ;// 0:
    .db 0
    ;// 1: U
    .db HIGH(SPR_ADDR__HERO_U)
    ;// 2: R
    .db HIGH(SPR_ADDR__HERO_R)
    ;// 3: UR
    .db HIGH(SPR_ADDR__HERO_UR)
    ;// 4: D
    .db HIGH(SPR_ADDR__HERO_D)
    ;// 5:
    .db 0
    ;// 6: DR
    .db HIGH(SPR_ADDR__HERO_DR)
    ;// 7:
    .db 0
    ;// 8: L
    .db HIGH(SPR_ADDR__HERO_L)
    ;// 9: UL
    .db HIGH(SPR_ADDR__HERO_UL)
    ;// A,B:
    .db 0,0
    ;// C: DL
    .db HIGH(SPR_ADDR__HERO_DL)
    ;// D,E,F:
    .db 0,0,0
#endasm
