/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasli <aasli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 08:27:53 by aasli             #+#    #+#             */
/*   Updated: 2022/06/18 14:09:46 by aasli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../headers/builtins.h"
#include "../libft/libft.h"

extern int	g_status;

void	ctrl_back_slash(int signum)
{
	(void)signum;
	printf("Quit (core dumped)\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	g_status = 131;
}

void	ctrl_c_exec(int signum)
{
	(void)signum;
	printf("\n");
	g_status = 130;
}

void	handle_signals_exec(t_data *data)
{
	(void)data;
	signal(SIGINT, ctrl_c_exec);
	signal(SIGQUIT, ctrl_back_slash);
}

void	ctrl_c(int signum)
{
	(void)signum;
	printf("\n");
	g_status = 130;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_signals_main(void)
{
	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, SIG_IGN);
}
