#include "math.h"
#include "util.h"
#include <stdio.h>
#include <string.h>

char * sum(char *n1, char *n2) {

    size_t i;
    int num1[12] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int num2[12] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int result[12] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int lastIndex1 = strlen(n1) - 1;
    int lastIndex2 = strlen(n2) - 1;

    char resultString[12] = "\0";
    int printZero = 0;

    clearString(resultString);

    for (i = 0; i <= lastIndex1; i++)
    {
        num1[lastIndex1 - i] = (int)n1[i] - 48;
    }

    for (i = 0; i <= lastIndex2; i++)
    {
        num2[lastIndex2 - i] = (int)n2[i] - 48;
    }
    
    for (i = 0; i < 12; i++)
    {
        int sRes = num1[i] + num2[i];

        if (sRes > 9)
        {
            result[i] += sRes % 10;
            num1[i + 1] += sRes / 10;
        }
        else 
        {
            result[i] += sRes;
        }
    }

    for (i = 11; i > 0; i--)
    {
        int number = result[i];

        if (number != 0 || printZero)
        {
            char digit = (char)(number + 48);

            printZero = 1;
            resultString[strlen(resultString)] = digit;
        }
    }

    return resultString;
}