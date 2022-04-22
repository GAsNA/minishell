#include <stdio.h>
#include <dirent.h>

int	main(int ac, char **av)
{
	DIR				*folder;
	struct dirent	*entry;

	folder = opendir("dir");
	if (folder == NULL)
	{
		perror("Unable to read directory");
		return (1);
	}
	while (entry = readdir(folder))
		printf("File: %s\n", entry->d_name);
	closedir(folder);
	return (0);
}
