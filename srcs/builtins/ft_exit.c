/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasli <aasli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 10:24:43 by aasli             #+#    #+#             */
/*   Updated: 2022/06/21 17:02:02 by aasli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../headers/builtins.h"
#include "../libft/libft.h"
#include <limits.h>

extern int	g_status;

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

int	nb_isminus(int nb)
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

static int	get_exit_exit(char *av)
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

int	ft_is_integer(char *av)
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
	if (av[0] == '-')
		nb = ft_atoll(av + 1) - 1;
	else
		nb = ft_atoll(av + 1);
	if (len > 19 || nb > 9223372036854775807)
		return (0);
	return (len);
}

int	ft_exit(char **cmd, t_data *data, t_cmd *cmds, int fork)
{
	int		status;

	if (no_exit_in_error(cmd, fork) == 1)
	{
		g_status = 1;
		return (1);
	}
	else if (exit_in_error(cmd, data, cmds, fork) == 2)
		exit (2);
	else if (cmd[0] && cmd[1] && ft_is_integer(cmd[1]))
		status = get_exit_exit(cmd[1]);
	else
		status = 0;
	if (fork == 0)
	{
		printf("exit\n");
		free_all(data, cmds);
		exit (status);
	}
	return (status);
}
