#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "display.h"
#include "player.h"
#include "items.h"
#include "utils.h"


void test(void) {
    player* player = make_player("Timidger");
    item* compass = new_item("Compass", actionable_type, (void*) new_actionable());
    item* sword = new_item("Sword", weapon_type, (void*) new_weapon(5));
    item* health_potion = new_item("Healing Potion", consumable_type, (void*) new_consumable(25, 0));
    // Item is set to null here and freed
    // The memory is copied and given to the player
    reset_format();
    char*  player_info;
    player_info = info(player);
    printf(player_info);
    free(player_info);
    give_item(player, &compass);
    give_item(player, &sword);
    give_item(player, &health_potion);

    player_info = info(player);
    printf(player_info);
    free(player_info);
    // This deletes the items he owns
    delete_player(player);
    // Should print nothing now that he is deleted
    player_info = info(player);
    free(player_info);
    printf(player_info);
    // This does nothing, but if we remove the give item to player, this will actually free the item
    // Because we gave it to player though, the item has already been freed and set to null
    delete_item(compass);
}

// Should figure out where to put. Player? Display? Some input module?
gender parse_gender(char* input) {
    if (strcmp(input, "boy") == 0) {
        return boy;
    } else if (strcmp(input, "girl") == 0) {
        return girl;
    } else if (strcmp(input, "neither") == 0) {
        return neither;
    } else {
        perror("Incorrect gender choice");
        exit(-1);
        //return neither;
    }
}


int main(int argc, char* argv[]) {
    if (argc > 1 && strcmp(argv[1], "--test") == 0) {
        test();
        return 0;
    }
    reset_format();
    printf( "You awaken in a room. A very familiar room. This is your room. It has been your room for as"
            " long as you can remember. Unfortunately it will not be your room for very long. Your "
            ANSI_BOLD "PARENTS " ANSI_COLOR_RESET "have decided that your room will be taken by "
            "your parent's new baby, " ANSI_BOLD "ALEX" ANSI_COLOR_RESET ", born just last week."
            " For the first week he was sleeping your parents, but they soon got tired of that. So they fixed the"
            " leaky pipe that had caused the basement to leak last year so that they could put the baby in your room"
            " while you would take the basement. They didn't ask you of course. Not their lovely first born."
            " Not their straight A, wonderful, positively angelic first child named . . .\n\n"
            " What is your name again" ANSI_BLINK " . . . ?" ANSI_COLOR_RESET);
    fflush(stdout);

    // Single key input grab
    raw_mode();
    hide_terminal_input();
    getchar();
    show_terminal_input();
    cooked_mode();

    // Actually get the name
    printf("\n\nName: ");
    char* name = malloc(32);
    name = get_input(32);
    // Make the player
    player* player = make_player(name);
    printf(". . . named" ANSI_COLOR_MAGENTA " %s" ANSI_COLOR_GRAY "!"
           " Of course. You know your own name."
           "  Though you have always thought it a stupid name"
          " for a " ANSI_BLINK ". . ." ANSI_COLOR_RESET "\n", name);
    // Get gender
    char* options[] = {"boy", "girl", "neither"};
    char* chosen = choose(options, ARRAY_SIZE(options));
    // Set the gender
    set_player_gender(player, parse_gender(chosen));
    char gender_text[1000];
    char* baby_gender;
    char* baby_pronoun;
    switch(player->gender) {
        case boy:
        case girl:
            baby_gender =  (strcmp(chosen, "boy") == 0) ? "sister" : "brother";
            baby_pronoun = (strcmp(chosen, "boy") == 0) ? "she" : "he";
            sprintf(gender_text, "A %s! " ANSI_COLOR_MAGENTA "%s" ANSI_COLOR_RESET
                   " is such a stupid name for a %s, you much prefer the "
                   "name " ANSI_BOLD "ALEX" ANSI_COLOR_RESET ". "
                   "But of course your stupid parents went and "
                   "called your new baby %s that. Probably just to mess with you. "
                   "Jokes on them though, they'll probably have to spend a fortune "
                   "in therapy bills for all the crap %s'll have to put up with in school."
                   " You should know, you're only in 7th grade and you've been bullied"
                   " ruthlessly for being a %s named " ANSI_COLOR_MAGENTA "%s" ANSI_COLOR_RESET
                   ", which isn't nearly as bad as being a %s named " ANSI_BOLD "ALEX" ANSI_COLOR_RESET 
                   ANSI_BLINK ". . ." ANSI_COLOR_RESET "\n",
                   chosen, player->name, chosen, baby_gender, baby_pronoun, chosen, player->name, chosen);
            break;
        case neither:
            strcpy(gender_text, NULL);
            break;
    }
    printf(gender_text, player->name);
    return 0;
}
