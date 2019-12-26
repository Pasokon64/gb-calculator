#include <gb/gb.h>
#include <stdio.h>
#include "tiles/cursor.c"
#include "tiles/keyboard.c"
#include "tiles/keyboardmap.c"

int currentCursorSpriteIndex = 0;

void changeCursorSprite(int);

void main() {
    
    SPRITES_8x16;
    set_sprite_data(0, 8, cursor);
    set_sprite_tile(0, 0);
    set_sprite_tile(1, 2);

    move_sprite(0, 40, 72);
    move_sprite(1, 48, 72);

    set_bkg_data(0, 103, keyboardTiles);
    set_bkg_tiles(0, 0, 20, 18, keyboardMap);

    SHOW_BKG;
    SHOW_SPRITES;
    DISPLAY_ON;

    while (1) {
        
        if (currentCursorSpriteIndex == 0) {
    
            currentCursorSpriteIndex = 1;
        }
        else {

            currentCursorSpriteIndex = 0;
        }
        
        changeCursorSprite(currentCursorSpriteIndex);
        delay(1000);
    }
}

void changeCursorSprite(int index) {

    if (index == 0) {
        
        set_sprite_tile(0, 0);
        set_sprite_tile(1, 2);
    }
    else {

        set_sprite_tile(0, 4);
        set_sprite_tile(1, 6);
    }
}