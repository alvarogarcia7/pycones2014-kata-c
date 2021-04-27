#include <stdio.h>
#include <string.h>
#include "lib.h"

int main(int argc, char **argv) {
    
    import_contents()
    if (argc >= 3 && strcmp(argv[2], "f") == 0 ){
        follow_user(argv[1], argv[2]);
    }
    printf("Hello, World!\n");
    return 0;
}
