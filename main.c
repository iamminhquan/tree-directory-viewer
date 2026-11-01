#include <dirent.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ANSI_COLOR_PINK "\x1b[38;5;213m"

char *directory_color() { return ANSI_COLOR_PINK; }
void reset_color() { printf("\033[0m"); }

void print_file(const char *name, bool is_directory, int indent) {
    // indent with 2 spaces per level
    if (indent) {
        printf("%*s", indent * 2, "");
    }

    if (is_directory) {
        printf("%s%s", directory_color(), name);
        reset_color();
        printf("\n");
    } else {
        printf("%s\n", name);
    }
}

int traverse_dir(const char *path, int indent) {
    DIR *directory = opendir(path);
    if (!directory) {
        perror("opendir");
        return -1;
    }

    struct dirent *entry;
    while ((entry = readdir(directory)) != NULL) {
        const char *directory_name = entry->d_name;

        // skip the . and .. directories
        if (strcmp(directory_name, ".") == 0 ||
            strcmp(directory_name, "..") == 0) {
            continue;
        }

        if (entry->d_type == DT_DIR) {
            // directory
            print_file(directory_name, true, indent);

            // traverse to sub_path
            size_t length = strlen(path) + strlen(directory_name) + 2;
            char *sub_path = malloc(length);
            snprintf(sub_path, length, "%s/%s", path, directory_name);
            traverse_dir(sub_path, indent + 1);
            free(sub_path);
        } else {
            // file
            print_file(directory_name, false, indent);
        }
    }

    closedir(directory);
    return 0;
}

int main(int argc, const char *argv[]) {
    const char *default_path = "./";
    if (argc > 1) {
        default_path = argv[1];
    }
    int error = traverse_dir(default_path, 0);
    return error == 0 ? 0 : 1;
}
