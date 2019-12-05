#include <stdio.h>
#include <stdlib.h>
#include<string.h> 

#define COMPARE(a, b) (strcmp(a, b) == 0)

#define MAP_STRING_TO_INT(str, integer) if (COMPARE(name, str)) return integer;

#define CHECK_AND_JUMP if (code_index >= argc || code_i >= 30) goto PROC;

// We should not need more than 30 codes...
int codes[30] = { -1 };

int code_from_name(char * name) {
    MAP_STRING_TO_INT("black", 30)
    MAP_STRING_TO_INT("red", 31)
    MAP_STRING_TO_INT("green", 32)
    MAP_STRING_TO_INT("yellow", 33)
    MAP_STRING_TO_INT("blue", 34)
    MAP_STRING_TO_INT("magenta", 35)
    MAP_STRING_TO_INT("cyan", 36)
    MAP_STRING_TO_INT("white", 37)

    MAP_STRING_TO_INT("bold", 1)
    MAP_STRING_TO_INT("italics", 3)
    MAP_STRING_TO_INT("underline", 4)
    MAP_STRING_TO_INT("crossed", 9)

    return -1;
}

int main(int argc, char * argv[]) {
    /* 
    * $ colorizer "message" "foreground color" "optional background color" "style colors"...
    */

    if (argc < 2) {
        return 1;
    }

    char * message = argv[1];
    int code_index = 2;
    int code = -1;
    int code_i = 0;

    char * output = malloc(sizeof(char) * 500);
    sprintf(output, "\x1B[");

    char * end = "\x1B[0m";

    // Foreground
    int fg = code_from_name(argv[code_index++]);
    codes[code_i++] = fg;
    CHECK_AND_JUMP;

    int bg = code_from_name(argv[code_index++]);

    // Backgrounds start at 40
    if (bg > 29 && bg < 38) bg += 10;
    
    codes[code_i++] = bg;
    CHECK_AND_JUMP;
    
    while (code_index < argc && code_i < 30) {
        bg = code_from_name(argv[code_index ++]);
        codes[code_i++] = bg;
    }

PROC:;
    int i = 0;
    for (i = 0; i < code_i; i ++) {
        char * partial = malloc(sizeof(char) * 50);
        sprintf(partial, ";%d", codes[i]);
        strcat(output, partial);
        free(partial);
    }
    strcat(output, "m");
    strcat(output, message);
    strcat(output, end);
    puts(output);
    free(output);
    return 0;
}
