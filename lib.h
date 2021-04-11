#ifndef PYCONES2014_KATA_LIB_H
#define PYCONES2014_KATA_LIB_H

#include <stdbool.h>

bool register_user(char *username);
void register_clear();

bool follow_user(char *username, char *who_to_follow);
char **user_is_following(char *username);

#endif //PYCONES2014_KATA_LIB_H
