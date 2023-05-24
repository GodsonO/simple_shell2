#include "shell.h"

/**
 * _dup2 - duplicate file discriptor to
 * new file discriptor
 * @oldfd: old
 *
 */
int _dup2(int oldfd, int newfd)
{
	int result;

	if (oldfd == newfd)
	{
		return (newfd);
	}
	close(newfd);

	result = _fcntl(oldfd, F_DUPFD, newfd);
	if (result == -1)
	{
		perror("Error in fcntl");
		return (-1);
	}
	return (result);
}
/*
int main() {
    int fd = open("example.txt", O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    int newfd = _dup2(fd, 100);  // Duplicate fd to newfd (100 in this example)
    if (newfd == -1) {
        perror("Error in my_dup2");
        return 1;
    }

    printf("Successfully duplicated file descriptor. New descriptor: %d\n", newfd);

    close(fd);  // Close the original file descriptor

    return 0;
}*/
