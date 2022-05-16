/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_env_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasli <aasli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 14:58:26 by aasli             #+#    #+#             */
/*   Updated: 2022/05/14 12:16:20 by aasli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../headers/builtins.h"
#include "../libft/libft.h"

void	print_lenv(t_lenv **lst)
{
	t_lenv	*tmp;

	tmp = *lst;
	while (tmp)
	{
		printf("%s%s\n", tmp->k, tmp->v);
		tmp = tmp->next;
	}
}

void	free_lenv(t_lenv **lst)
{
	t_lenv	*tmp;
	t_lenv	*tmp2;

	tmp = *lst;
	while (tmp)
	{
		tmp2 = tmp;
		free(tmp->k);
		free(tmp->v);
		tmp = tmp->next;
		free(tmp2);
	}
}

int	ft_strnlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '=')
		i++;
	return (i);
}
