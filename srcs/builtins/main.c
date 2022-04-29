/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasli <aasli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 08:44:48 by aasli             #+#    #+#             */
/*   Updated: 2022/04/29 14:59:30 by aasli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../libft/libft.h"

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;

// Test env linked list
	
	t_lenv	*begin = get_env(env);
	if (!begin)
		return (1);
	av++;
//	print_lenv(&begin);
	printf ("---------------------------------------------------\n");
/*	ft_pwd(av, &begin);
	ft_cd(av, &begin);
	ft_pwd(av, &begin);
*/	
//	print_lenv(&begin);
	printf ("---------------------------------------------------\n");

//	ft_echo(av, &env);
	ft_unset(av, &begin);
	print_lenv(&begin);
/*	char **avenv = malloc(2 * sizeof(char *));
	avenv[0] = ft_strdup("env");
	avenv[1] = 0;
	ft_env(avenv, &n_env);*/
//	free_env(n_env);
//	free_env(avenv);
	free_lenv(&begin);
	return (0);
}
