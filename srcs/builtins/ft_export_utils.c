/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasli <aasli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 12:37:38 by aasli             #+#    #+#             */
/*   Updated: 2022/05/05 16:59:58 by aasli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
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
			printf("CONCATENATION\n");
			return (1);
		}
		i++;
		printf("NOT CONCATENATION\n");
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
