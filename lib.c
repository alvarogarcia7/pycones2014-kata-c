#include "lib.h"
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <printf.h>

#define MAX_USERS 100

char *(registered_users)[MAX_USERS];
int max_index = 0;
char **(follows)[MAX_USERS] = {0};
int followees[MAX_USERS] = {0};

void register_clear() {
    for (int i = 0; i < MAX_USERS && i < max_index; ++i) {
        free(registered_users[i]);
        registered_users[i] = NULL;
    }
    for (int i = 0; i < MAX_USERS && i < max_index; ++i) {
        for (int j = 0; j < followees[i]; ++j) {
            free(follows[i][j]);
            follows[i][j] = NULL;
        }
        free(follows[i]);
        follows[i] = NULL;
    }
    for (int i = 0; i < MAX_USERS && i < max_index; ++i) {
        followees[i] = 0;
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
            follows[i] = realloc(follows[i], sizeof(char *) * (this_followee + 1 + 1));
            follows[i][this_followee] = calloc(strlen(who_to_follow) + 1, sizeof(char));
            strcpy(follows[i][this_followee], who_to_follow);
            follows[i][this_followee + 1] = NULL;
            followees[i]++;
            return true;
        }
    }
    return false;
}


void print_all_users() {
    for (int i = 0; i < MAX_USERS && i < max_index; ++i) {
        printf("Registered: '%s'\n", registered_users[i]);
    }
}

char **user_is_following(char *username) {
    for (int i = 0; i < MAX_USERS && i < max_index; ++i) {
        if (strcmp(registered_users[i], username) == 0) {
            return follows[i];
        }
    }
    return NULL;
}

char **export_contents() {
    char **lines = calloc(max_index + 1, sizeof(char *));
    for (int i = 0; i < max_index; ++i) {
        int line_size = strlen(registered_users[i]) + strlen(": ");
        for (int j = 0; j < followees[i]; ++j) {
            line_size += strlen(follows[i][j]) + strlen(",");
        }
        lines[i] = calloc(line_size + 1, sizeof(char));

        strcpy(lines[i] + strlen(lines[i]), registered_users[i]);
        strcpy(lines[i] + strlen(lines[i]), ": ");
        for (int j = 0; j < followees[i]; ++j) {
            strcpy(lines[i] + strlen(lines[i]), follows[i][j]);
            strcpy(lines[i] + strlen(lines[i]), ",");
        }
        lines[i][strlen(lines[i]) + 1] = '\0';
    }

    return lines;
}


void import_contents(char **backup) {
    char *string = backup[0];
    while (strlen(string) > 0) {
        {
            int user_begin = 0, user_end = 0;
            for (int i = 0; i < strlen(string); ++i) {
                if (':' == string[i]) {
                    user_end = i - 1;
                    printf("%c %c\n", string[user_begin], string[user_end]);
                }
            }
        }
        string++;
    }
}

void print_debug_state() {
    printf("Max index: %d\n", max_index);
    for (int i = 0; i < MAX_USERS && i < max_index; ++i) {
        printf("Registered: '%s'\n", registered_users[i]);
        printf("\tFollows: ");
        for (int j = 0; j < followees[i]; ++j) {
            printf("'%s', ", follows[i][j]);
        }
        printf("\n");
    }
}