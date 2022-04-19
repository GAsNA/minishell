/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasli <aasli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 08:44:48 by aasli             #+#    #+#             */
/*   Updated: 2022/04/18 21:11:20 by aasli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../libft/libft.h"

int	main(int ac, char **av, char **env)
{
	char **n_env;

	(void)ac;
	av++;
	n_env = get_env(env);
	if (!n_env)
		return (1);
	ft_pwd(av);
	ft_cd(av, n_env);
	ft_pwd(av);
	if (n_env)
		printf("No more\n");
	else
		printf("Still more\n");
	return (0);
}
