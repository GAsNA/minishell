#include <stdio.h>
#include <fcntl.h>           /* Definition of AT_* constants */
#include <sys/stat.h>

int	main(int ac, char **av)
{
	struct stat	statusfile; // TW Do not declare pointer to
							// struct or allocate dynamically
	if (stat(av[1], &statusfile) == -1)
	{
		perror("Error");
		return (0);
	}
	printf("size of file = %li\n", statusfile.st_size);
	return (0);
}
