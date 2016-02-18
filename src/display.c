#include "display.h"
#include "player.h"
#include "items.h"

#include <stdio.h>
#include <string.h>



#define COLOR_PRELUDE "<" ANSI_COLOR_GREEN
#define END_COLOR ANSI_COLOR_RESET ">" 
#define COLOR_ITEM COLOR_PRELUDE ANSI_COLOR_GREEN

void reset_format(void) {
    printf(ANSI_COLOR_RESET);
}

void print_items(player* player) {
    for (int i = 0; i < ARRAY_SIZE(player->items); i++) {
        print_item(player->items[i]);
    }
}

void print_item(item* item) {
    char* name = get_item_name(item);
    printf("%s\n", name);
    free(name);
}

char* get_item_name(item* item) {
    if ((! item) || (! item->name)) {
        return strdup(ANSI_COLOR_RESET "<" ANSI_COLOR_GRAY "Nothing" ANSI_COLOR_RESET ">");
    }
    char* output_string;
    if (! (output_string  = calloc(strlen(item->name) + 1 + strlen(COLOR_ITEM) + 1 + strlen(END_COLOR) + 2, sizeof(char)))) {
        perror("Could not allocate memory for string!");
        return NULL;
    }
    
    if ((sprintf(output_string, COLOR_ITEM "%s" END_COLOR, item->name)) < 0) {
        perror("Could not format string properly!");
        if (! (strcpy(output_string, item->name))) {
            perror("Could not recover string formatting");
            free(output_string);
            return NULL;
        }
    }
    return output_string;
}

