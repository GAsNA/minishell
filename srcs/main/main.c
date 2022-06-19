/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasli <aasli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 08:44:48 by aasli             #+#    #+#             */
/*   Updated: 2022/06/19 13:42:33 by aasli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../headers/builtins.h"
#include "../libft/libft.h"

int	g_status = 0;

char	**get_c_nv(t_lenv **lenv)
{
	t_lenv	*tmp;
	char	**env;
	int		i;

	env = malloc(1000 * sizeof(char *));
	if (!env)
	{
		printf("Allocation error\n");
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

void	minishell(t_data *data)
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
			printf("exit\n");
			return ;
		}
		if (!data->line[0])
			continue ;
		add_history(data->line);
		cmd = parsing(get_regroup(get_lexing(data->line)), *lenv);
		if (empty_cmd(cmd) == 1)
			continue ;
		ft_loop_cmds(cmd, data);
		ft_list_clear_cmd(cmd);
		free(data->line);
	}	
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
	t_data		data;

	(void)ac;
	(void)av;
	data_init(&data, envp);
	minishell(&data);
	free_lenv(&data.env);
	if (data.hidden_path != NULL)
		free(data.hidden_path);
	return (0);
}
