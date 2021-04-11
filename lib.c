#include "lib.h"
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERS 100

char *(registered_users)[MAX_USERS];
int max_index = 0;
char **(follows)[MAX_USERS];
int followees[MAX_USERS] = {0};

void register_clear() {
    for (int i = 0; i < MAX_USERS && i < max_index; ++i) {
        free(registered_users[i]);
    }
    max_index = 0;
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

bool follow_user(char *username, char *who_to_follow) {
    for (int i = 0; i < MAX_USERS && i < max_index; ++i) {
        if (strcmp(registered_users[i], username) == 0) {
            int this_followee = followees[i] + 1;
            follows[i] = realloc(follows[i], sizeof(char **) * this_followee);
            follows[i][this_followee] = calloc(strlen(who_to_follow), sizeof(char));
            strcpy(follows[i][this_followee], who_to_follow);
            followees[i]++;
            return true;
        }
    }
    return false;
}

char **user_is_following(char *username) {
    for (int i = 0; i < MAX_USERS && i < max_index; ++i) {
        if (strcmp(registered_users[i], username) == 0) {
            return follows[i];
        }
    }
    return NULL;
}