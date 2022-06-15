/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasli <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 13:56:36 by aasli             #+#    #+#             */
/*   Updated: 2022/06/14 14:00:16 by aasli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../headers/builtins.h"
#include "../libft/libft.h"

int	get_exit(int nb)
{
	int	j;

	j = 0;
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
