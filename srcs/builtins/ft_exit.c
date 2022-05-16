/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasli <aasli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 10:24:43 by aasli             #+#    #+#             */
/*   Updated: 2022/05/14 12:12:38 by aasli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../headers/builtins.h"
#include "../libft/libft.h"

static int	nb_isminus(int nb)
{
	int	j;

	j = 256;
	while (nb < 0)
	{
		nb++;
		j--;
		if (j == -1)
			j = 255;
	}
	return (j);
}

static int	get_exit(char *av)
{
	int	j;
	int	nb;

	j = 0;
	nb = ft_atoi(av);
	if (nb >= 0)
	{
		while (nb > 0)
		{
			nb--;
			j++;
			if (j == 256)
				j = 0;
		}
	}
	else
		return (nb_isminus(nb));
	return (j);
}

static int	ft_isnumeric(char *av)
{
	int	i;

	i = 0;
	if (av[0] == '-' || av[0] == '+')
		i++;
	while (av[i])
	{
		if (!ft_isdigit(av[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(char **cmd, t_lenv **env)
{
	(void)env;
	if (cmd[0] && cmd[1] && cmd[2] && ft_isnumeric(cmd[1]))
	{
		printf("Exit\n");
		printf("Rovidshell: exit: too many arguments\n");
		return (1);
	}
	else if (cmd[0] && cmd[1] && !ft_isnumeric(cmd[1]))
	{
		printf("Exit\n");
		printf("Rovidshell: exit: %s: numeric argument is required\n", cmd[1]);
		exit (2);
	}
	else if (cmd[0] && cmd[1] && ft_isnumeric(cmd[1]))
	{
		printf("Exit\n");
		exit (get_exit(cmd[1]));
	}
	else
	{
		printf("Exit\n");
		exit (0);
	}
}
