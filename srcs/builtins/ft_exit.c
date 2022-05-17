/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasli <aasli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 10:24:43 by aasli             #+#    #+#             */
/*   Updated: 2022/05/17 14:32:46 by aasli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../headers/builtins.h"
#include "../libft/libft.h"
#include <limits.h>

static long long int	ft_atoll(const char *nptr)
{
	int				i;
	int				s;
	long long int	res;

	i = 0;
	s = 1;
	res = 0;
	while (nptr[i] == ' ' || nptr[i] == '\n'
		||nptr[i] == '\t' || nptr[i] == '\f'
		||nptr[i] == '\v' || nptr[i] == '\r')
	{
		i++;
	}
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			s *= -1;
		i++;
	}
	while (nptr[i] != '\0' && nptr[i] >= '0' && nptr[i] <= '9')
	{
		res = res * 10 + (nptr[i] - 48);
		i++;
	}
	return (res * s);
}

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

static int	ft_is_integer(char *av)
{
	int						i;
	int						len;
	unsigned long long int	nb;

	i = 0;
	len = 0;
	if (av[0] == '-' || av[0] == '+')
		i++;
	while (av[i])
	{
		if (!ft_isdigit(av[i]))
			return (0);
		i++;
		len++;
	}
	nb = ft_atoll(av);
	if (len > 19 || nb > 9223372036854775807)
		return (0);
	return (len);
}

int	ft_exit(char **cmd, t_lenv **env)
{
	(void)env;
	if (cmd[0] && cmd[1] && cmd[2] && ft_is_integer(cmd[1]))
	{
		printf("Exit\n");
		printf("Rovidshell: exit: too many arguments\n");
		return (1);
	}
	else if (cmd[0] && cmd[1] && !ft_is_integer(cmd[1]))
	{
		printf("Exit\n");
		printf("Rovidshell: exit: %s: numeric argument is required\n", cmd[1]);
		exit (2);
	}
	else if (cmd[0] && cmd[1] && ft_is_integer(cmd[1]))
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
