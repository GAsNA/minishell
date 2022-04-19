/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasli <aasli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 09:43:07 by aasli             #+#    #+#             */
/*   Updated: 2022/04/19 12:13:58 by rleseur          ###   ########.fr       */
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

enum e_type
{
	LITERAL,
	SPACE_,
	OUTREDIR,
	INREDIR,
	PIPE,
	SIMPLEQUOTE,
	DOUBLEQUOTE
};

typedef struct s_data		t_data;
typedef struct s_lexing		t_lexing;

struct s_data
{
	int		run;
	int		exit_code;
	char	**env;
	char	*line;
};

struct s_lexing
{
	char		letter;
	enum e_type	type;
	t_lexing	*next;
};

/********************************************/
/*	  			   Protoypes				*/
/********************************************/

/* parsing.c */
t_lexing	*get_lexing(char *line);

#endif
