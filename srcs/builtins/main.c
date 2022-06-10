/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasli <aasli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 08:44:48 by aasli             #+#    #+#             */
/*   Updated: 2022/06/10 16:08:23 by aasli            ###   ########.fr       */
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
	int		i;

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

t_lenv	*get_min_env(t_data *data)
{
	t_lenv	*lbegin;
	char	*tmp;
	char	*tmp2;

	lbegin = NULL;
	tmp = ft_calloc(2049, sizeof(char));
	if (!tmp)
	{
		printf("Allocation error");
		exit (1);
	}
	tmp2 = ft_strjoin("PWD=", getcwd(tmp, 2048));
	ft_addback_lenv(data, ft_new_lenv(tmp2));
	free (tmp2);
	ft_addback_lenv(data, ft_new_lenv("SHLVL=1"));
	tmp2 = ft_strjoin("_=", getcwd(tmp, 2048));
	free(tmp);
	tmp = ft_strjoin(tmp2, "/Minishell");
	ft_addback_lenv(data, ft_new_lenv(tmp));
	free(tmp);
	free(tmp2);
	return (data->env);
}

int	minishell(t_data *data)
{
	t_lenv	**lenv;
	t_cmd	*cmd;

	lenv = &data->env;
	data->run = 1;
	while (data->run)
	{
		handle_signals_main();
		data->line = readline("Rovidshell $>");
		if (!data->line)
		{
			data->run = 0;
			printf("exit");
			return (0);
		}
		if (!data->line[0])
			continue ;
		add_history(data->line);
		handle_signals_exec();
		cmd = parsing(get_regroup(get_lexing(data->line)), *lenv);
		ft_loop_cmds(cmd, data);
		ft_list_clear_cmd(cmd);
		free(data->line);
	}	
	return (0);
}

void	data_init(t_data *data, char **envp)
{
	data->unset_path = 0;
	data->env = NULL;
	if (!*envp)
	{
		data->env = get_min_env(data);
		data->min_env = 1;
		data->hidden_path
			= ft_strjoin("/usr/local/sbin/:",
				"/usr/local/bin/:/usr/sbin/:/usr/bin/");
	}
	else
	{
		data->env = get_env(data, envp);
		data->min_env = 0;
		data->hidden_path = NULL;
	}
	if (data->env == NULL
		|| (data->min_env == 1 && data->hidden_path == NULL))
	{
		printf("Allocation error");
		exit (1);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;

	(void)ac;
	(void)av;
	data_init(&data, envp);
	minishell(&data);
	free_lenv(&data.env);
	return (0);
}
