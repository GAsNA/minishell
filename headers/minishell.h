/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasli <aasli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 09:43:07 by aasli             #+#    #+#             */
/*   Updated: 2022/04/15 16:41:30 by rleseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

enum e_ops
{
	PIPE,
	REDI_IN,
	REDI_OUT,
	DREDI_IN,
	DREDI_OUT
};

typedef struct s_data		t_data;
typedef struct s_command	t_command;

struct s_data
{
	int		run;
	int		exit_code;
	char	**env;
	char	*line;
};

struct s_command
{
	char		**command;
	t_command	*next;
};

/********************************************/
/*	  			   Protoypes				*/
/********************************************/

/* parsing.c */
char	**get_commands(char *line);

#endif
