#include <gb/gb.h>
#include <stdio.h>
#include <time.h>
#include "tiles/cursor.c"
#include "tiles/keyboard.c"
#include "tiles/keyboardmap.c"

void keyboard();
void changeCursorDelay();
void changeCursorPosition();
void changeCursorSprite(int);

int currentCursorSpriteIndex = 0;
unsigned int lastTime = 0;

int cursorLocations[][4][2] = {
    { { 40, 48 }, { 64, 48 }, { 88, 48 }, { 120, 48 } },
    { { 40, 72 }, { 64, 72 }, { 88, 72 }, { 120, 72 } },
    { { 40, 96 }, { 64, 96 }, { 88, 96 }, { 120, 96 } },
    { { 40, 120 }, { 64, 120 }, { 88, 120 }, { 120, 120 } },
    { { 40, 144 }, { 64, 144 }, { 88, 144 }, { 120, 144 } },
};

int cursorX = 0;
int cursorY = 0;
int maxPosX = 0;
int maxPosY = 0;

void main() {
    
    maxPosX = sizeof(cursorLocations[0]) / sizeof(cursorLocations[0][0]) - 1;
    maxPosY = sizeof(cursorLocations) / sizeof(cursorLocations[0]) - 1;

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

        keyboard();
        changeCursorPosition();
        
        changeCursorDelay(&lastTime);
        delay(100);
    }
}

void keyboard() {

    switch (joypad()) {
        case J_UP:
            cursorY = cursorY > 1 ? cursorY - 1 : cursorY;
            break;
        case J_DOWN:
            cursorY = cursorY < maxPosY ? cursorY + 1 : cursorY;
            break;
        case J_RIGHT:
            cursorX = cursorX < maxPosX ? cursorX + 1 : cursorX;
            break;
        case J_LEFT:
            cursorX = cursorX > 1 ? cursorX - 1 : cursorX;
            break;
        default:
            break;
    }
}

void changeCursorPosition() {

    int positionX = cursorLocations[cursorY][cursorX][0];
    int positionY = cursorLocations[cursorY][cursorX][1];

    move_sprite(0, positionX, positionY);
    move_sprite(1, positionX + 8, positionY);
}

void changeCursorDelay() {

    unsigned int currentTime = clock();

    if ((currentTime - lastTime) >= 20) {

        if (currentCursorSpriteIndex == 0) {
    
            currentCursorSpriteIndex = 1;
        }
        else {

            currentCursorSpriteIndex = 0;
        }

        changeCursorSprite(currentCursorSpriteIndex);
        lastTime = currentTime;
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