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
	char	*str;
	int		i;
	int		ret;
	int		fd;

	i = 0;

// Using readline and add_history to read lines from the stdin and add to the history of readline
/*
	while (42)
	{
		str = readline(">> ");
		add_history(str);
		printf("%s\n", str);
		i++;
	}
*/

// Get a new prompt to the next line when using CTRL-D
/*
	while (i < 1)
	{
		str = readline(">> ");
		add_history(str);
		printf("%s\n", str);
		i++;
	}
	rl_on_new_line();				//go to the next line
	rl_replace_line("", 0);			//empty the buffer and replace by the string
	rl_redisplay();					//display the last string of the command readline
*/

// Get the current directory like pwd and print it
/*
	char cdir[1024];
	getcwd(cdir, 1024);
	printf("%s\n", cdir);
*/

// Change the directory	
/*
	chdir("../");	
	getcwd(cdir, 1024);
	printf("%s\n", cdir);
*/

// get the env variable
/*
	printf("ENV V: %s\n", getenv("PATH"));
	printf("ENV V: %s\n", getenv("LOGNAME"));
*/
	return (0);
}
