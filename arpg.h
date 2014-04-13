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

#define SPR_ADDR__TEST 0x5300

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
char hero_direction;
char hero_walk_state;

int hero_x;
int hero_y;