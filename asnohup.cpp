#include <cstring>
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <command> [args...]\n";
        return 1;
    }

    pid_t pid = fork();
    if (pid < 0) {
        std::cerr << "Fork failed: " << std::strerror(errno) << "\n";
        return 1;
    }

    if (pid > 0) {
        std::cout << "Started process " << pid << " in the background.\n";
        return 0;
    }

    if (setsid() < 0) {
        std::cerr << "Failed to create new session: " << std::strerror(errno) << "\n";
        return 1;
    }

    int dev_null = open("/dev/null", O_RDWR);
    if (dev_null < 0) {
        std::cerr << "Failed to open /dev/null: " << std::strerror(errno) << "\n";
        return 1;
    }

    if (dup2(dev_null, STDIN_FILENO) < 0 ||  
        dup2(dev_null, STDOUT_FILENO) < 0 || 
        dup2(dev_null, STDERR_FILENO) < 0) {
        std::cerr << "Failed to redirect IO to /dev/null: " << std::strerror(errno) << "\n";
        close(dev_null);
        return 1;
    }
    close(dev_null);

    execvp(argv[1], argv + 1);

    std::cerr << "Failed to start " << argv[1] << ": " << std::strerror(errno) << "\n";
    return 1;

}
