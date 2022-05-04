/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasli <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 10:11:36 by aasli             #+#    #+#             */
/*   Updated: 2022/05/04 10:33:37 by aasli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../libft/libft.h"

static int	check_echo(char **cmd)
{
	int	i;
	int	n;

	i = 1;
	n = 0;
	while (cmd[i])
	{
		if (ft_strncmp(cmd[i], "-n", 3) == 0)
			n++;
		i++;
	}
	return (n);
}

static void	print_echo(char **cmd, int n)
{
	int	i;

	i = 1;
	while (cmd[i + n])
	{
		if (i != 1)
			printf(" ");
		printf("%s", cmd[i + n]);
		i++;
	}
}

int	ft_echo(char **cmd, t_lenv **env)
{
	int		n;

	printf("ECHOYAGE\n");
	(void)env;
	n = check_echo(cmd);
	print_echo(cmd, n);
	if (n == 0)
		printf("\n");
	return (0);
}
