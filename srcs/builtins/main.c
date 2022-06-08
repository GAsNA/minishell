/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasli <aasli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 08:44:48 by aasli             #+#    #+#             */
/*   Updated: 2022/06/08 10:44:31 by aasli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../headers/builtins.h"
#include "../libft/libft.h"

int	g_status = 0;

void	ctrl_c_exec(int signum)
{
	(void)signum;
	printf("\n");
	g_status = signum + 28;
}

void	handle_signals_exec(void)
{
	signal(SIGINT, ctrl_c_exec);
	signal(SIGQUIT, SIG_IGN);
}


void	ctrl_c(int signum)
{
	(void)signum;
	printf("\n");
	g_status = signum + 28;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_signals_main(void)
{
	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, SIG_IGN);
}

void	free_split(char **cmd)
{
	int		i;

	i = 0;
	while (cmd[i])
		free(cmd[i++]);
	free(cmd);
}

int	print_cmd(char **cmd)
{
	int		i;

	i = 0;
	while (cmd[i])
		printf("%s ", cmd[i++]);
	printf("\n");
	return (0);
}

char	**get_c_nv(t_lenv **lenv)
{
	t_lenv	*tmp;
	char	**env;
	int i;
	
	env = malloc(1000 * sizeof(char *));
	if (!env)
	{
		printf("Allocation error");
		return (NULL);
	}
	tmp = *lenv;
	i = 0;
	while (tmp)
	{
		env[i] = ft_strjoin(tmp->k, tmp->v);
		i++;
		tmp = tmp->next;
	}
	env[i] = 0;
	return (env);
}

t_lenv	*get_min_env(void)
{
	t_lenv	*lbegin;
	char	*pwd;
	char	*tmp;
	char	*tmp2;

	lbegin = NULL;
	tmp = ft_calloc(2049, sizeof(char));
	if (!tmp)
	{
		printf("Allocation error");
		return (0);
	}
	pwd = ft_strjoin("PWD=", getcwd(tmp, 2048));
	ft_addback_lenv(&lbegin, ft_new_lenv(pwd));
	free (pwd);
	ft_addback_lenv(&lbegin, ft_new_lenv("SHLVL=1"));
	tmp2 = ft_strjoin("_=", getcwd(tmp, 2048));
	free(tmp);
	tmp = ft_strjoin(tmp2, "/Minishell");
	ft_addback_lenv(&lbegin, ft_new_lenv(tmp));
	free(tmp);
	free(tmp2);
	return (lbegin);
}

int	minishell(t_lenv **env)
{
	t_data	data;
	//char	**cmd;
	t_lenv	**lenv;

	lenv = env;
	data.run = 1;
	while (data.run)
	{
		handle_signals_main();
		data.line = readline("Rovidshell $>");
		if (!data.line)
		{
			data.run = 0;
			printf("exit\n");
			return (0);
		}
		if (data.line[0])
			add_history(data.line);
		t_cmd cmd;
		cmd.cmd = malloc(sizeof(char *) * 2);
		cmd.cmd[0] = ft_strdup("wc");
		cmd.cmd[1] = 0;
		cmd.fd_out = open("test", O_CREAT | O_WRONLY | O_TRUNC, 0644);
		//cmd.fd_out = -1;
		if (cmd.fd_out < 0)
			printf("error fd\n");
		cmd.fd_in = -1;
//		cmd.next = NULL;
		t_cmd cmd2;
		cmd2.cmd = malloc(sizeof(char *) * 2);
		cmd2.cmd[0] = ft_strdup("wc");
		cmd2.cmd[1] = 0;
		cmd2.fd_out = -1;
		cmd2.fd_in = -1;
		cmd.next = &cmd2;
		cmd2.next = NULL;
		cmd2.prev = &cmd;
/*		t_cmd cmd3;
		cmd3.cmd = malloc(sizeof(char *) * 2);
		cmd3.cmd[0] = ft_strdup("/usr/bin/ls");
		cmd3.cmd[1] = 0;
		cmd3.fd_out = -1;
		cmd3.fd_in = -1;
		cmd2.next = &cmd3;
		cmd3.next = NULL;*/
//		char **enve = get_c_nv(lenv);
		handle_signals_exec();
		ft_loop_cmds(&cmd, lenv);/*
		free(cmd.cmd[0]);
		free(cmd2.cmd[0]);
		free(cmd3.cmd[0]);
		free(cmd.cmd);
		free(cmd2.cmd);
		free(cmd3.cmd);*/
//		free_split(enve);
//		free_split(cmd);
		free(data.line);
	}	
	return (0);
}

int	main(int ac, char **av, char **env)
{
	int		exit_code;
	t_lenv	*begin;

	(void)ac;
	(void)av;
	if (!*env)
		begin = get_min_env();
	else
		begin = get_env(env);
	if (!begin)
		return (1);
	exit_code = minishell(&begin);
	free_lenv(&begin);
	return (exit_code);
}
