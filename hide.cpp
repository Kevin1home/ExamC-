#include <iostream>
#include <unistd.h>
#include <sys/stat.h>
#include <string>

const char* DARK_DIR = "./.darkdir";

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <file-to-hide>\n";
        return 1;
    }

    const char* sourceFile = argv[1];

    if (access(sourceFile, F_OK) != 0) {
        std::cerr << "Error: The specified file does not exist.\n";
        return 1;
    }

    if (mkdir(DARK_DIR, 0311) != 0 && errno != EEXIST) {
        std::cerr << "Error: Could not create dark directory.\n";
        return 1;
    }

    std::string targetFile = std::string(DARK_DIR) + "/" + std::string(sourceFile);

    if (rename(sourceFile, targetFile.c_str()) != 0) {
        std::cerr << "Error: Could not move the file to the dark directory.\n";
        return 1;
    }

    std::cout << "File hidden successfully in the dark directory: " << targetFile << "\n";
    return 0;
}
