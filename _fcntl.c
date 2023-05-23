#include "shell.h"

/**
 * _fcntl - duplicate file discriptor
 * @fd: the file discriptor
 * @cmd: the new num
 *
 */
int _fcntl(int fd, int cmd, ...)
{
	int arg, result = -1;
	va_list argp;

	va_start(argp, cmd);

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
