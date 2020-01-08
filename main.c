#include <gb/gb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "math.c"
#include "util.c"
#include "tiles/cursor.c"
#include "tiles/keyboard.c"
#include "tiles/keyboardmap.c"

void solve();
void keyboard();
void action(char);
void updateDisplay();
void addToDisplay(char);
void changeCursorDelay();
void storeOperation(char);
void changeCursorPosition();
void changeCursorSprite(int);

char n1[12] = "0";
char n2[12] = "0";
char operation = '\0';
char display[12] = "0";

unsigned int lastTime = 0;
int currentCursorSpriteIndex = 0;

int cursorLocations[][4][2] =
{
    {{40, 48}, {64, 48}, {88, 48}, {120, 48}},
    {{40, 72}, {64, 72}, {88, 72}, {120, 72}},
    {{40, 96}, {64, 96}, {88, 96}, {120, 96}},
    {{40, 120}, {64, 120}, {88, 120}, {120, 120}},
    {{40, 144}, {64, 144}, {88, 144}, {120, 144}},
};

char keyboardOptions[][4] =
{
    {' ', 'c', '<', '/'},
    {'7', '8', '9', '*'},
    {'4', '5', '6', '-'},
    {'1', '2', '3', '+'},
    {'%', '0', ',', '='}
};

int cursorX = 0;
int cursorY = 0;
int maxPosX = 0;
int maxPosY = 0;

int keydown = 0;
int shiftOperator = 0;

void main()
{
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

    while (1)
    {
        keyboard();
        updateDisplay();
        changeCursorPosition();

        changeCursorDelay(&lastTime);
    }
}

void updateDisplay() {

    int i;
    char displayMap[24];

    for (i = 0; i < 12; i++)
    {
        if (display[i] != '\0' && display[i] != ' ')
        {
            int c = 80 + (((int)display[i] - 48) * 2);
            displayMap[i] = c; 
            displayMap[12 + i] = c + 1;
        }
        else 
        {
            displayMap[i] = 0;
            displayMap[12 + i] = 0;
        }
    }

    set_bkg_tiles(4, 1, 12, 2, displayMap);
}

void keyboard()
{
    if (keydown)
    {
        waitpadup();
        keydown = 0;
    }

    switch (joypad())
    {
    case J_UP:
        cursorY = cursorY > 1 ? cursorY - 1 : cursorY;
        keydown = 1;
        break;
    case J_DOWN:
        cursorY = cursorY < maxPosY ? cursorY + 1 : cursorY;
        keydown = 1;
        break;
    case J_RIGHT:
        cursorX = cursorX < maxPosX ? cursorX + 1 : cursorX;
        keydown = 1;
        break;
    case J_LEFT:
        cursorX = cursorX > 1 ? cursorX - 1 : cursorX;
        keydown = 1;
        break;
    case J_A:
        action(keyboardOptions[cursorY][cursorX]);
        keydown = 1;
        break;
    default:
        break;
    }
}

void action(char option)
{
    if (shiftOperator)
    {
        shiftOperator = 0;
        clearString(&display);
    }

    switch (option)
    {
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
        addToDisplay(option);
        break;
    case '+':
    case '-':
    case '*':
    case '/':
        storeOperation(option);
        break;
    case '=':
        solve();
        break;
    default:
        break;
    }
}

void addToDisplay(char option)
{
    if (strlen(display) < 12)
    {
        if (display[0] == '0' && display[1] != ',')
        {
            display[0] = option;
        }
        else
        {
            display[strlen(display)] = option;
        }
    }
}

void storeOperation(char option) {

    if (operation == '\0')
    {
        strcpy(n1, display);
        operation = option;
        shiftOperator = 1;
    }
    else 
    {
        solve();
        strcpy(n1, display);
        operation = option;
        shiftOperator = 1;
    }
}

void solve() {

    char result[12];
    strcpy(n2, display);

    switch (operation)
    {
    case '+':
        strcpy(result, sum(n1, n2));
        break;
    
    default:
        break;
    }

    operation = '\0';
    clearString(&n1);
    clearString(&n2);
    clearString(&display);
    strcpy(display, result);
}

void changeCursorPosition()
{
    int positionX = cursorLocations[cursorY][cursorX][0];
    int positionY = cursorLocations[cursorY][cursorX][1];

    move_sprite(0, positionX, positionY);
    move_sprite(1, positionX + 8, positionY);
}

void changeCursorDelay()
{
    unsigned int currentTime = clock();

    if ((currentTime - lastTime) >= 20)
    {
        if (currentCursorSpriteIndex == 0)
        {
            currentCursorSpriteIndex = 1;
        }
        else
        {
            currentCursorSpriteIndex = 0;
        }

        changeCursorSprite(currentCursorSpriteIndex);
        lastTime = currentTime;
    }
}

void changeCursorSprite(int index)
{
    if (index == 0)
    {
        set_sprite_tile(0, 0);
        set_sprite_tile(1, 2);
    }
    else
    {
        set_sprite_tile(0, 4);
        set_sprite_tile(1, 6);
    }
}