/* Screen resolution is 256x224 */
#define SCREEN_WIDTH 256
#define SCREEN_HEIGHT 224

#define SPR_NUM__HERO 0
#define SPR_NUM__SWORD 1
#define PAL_NUM__HERO 0
#define PAL_NUM__SWORD 1

/* sprite addresses */
#define SPR_ADDR__HERO_U 0x5000
#define SPR_ADDR__HERO_UR 0x5400
#define SPR_ADDR__HERO_R 0x5800
#define SPR_ADDR__HERO_DR 0x5C00
#define SPR_ADDR__HERO_D 0x6000
#define SPR_ADDR__HERO_DL 0x6400
#define SPR_ADDR__HERO_L 0x6800
#define SPR_ADDR__HERO_UL 0x6C00

#define SPR_ADDR__SWORD 0x7000

/* SPRITES */
#incspr(spr_hero_u, "graphics/hero.pcx", 0, 0, 2, 8);
#incspr(spr_hero_ur, "graphics/hero.pcx", 32, 0, 2, 8);
#incspr(spr_hero_r, "graphics/hero.pcx", 64, 0, 2, 8);
#incspr(spr_hero_dr, "graphics/hero.pcx", 96, 0, 2, 8);
#incspr(spr_hero_d, "graphics/hero.pcx", 128, 0, 2, 8);
#incspr(spr_hero_dl, "graphics/hero.pcx", 160, 0, 2, 8);
#incspr(spr_hero_l, "graphics/hero.pcx", 192, 0, 2, 8);
#incspr(spr_hero_ul, "graphics/hero.pcx", 224, 0, 2, 8);

#incspr(spr_sword, "graphics/sword.pcx", 0, 0, 2, 4);

#incpal(pal_hero, "graphics/hero.pcx");
#incpal(pal_sword, "graphics/sword.pcx");

/* GLOBALS */
char joy1;
char joy1a;
char hero_direction;
char hero_walk_state;

int frame;
int hero_x;
int hero_y;
int spr_addr_hero;
int spr_addr_hero_modifier;
int old_spr_addr_hero;
int hero_swing;

int sword_x;
int sword_y;
int spr_addr_sword;
int old_spr_addr_sword;