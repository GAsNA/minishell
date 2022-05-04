/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasli <aasli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 08:44:48 by aasli             #+#    #+#             */
/*   Updated: 2022/05/04 11:22:35 by aasli            ###   ########.fr       */
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
//	ft_unset(av, &begin);
//	print_lenv(&begin);
	printf("exit return: %d",ft_exit(av, &begin));
	free_lenv(&begin);
	return (0);
}
