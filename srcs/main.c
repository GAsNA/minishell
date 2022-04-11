#include "../headers/minishell.h"

int	minishell(char **env)
{
	t_data data;
	
	data.run = 1;
	while (data.run)
	{
		data.line = readline("Rovidshell $>");
		if (!data.line)
		{
			data.run = 0;
			return (123);
		}
	}
	return (0);
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	int	exit_code;

	exit_code = minishell(env);
	return (exit_code);
}
