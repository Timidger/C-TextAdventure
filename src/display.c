#include "display.h"
#include "player.h"
#include "items.h"

#include <stdbool.h>
#include <termios.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>



#define COLOR_PRELUDE "<" ANSI_COLOR_GREEN
#define END_COLOR ANSI_COLOR_RESET ">" 
#define COLOR_ITEM COLOR_PRELUDE ANSI_COLOR_GREEN


struct termios OLD, NEW;
bool TERMINAL_INPUT_HIDDEN = false;

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

void hide_terminal_input(void) {
    if (TERMINAL_INPUT_HIDDEN) {
        return;
    }
    if (tcgetattr (fileno (stdout), &OLD) != 0) {
        perror("Could not hide character input!");
        return;
    }
    NEW = OLD;
    NEW.c_lflag &= ~ECHO;
    if (tcsetattr (fileno (stdout), TCSAFLUSH, &NEW) != 0) {
        perror("Could not hide character input!");
        return;
    }
    TERMINAL_INPUT_HIDDEN = true;
}

void show_terminal_input(void) {
    if (! TERMINAL_INPUT_HIDDEN) {
        return;
    }
    (void) tcsetattr (fileno (stdout), TCSAFLUSH, &OLD);
    TERMINAL_INPUT_HIDDEN = false;
}

char* get_input(int limit) {
    char input[limit];
    fgets(input, limit, stdin);
    // Remove the new line
    input[strlen(input) - 1] = 0;
    return strdup(input);
}

char* choose(char* options[], int num_of_options) {
    printf("Choose one of the following:\n");
    int max_length = 0;
    int length = 0;
    for (int i = 0; i < num_of_options; i++) {
        printf("\t%d: " ANSI_BOLD "%s" ANSI_COLOR_RESET "\n", i+1, options[i]);
        // Plus one cause null ptr
        length = strlen(options[i]) + 1;
        if (length > max_length) {
            // And another cause fgets assumes another
            max_length = length + 1;
        }
    }
    char input[max_length];
    char* input_ptr = input;
    while (true) {
        input_ptr = get_input(max_length);
        for (int i = 0; i < num_of_options; i++) {
            if (strcasecmp(options[i], input_ptr) == 0) {
                return options[i];
            }
        }
    }
    perror("Fell out of infinite loop");
    return NULL;
}
 
void raw_mode(void) {
    system("/bin/stty raw");
}
void cooked_mode(void) {
    system("/bin/stty cooked");
}
