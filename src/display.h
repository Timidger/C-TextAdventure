
#include "player.h"
#include "items.h"
#include "utils.h"


#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_GRAY    "\x1b[37m"

#define ANSI_BLINK         "\e[5m"
#define ANSI_BOLD          "\e[1m"

#define ANSI_COLOR_RESET   "\x1b[0m"

void reset_format(void);
void hide_terminal_input(void);
void show_terminal_input(void);
char* get_input(int limit);
void print_items(player* player);
void print_item(item* item);
char* info(player* player);
char* get_item_name(item* item);
char* choose(char* options[], int num_of_options);
void raw_mode(void);
void cooked_mode(void);
