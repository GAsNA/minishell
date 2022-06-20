/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasli <aasli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 12:40:37 by aasli             #+#    #+#             */
/*   Updated: 2022/06/20 14:41:44 by aasli            ###   ########.fr       */
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


//	Main
int	empty_cmd(t_cmd *cmd);

//	Env
char	**get_c_nv(t_lenv **lenv);

//	Signals functions
void	ctrl_c_exec(int signum);
void	ctrl_c(int signum);
void	handle_signals_exec(t_data *data);
void	handle_signals_main(void);
void	reset_signals(t_data *data);

//	Free functions
void	free_split(char **cmd);
void	free_all(t_data *data, t_cmd *cmd);

//	Exec

void	close_parent_fds(t_cmd *cmd);
void	ft_close(void);
int		ft_prepare_child(t_cmd *tmp);
int		no_fork_allowed(char **cmd);
int		ft_exec_child(t_cmd *cmds, t_cmd *cmd, t_data *data);
void	wait_childs(t_cmd *cmd);
int		launch_builtin(t_cmd *cmd, t_data *data);

//	Exec utils
char	*try_access_path(char *cmd, char **paths, int i);
char	*get_exec_path(char *cmd, t_data *data);
int		is_builtin(char **cmd);



#endif
