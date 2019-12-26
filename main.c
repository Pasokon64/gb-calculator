#include <gb/gb.h>
#include <stdio.h>
#include "tiles/keyboard.c"
#include "tiles/keyboardmap.c"

void main() {
    
    set_bkg_data(0, 103, keyboardTiles);
    set_bkg_tiles(0, 0, 20, 18, keyboardMap);

    SHOW_BKG;
    DISPLAY_ON;
}