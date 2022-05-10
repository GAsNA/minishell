/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasli <aasli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 09:59:45 by aasli             #+#    #+#             */
/*   Updated: 2022/05/10 12:46:57 by aasli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../libft/libft.h"

char	**ft_get_paths(t_lenv **env)
{
	char	*path;
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
	path = ft_substr(tmp, 5, ft_strlen(tmp));
	free(tmp);
	tmp2 = ft_split(path, ':');
	free(path);
	return (tmp2);
}
