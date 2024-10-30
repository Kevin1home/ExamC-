#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>

const char XOR_KEY = 0xFF;

const size_t MAGIC_LENGTH = 16;

void xorMagicBytes(const std::string& filename, bool addExtension) {
    std::fstream file(filename, std::ios::binary | std::ios::in | std::ios::out);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + filename);
    }

    char magicBytes[MAGIC_LENGTH];
    file.read(magicBytes, MAGIC_LENGTH);

    if (file.gcount() < MAGIC_LENGTH) {
        throw std::runtime_error("File is smaller than MAGIC_LENGTH: " + filename);
    }

    for (size_t i = 0; i < MAGIC_LENGTH; ++i) {
        magicBytes[i] ^= XOR_KEY;
    }

    file.seekp(0);
    if (!file.write(magicBytes, MAGIC_LENGTH)) {
        throw std::runtime_error("Failed to write to file: " + filename);
    }

    if (addExtension) {
        std::string newFilename = filename + ".hide";
        std::rename(filename.c_str(), newFilename.c_str());
        std::cout << "File distorted and renamed to: " << newFilename << std::endl;
    }
    else {
        std::string originalFilename = filename.substr(0, filename.size() - 5);
        std::rename(filename.c_str(), originalFilename.c_str());
        std::cout << "File restored and renamed to: " << originalFilename << std::endl;
    }
}

bool hasHideExtension(const std::string& filename) {
    return filename.size() > 5 && filename.substr(filename.size() - 5) == ".hide";
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <mode> <filename>" << std::endl;
        std::cerr << "Modes:\n  distort - to distort the file\n  restore - to restore the file" << std::endl;
        return 1;
    }

    std::string mode = argv[1];
    std::string filename = argv[2];

    try {
        if (mode == "distort") {
            if (hasHideExtension(filename)) {
                std::cerr << "Error: File already has .hide extension: " << filename << std::endl;
                return 1;
            }
            xorMagicBytes(filename, true);
        }
        else if (mode == "restore") {
            if (!hasHideExtension(filename)) {
                std::cerr << "Error: File does not have .hide extension: " << filename << std::endl;
                return 1;
            }
            xorMagicBytes(filename, false);
        }
        else {
            std::cerr << "Error: Unknown mode " << mode << std::endl;
            return 1;
        }
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
