#ifndef		MINISHELL_H
# define	MINISHELL_H

# include<stdio.h>
# include<stdlib.h>
# include<readline/readline.h>
# include<readline/history.h>

typedef	struct s_data
{
	int		run;
	int		exit_code;
	char	**env;
	char	**line;
}	t_data;

#endif
