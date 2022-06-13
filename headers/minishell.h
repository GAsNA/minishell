/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasli <aasli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 12:40:37 by aasli             #+#    #+#             */
/*   Updated: 2022/06/13 08:49:42 by aasli            ###   ########.fr       */
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
# include "garbage.h"
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
typedef struct s_glist		t_glist;

struct s_data
{
	int		run;
	t_lenv	*env;
	int		min_env;
	int		unset_path;
	t_glist	*glist;
	char	*line;
	char	*hidden_path;
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

//	Signals functions
void	ctrl_c_exec(int signum);
void	ctrl_c(int signum);
void	handle_signals_exec(void);
void	handle_signals_main(void);

//	Free functions
void	free_split(char **cmd);
#endif
