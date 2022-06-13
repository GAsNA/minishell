/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasli <aasli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 08:27:53 by aasli             #+#    #+#             */
/*   Updated: 2022/06/13 08:54:50 by aasli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../headers/builtins.h"
#include "../libft/libft.h"

extern int	g_status;

void	ctrl_c_exec(int signum)
{
	(void)signum;
	printf("\n");
	g_status = signum + 28;
}

void	handle_signals_exec(void)
{
	signal(SIGINT, ctrl_c_exec);
	signal(SIGQUIT, SIG_IGN);
}

void	ctrl_c(int signum)
{
	(void)signum;
	printf("\n");
	g_status = signum + 28;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_signals_main(void)
{
	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, SIG_IGN);
}
