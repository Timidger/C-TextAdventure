#include "items.h"


#include <string.h>
#include <stdio.h>
#include <stdlib.h>

item* new_item(char* name, item_type type, void* item) {
    if (! name || ! item) {
        return NULL;
    }
    char* error_message = "";
    struct item* new_item;
    new_item = malloc(sizeof(*new_item));
    if (! new_item) {
        error_message = "Could not allocate memory for a new item!";
        goto cleanup;
    }
    new_item->name = malloc(strlen(name) + 1);
    if (! new_item->name) {
        error_message = "Could not allocate space to copy the string!";
        goto cleanup;
    }
    if (! strcpy(new_item->name, name)) {
        error_message = "Could not copy string!";
        goto cleanup;
    }
    new_item->type = type;
    new_item->item = item;
    return new_item;

    cleanup:
       perror(error_message); 
       if (new_item && new_item->name) {
           free(new_item->name);
       }
       if (new_item) {
           free(new_item);
       }
       return NULL;
}

actionable* new_actionable() {
    actionable* new_item;
    new_item =  malloc(sizeof(*new_item));
    if (! new_item) {
        perror("Could not allocate memory for an actionable");
        return NULL;
    }
    return new_item;
}

weapon* new_weapon(int damage) {
    weapon* new_item;
    new_item =  malloc(sizeof(*new_item));
    if (! new_item) {
        perror("Could not allocate memory for an weapon");
        return NULL;
    }
    new_item->damage = damage;
    return new_item;
}

consumable* new_consumable(int health, int mana) {
    consumable* new_item;
    new_item =  malloc(sizeof(*new_item));
    if (! new_item) {
        perror("Could not allocate memory for an consumable");
        return NULL;
    }
    new_item->health = health;
    new_item->mana = mana;
    return new_item;
}
potion* new_potion(effect effect_function) {
    potion* new_item;
    new_item =  malloc(sizeof(*new_item));
    if (! new_item) {
        perror("Could not allocate memory for an potion");
        return NULL;
    }
    new_item->effect_function = effect_function;
    return new_item;
}

item* get_item(item* items[], int item_size, char* item_name) {
    if (! items || item_size <= 0 || ! item_name) {
        return NULL;
    }
    for (int i = 0; i < item_size; i++) {
        if (! items[i]) {
            continue;
        }
        if (items[i]->name == item_name) {
            return items[i];
        }
    }
    return NULL;
}

void delete_item(item* item) {
    if (! item) {
        return;
    }
    if (item->name) {
        free(item->name);
    }
    // If the other types become more complicated, this has to free their mem
    if (item->item) {
        free(item->item);
    }
    free(item);
}


