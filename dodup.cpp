#include <iostream>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
	if (argc < 2) {
		std::cerr << "No arguments for command " << argv[0] << "found." << std::endl;
		return 1;
	}

	int fd_out = open("out.txt", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if (fd_out < 0) {
		std::cerr << "File out.txt was not opened." << std::endl;
		return 1;
	}
	int fd_err = open("err.txt", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if (fd_err < 0) {
		std::cerr << "File err.txt was not opened." << std::endl;
		close(fd_out);
		return 1;
	}

	if (dup2(fd_out, STDOUT_FILENO) < 0) {
		std::cerr << "Failed to redirect stdout." << std::endl;
		close(fd_out);
		close(fd_err);
		return 1;
	}
	if (dup2(fd_err, STDERR_FILENO) < 0) {
		std::cerr << "Failed to redirect stderr." << std::endl;
		close(fd_out);
		close(fd_err);
		return 1;
	}
	close(fd_out);
	close(fd_err);

	execvp(argv[1], argv + 1);

	std::cerr << "Command " << argv[1] << " was not executed." << std::endl;
	return 1;

}
