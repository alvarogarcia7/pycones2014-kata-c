#include "lib.h"
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERS 100

char *(registered_users)[MAX_USERS];
int max_index =0;

void register_clear(){
    for (int i = 0; i < MAX_USERS && i < max_index; ++i) {
        free(registered_users[i]);
    }
    max_index =0;
}

bool register_user(char *username) {
    int i = 0;
    for (i = 0; i < MAX_USERS && i < max_index; ++i) {
        if (strcmp(registered_users[i], username) == 0) {
            return false;
        }
    }
    registered_users[i] = calloc(strlen(username) + 1, sizeof(char));
    strcpy(registered_users[i], username);
    max_index++;
    return true;
}
