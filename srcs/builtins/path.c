/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasli <aasli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 09:59:45 by aasli             #+#    #+#             */
/*   Updated: 2022/05/30 14:07:14 by aasli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../headers/builtins.h"
#include "../libft/libft.h"

char	**ft_get_paths(t_lenv **env)
{
	char	*tmp;
	char	**tmp2;
	t_lenv	*tmp3;

	tmp3 = *env;
	if (!tmp3)
		return (NULL);
	while (tmp3)
	{
		if (ft_strncmp("PATH=", tmp3->k, 5) == 0)
		{
			tmp = ft_strdup(tmp3->v);
			break ;
		}
		tmp = NULL;
		tmp3 = tmp3->next;
	}
	if (tmp == NULL)
		return (NULL);
	tmp2 = ft_split(tmp, ':');
	return (tmp2);
}
