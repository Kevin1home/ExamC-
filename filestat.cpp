#include <iostream>
#include <dirent.h>
#include <map>
#include <cstring>

int main() {
    DIR* dir;
    struct dirent* entry;
    std::map<unsigned char, int> file_types;

    dir = opendir(".");
    if (dir == nullptr) {
        perror("opendir");
        return 1;
    }

    while ((entry = readdir(dir)) != nullptr) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        file_types[entry->d_type]++;
    }

    closedir(dir);

    for (const auto& [type, count] : file_types) {
        std::string type_name;
        switch (type) {
        case DT_REG: type_name = "Regular file"; break;
        case DT_DIR: type_name = "Directory"; break;
        case DT_LNK: type_name = "Symbolic link"; break;
        case DT_BLK: type_name = "Block device"; break;
        case DT_CHR: type_name = "Character device"; break;
        case DT_FIFO: type_name = "FIFO"; break;
        case DT_SOCK: type_name = "Socket"; break;
        default: type_name = "Unknown"; break;
        }
        std::cout << type_name << ": " << count << std::endl;
    }

    return 0;
}
