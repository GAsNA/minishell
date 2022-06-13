/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasli <aasli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 12:37:38 by aasli             #+#    #+#             */
/*   Updated: 2022/06/10 17:30:30 by aasli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../headers/builtins.h"
#include "../libft/libft.h"

int	check_key(char *key)
{
	int	i;

	i = 0;
	while (key[i])
	{
		if (key[i] == '=')
			break ;
		i++;
	}
	if (i >= (int)ft_strlen(key))
		return (-1);
	return (i);
}

int	c_c(char *key)
{
	int	i;

	i = 0;
	while (key[i])
	{
		if (key[i] == '=' && key[i - 1] == '+')
		{
			return (1);
		}
		i++;
	}
	return (0);
}

char	*get_key(char *key)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	while (key[i])
	{
		if (key[i] == '=')
			break ;
		i++;
	}
	if (i >= (int)ft_strlen(key))
		return (NULL);
	tmp = ft_substr(key, 0, i + 1);
	if (!tmp)
		return (NULL);
	return (tmp);
}
