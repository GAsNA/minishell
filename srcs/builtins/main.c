/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasli <aasli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 08:44:48 by aasli             #+#    #+#             */
/*   Updated: 2022/04/27 17:19:16 by aasli            ###   ########.fr       */
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
//	ft_pwd(av, &n_env);
//	ft_cd(av, &n_env);
//	ft_pwd(av, &n_env);
	/*if (n_env)
	{
		int i = 0;
		char **tmp = n_env;
		while (tmp[i])
		{
			printf("%s\n", tmp[i]);
			i++;
		}
	}
	ft_echo(av, &env);*/
	ft_unset(av, &n_env);
/*	char **avenv = malloc(2 * sizeof(char *));
	avenv[0] = ft_strdup("env");
	avenv[1] = 0;
	ft_env(avenv, &n_env);*/
	free_env(n_env);
//	free_env(avenv);
	return (0);
}
