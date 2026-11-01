#include <stdio.h>
#include <dirent.h>

int traverse_dir(const char *path) {
    DIR* directory = opendir(path);
    if (!directory) {
        perror("opendir");
        return -1;
    }

    struct dirent *entry;
    while ((entry = readdir(directory)) != NULL) {
        const char* directory_name = entry->d_name;
        printf("%s\n", directory_name);

        if (entry->d_type == DT_DIR) {
            // directory
        } else {
            // file
        }
    }

    return 0;
}

int main(int argc, const char *argv[]) {
    const char *default_path = "./";
    if (argc > 1) {
        default_path = argv[1];
    }
    int error = traverse_dir(default_path);
    return 0;
}
