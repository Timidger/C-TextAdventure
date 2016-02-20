#include "player.h"
#include "items.h"
#include "utils.h"
#include "display.h"

#include <assert.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

static int count_digits(int i) {
    return floor (log10 (abs (i))) + 1;
}

player* make_player(char* name) {
    if (! name) {
        return NULL;
    }
    char* error_message = "";
    player* new_player;
    if (! (new_player = malloc(sizeof(*new_player)))) {
        error_message = "Could not allocate memory for player!";
        goto cleanup;
    }
    if (! (new_player->name = malloc(strlen(name) + 1))) {
        error_message = "Could not allocate memory for the player name";
        goto cleanup;
    }
    if (! strcpy(new_player->name, name)) {
        error_message = "Could not copy string";
        goto cleanup;
    }
    new_player->health = 100;
    new_player->mana = 100;
    return new_player;

    cleanup:
        perror(error_message);
        if (new_player && new_player->name) {
            free(new_player->name);
        }
        if (new_player) {
            free(new_player);
        }
        return NULL;
}

void delete_player(player* player) {
    if (! player) {
        return;
    }
    if (player->name) {
        free(player->name);
    }
    if (player->items) {
        for (int i = 0; i < ARRAY_SIZE(player->items); i++) {
            delete_item(player->items[i]);
        }
    }
    free(player);
}

struct item* get_item_from_player(player* player, char* item_name) {
    return get_item(player->items, ARRAY_SIZE(player->items), item_name);
};

bool give_item(player* player, item** item) {
    if (! item || ! *item || ! player) {
        return false;
    }
    for (int i = 0; i < ARRAY_SIZE(player->items); i++) {
        if (! player->items[i]) {
            player->items[i] = malloc(sizeof(*player->items[i]));
            memcpy(player->items[i], *item, sizeof(struct item));
            player->items[i]->name = strdup((*item)->name);
            player->items[i]->item = strdup((*item)->item);
            delete_item(*item);
            *item = NULL;
            return true;
        }
    }
    return false;
}

char* info(player* player) {
    if ((! player ) || (! player->name) || (! player->items)) {
        return NULL;
    }
    char* output_string;
    char* header_string_format = "Your name is " ANSI_COLOR_MAGENTA "%s" ANSI_COLOR_RESET "\n";
    char header_string[sizeof(header_string_format)];
    sprintf(header_string, header_string_format, player->name);
    int header_length = strlen(header_string) + 1;
    char * inventory_string;
    int num_of_items = ARRAY_SIZE(player->items);
    if (num_of_items == 0) {
        inventory_string = "You have no inventory\n";
        output_string = malloc((header_length + strlen(inventory_string) + 1) * sizeof(*inventory_string));
        strcpy(output_string, header_string);
        strcat(output_string, inventory_string);
        return output_string;
    } else {
        inventory_string = "You have the following items:\n";
        char* list_string = "\tIn item slot %d you have a %s\n";
        // Count the size of the strings we have to add
        int item_string_length = 0;
        for (int i = 0; i < num_of_items; i++) {
            char* name = get_item_name(player->items[i]);
            if (name) {
                item_string_length += strlen(name) + 1;
                free(name);
            }
            // Get the number of digits, add to how many bytes we need to add
            item_string_length += count_digits(i + 1);
        }
        // That 1000 is to give it enough room. Not sure how to calculate exactly how much it needs, but that's enough...
        int output_string_size = 1000 + (header_length + strlen(inventory_string) + 1 + item_string_length) * sizeof(*inventory_string);
        output_string = malloc(output_string_size);
        strcat(output_string, header_string);
        strcat(output_string, inventory_string);
        for (int i = 0; i < num_of_items; i++) {
            char* name = get_item_name(player->items[i]);
            int buffer_size = strlen(list_string) + strlen(name) + 1 + count_digits(i + 1);
            char buffer[buffer_size];
            if (sprintf(buffer, list_string, i+1, name) < 0) {
                perror("Could not format the string properly");
                free(name);
                return NULL;
            }
            assert(strlen(buffer) <= buffer_size);
            free(name);
            strcat(output_string, buffer);
            assert(strlen(output_string) <= output_string_size);
        }
        return output_string;
    }
}

void set_player_gender(player* player, gender option) {
    if (! player || ! player->name) {
        perror("Player not initalised properly");
        return;
    }
    player->gender = option;
}
