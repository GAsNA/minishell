/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasli <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 10:11:36 by aasli             #+#    #+#             */
/*   Updated: 2022/06/14 13:58:06 by aasli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../headers/builtins.h"
#include "../libft/libft.h"

extern int g_status;

static int	full_n(char *cmd)
{
	int	i;

	cmd += 2;
	i = 0;
	while (cmd[i])
	{
		if (cmd[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

static int	check_echo(char **cmd)
{
	int	i;
	int	n;

	i = 1;
	n = 0;
	while (cmd[i])
	{
		if (ft_strncmp(cmd[i], "-n", 2) != 0)
			return (n);
		if (ft_strncmp(cmd[i], "-n", 2) == 0
			&& full_n(cmd[i]))
			n++;
		i++;
	}
	return (n);
}

static void	print_echo(char **cmd, int n)
{
	int	i;
	char *status;

	i = 1;
	status = NULL;
	while (cmd[i + n] != NULL)
	{
		if (i != 1)
			write(1, " ", 1);
		if (ft_strncmp(cmd[i + n], "$?", 2) == 0)
		{
			printf("gstatus = %i\n", g_status);
			g_status = get_exit(g_status);
			status = ft_itoa(g_status);
			write(1, status, ft_strlen(status));
			if (cmd[i + n] + 2 != NULL)	
				write(1, cmd[i + n] + 2, ft_strlen(cmd[i + n] + 2));
			free(status);
		}
		else
			write(1, cmd[i + n], ft_strlen(cmd[i + n]));
		i++;
	}
}

int	ft_echo(char **cmd, t_lenv **env)
{
	int		n;

	(void)env;
	n = check_echo(cmd);
	print_echo(cmd, n);
	if (n == 0)
		write(1, "\n", 1);
	g_status = 0;
	return (0);
}
