/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasli <aasli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 08:44:48 by aasli             #+#    #+#             */
/*   Updated: 2022/04/21 14:34:45 by aasli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../libft/libft.h"

int	main(int ac, char **av, char **env)
{
	char	**n_env;

	(void)ac;
	av++;
	n_env = get_env(env);
	if (!n_env)
		return (1);
	ft_pwd(av, &n_env);
	ft_cd(av, &n_env);
	ft_pwd(av, &n_env);
	/*if (n_env)
	{
		int i = 0;
		char **tmp = n_env;
		while (tmp[i])
		{
			printf("%s\n", tmp[i]);
			i++;
		}
	}*/
	free_env(n_env);
	return (0);
}
