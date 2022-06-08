/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasli <aasli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 12:40:37 by aasli             #+#    #+#             */
/*   Updated: 2022/06/08 12:01:44 by rleseur          ###   ########.fr       */
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
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# include "parsing.h"
# include "../srcs/libft/libft.h"

/*enum ops
{
	PIPE,
	REDI_IN,
	REDI_OUT,
	DREDI_IN,
	DREDI_OUT
};*/

typedef struct s_data		t_data;
typedef struct s_command	t_command;
typedef struct s_lenv		t_lenv;

struct s_data
{
	int		run;
	int		exit_code;
	char	**env;
	char	*line;
};

/*struct s_command
{
	char		**command;
	enum ops	op;
	t_command	*next;
};*/

struct s_lenv
{
	char		*k;
	char		*v;
	t_lenv		*next;
};

#endif
