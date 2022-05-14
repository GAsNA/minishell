/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasli <aasli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 08:44:48 by aasli             #+#    #+#             */
/*   Updated: 2022/05/14 11:59:23 by aasli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../libft/libft.h"

void	ctrl_c(int signum)
{
	(void)signum;
	printf("\n");
	//Need to set global_status to signum + 28
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

char	**getEnv(t_lenv **lenv)
{
	t_lenv *tmp;
	char **env = malloc(1000 * sizeof(char *));
	tmp = *lenv;
	int i = 0;
	while (tmp)
	{
		env[i] = ft_strjoin(tmp->k, tmp->v);
		i++;
		tmp = tmp->next;
	}
	env[i] = 0;
	return (env);
}

int	minishell(t_lenv **env)
{
	t_data	data;
	char	**cmd;
	t_lenv	**lenv;

	handle_signals_main();
	data.run = 1;
	lenv = env;
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
		cmd = ft_split(data.line, ' ');
		printf("---------------------------------------\n");
		if (ft_strncmp(cmd[0], "cd", ft_strlen(cmd[0])) == 0)
			ft_cd(cmd, lenv);
		else if (ft_strncmp(cmd[0], "pwd", ft_strlen(cmd[0])) == 0)
			ft_pwd(cmd, lenv);
		else if (ft_strncmp(cmd[0], "env", ft_strlen(cmd[0])) == 0)
			ft_env(cmd, lenv);
		else if (ft_strncmp(cmd[0], "unset", ft_strlen(cmd[0])) == 0)
			ft_unset(cmd, lenv);
		else if (ft_strncmp(cmd[0], "exit", ft_strlen(cmd[0])) == 0)
			ft_exit(cmd, lenv);
		else if (ft_strncmp(cmd[0], "export", ft_strlen(cmd[0])) == 0)
			ft_export(cmd, lenv);
		else if (ft_strncmp(cmd[0], "echo", ft_strlen(cmd[0])) == 0)
			ft_echo(cmd, lenv);
		else
		{
			int pid = fork();
			if (pid == 0)
			{
				char **env = getEnv(lenv);
				char **paths = ft_get_paths(lenv);
				int  i = 0;
				char *tmp;
				char *path;
				if (!env[0])
					printf("env empty\n");
				execve(cmd[0], cmd, env);
				while (paths[i])
				{
					tmp = ft_strjoin(paths[i], "/");
					path = ft_strjoin(tmp, cmd[0]);
					free(tmp);
					//printf("%s\n", path);
					execve(path, cmd, env);
					free(path);
					i++;
				}
				free_split(env);
				free_split(paths);
			}
			else
			{
				waitpid(pid, NULL, 0);
				printf("---------------------------------------\n");
			}
		}
		free_split(cmd);
		free(data.line);
	}	
	return (0);
}

int	main(int ac, char **av, char **env)
{
	int	exit_code;

	(void)ac;
	(void)av;
	t_lenv	*begin = get_env(env);
	if (!begin)
		return (1);
	exit_code = minishell(&begin);
	printf("%d\n", exit_code);
	free_lenv(&begin);
	return (exit_code);
}
