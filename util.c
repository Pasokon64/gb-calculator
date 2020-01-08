#include "util.h"
#include <stdio.h>

void clearString(char* text) {

    size_t i;

    for (i = 0; i < 12; i++)
    {
        text[i] = '\0';
    }
}