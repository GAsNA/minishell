/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasli <aasli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 09:44:11 by aasli             #+#    #+#             */
/*   Updated: 2022/04/27 14:48:22 by rleseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ctrl_c(int signum)
{
	(void)signum;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_signals_main(void)
{
	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, SIG_IGN);
}

int	minishell(char **env)
{
	t_data		data;
	t_pipe		*pipe;
	t_pipe		*tmp;

	(void)env;
	handle_signals_main();
	data.run = 1;
	while (data.run)
	{
		data.line = readline("Rovidshell $>");
		if (!data.line)
		{
			data.run = 0;
			printf("exit\n");
			return (0);
		}
		if (data.line[0])
			add_history(data.line);
		pipe = parsing(get_regroup(get_lexing(data.line)));
		if (!pipe)
			return (1);
		tmp = pipe;
		while (tmp)
		{
			while (tmp->left->redir)
			{
				printf("%s\t%i\n", tmp->left->redir->val,
					tmp->left->redir->type);
				tmp->left->redir = tmp->left->redir->next;
			}
			printf("\n");
			tmp = tmp->next;
		}
		ft_list_clear_pipe(pipe);
	}
	return (0);
}

int	main(int ac, char **av, char **env)
{
	int	exit_code;

	(void)ac;
	(void)av;
	exit_code = minishell(env);
	return (exit_code);
}
