#include "lib.h"
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERS 100

char *(registered_users)[MAX_USERS];
int max_index = 0;
char **(follows)[MAX_USERS] = {0};
int followees[MAX_USERS] = {0};

void register_clear() {
    for (int i = 0; i < MAX_USERS && i < max_index; ++i) {
        free(registered_users[i]);
    }
    for (int i = 0; i < MAX_USERS && i < max_index; ++i) {
        free(follows[i]);
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
            int this_followee = followees[i];
            char **followees = follows[i];

            followees = realloc(followees, sizeof(char **) * this_followee + 1 + 1);
            followees[this_followee] = calloc(strlen(who_to_follow), sizeof(char));
            strcpy(followees[this_followee], who_to_follow);
            followees[this_followee + 1] = NULL;
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