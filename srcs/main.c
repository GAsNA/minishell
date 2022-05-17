/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasli <aasli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 09:44:11 by aasli             #+#    #+#             */
/*   Updated: 2022/05/06 23:55:32 by rleseur          ###   ########.fr       */
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

int	minishell(t_lenv *lenv)
{
	int			i;
	t_data		data;
	t_pipe		*pipe;
	t_pipe		*tmp;

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
		pipe = parsing(get_regroup(get_lexing(data.line)), lenv);
		if (!pipe)
			printf("ERROR\n");
		tmp = pipe;
		while (tmp)
		{
			i = -1;
			while (tmp->left->av[++i])
				printf("%s\t", tmp->left->av[i]);
			printf("\n");
			tmp = tmp->next;
		}
		ft_list_clear_pipe(pipe);
	}
	return (0);
}

static char	**get_k_v(char *env)
{
	int		i;
	int		j;
	char	**res;

	res = malloc(3 * sizeof(char *));
	if (!res)
		return (0);
	i = 0;
	while (env[i] != '=')
		i++;
	i += 1;
	res[0] = malloc((i + 1) * sizeof(char));
	if (!res[0])
		return (0);
	i = -1;
	while (env[++i] != '=')
		res[0][i] = env[i];
	res[0][i] = '=';
	i += 1;
	res[0][i] = '\0';
	j = 0;
	while (env[i + j])
		j++;
	res[1] = malloc((j + 1) * sizeof(char));
	if (!res[1])
		return (0);
	j = 0;
	while (env[i + j])
	{
		res[1][j] = env[i + j];
		j++;
	}
	res[1][j] = '\0';
	res[2] = 0;
	return (res);
}

static t_lenv	*get_lenv(char **env)
{
	int		i;
	char	**res;
	t_lenv	*lenv;

	lenv = NULL;
	i = -1;
	while (env[++i])
	{
		res = get_k_v(env[i]);
		ft_list_push_back_lenv(&lenv, res[0], res[1]);
		free(res);
	}
	return (lenv);
}

int	main(int ac, char **av, char **env)
{
	//int		i;
	int		exit_code;
	t_lenv	*lenv;
	//t_pipe	*pipe;
	//t_pipe	*tmp;

	(void)ac;
	(void)av;
	lenv = get_lenv(env);
	exit_code = minishell(lenv);
	/*pipe = parsing(get_regroup(get_lexing(av[1])), lenv);
	if (!pipe)
		printf("ERROR\n");
	tmp = pipe;
	while (tmp)
	{
		i = -1;
		while (tmp->left->av[++i])
			printf("%s\t", tmp->left->av[i]);
		printf("\n");
		tmp = tmp->next;
	}
	ft_list_clear_pipe(pipe);*/
	ft_list_clear_lenv(lenv);
	return (exit_code);
	//return (0);
}
