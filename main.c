#include <stdio.h>
#include <string.h>
#include "lib.h"
#include <stdlib.h>

int import_from_file(const char *FILENAME) {
    char *line_buf = NULL;
    size_t line_buf_size = 0;
    ssize_t line_size;
    FILE *fp = fopen(FILENAME, "r");
    if (!fp)
    {
        fprintf(stderr, "Error opening file '%s'\n", FILENAME);
        return EXIT_FAILURE;
    }

    line_size = getline(&line_buf, &line_buf_size, fp);

    while (line_size >= 0)
    {
        import_contents(line_buf);
        line_size = getline(&line_buf, &line_buf_size, fp);
    }

    free(line_buf);
    line_buf = NULL;

    fclose(fp);
    return 0;
}

int export_to_file(const char *FILENAME) {
    FILE *fp = fopen(FILENAME, "w");
    if (!fp)
    {
        fprintf(stderr, "Error opening file '%s'\n", FILENAME);
        return EXIT_FAILURE;
    }

    char **results = export_contents();

    int i = 0;
    while (results[i] != NULL)
    {
        fprintf(fp, "%s", results[i]);
        i++;
    }

    fclose(fp);
    return 0;
}

int main(int argc, char **argv) {

    import_from_file("../export.db");
    if (argc >= 4 && strcmp(argv[2], "f") == 0 ){
        follow_user(argv[1], argv[3]);
        char **lines = export_contents();
        print_debug_state();
        int i =0;
        while(lines[i] != NULL){
            printf("%s\n", lines[i]);
            i++;
        }
    }
    export_to_file("../export.db");
    return 0;
}
