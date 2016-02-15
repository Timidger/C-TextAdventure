#include "player.h"
#include "items.h"
#include "utils.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

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
    get_item(player->items, ARRAY_SIZE(player->items), item_name);
};

bool give_item(player* player, item** item) {
    if (! item || ! *item || ! player) {
        return false;
    }
    for (int i = 0; i < ARRAY_SIZE(player->items); i++) {
        if (! player->items[i]) {
            player->items[i] = malloc(sizeof(*player->items[i]));
            memcpy(player->items[i], *item, sizeof(struct item));
            free(*item);
            *item = NULL;
            return true;
        }
    }
    return false;
}

