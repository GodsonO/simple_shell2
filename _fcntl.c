#include "shell.h"

/**
 * _fcntl - duplicate file discriptor
 * @fd: the file discriptor
 * @cmd: the new num
 *
 */
int _fcntl(int fd, int cmd, ...)
{
	int result, arg;
	va_list argp;

	va_start(argp, cmd);


	result = -1;

	switch (cmd)
	{
		case F_DUPFD:
			{
				arg = va_arg(argp, int);
				result = _dup2(fd, arg);
				break;
			}
		case F_GETFL:
			{
				result = fcntl(fd, cmd);
				break;
			}
		default:
			errno = EINVAL;
			break;
	}

	va_end(argp);
	return (result);
}
/*
int main(void) {
    int fd = open("example.txt", O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    int newfd = _fcntl(fd, F_DUPFD, 0);  // Duplicate fd
    if (newfd == -1) {
        perror("Error in my_fcntl");
        return 1;
    }

    printf("Successfully duplicated file descriptor. New descriptor: %d\n", newfd);

    close(fd);  // Close the original file descriptor

    return 0;
}*/
