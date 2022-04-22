#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int	main(int ac, char **av)
{
	int		ret;
	int		fd;
	char	buff[1024];

	// Check the accessibility to a pathname
	/*
	   ret = access(av[1], F_OK);
	   if (ret == -1)
	   {
	   printf("This file doesn't exist\n");
	   return (1);
	   }
	   else
	   {
	   printf("The file exists\n");
	   return (1);
	   }
	 */
	// Open a file with given rights
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		perror("OPEN");
	else
		printf("The file is open\n");
	// Read from a file descriptor
	ret = read(fd, buff, 5);
	if (ret == -1)
		perror("READ");
	else
		printf("READ OK\n");
	// Delete a file with the unlink command
	if (unlink(av[2]) != 0)
		perror("Delete");
	else
		printf("%s has been deleted\n", av[2]);
	// Close the file descriptor
	close(fd);
	return (0);
}
