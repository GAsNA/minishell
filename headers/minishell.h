/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasli <aasli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 09:43:07 by aasli             #+#    #+#             */
/*   Updated: 2022/05/05 13:27:04 by aasli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include<stdio.h>
# include<stdlib.h>
# include<unistd.h>
# include<signal.h>
# include <dirent.h>
#include <errno.h>

enum ops
{
	PIPE,
	REDI_IN,
	REDI_OUT,
	DREDI_IN,
	DREDI_OUT
};

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

struct s_command
{
	char		**command;
	enum ops	op;
	t_command	*next;
};

struct s_lenv
{
	char		*k;
	char		*v;
	t_lenv		*next;
};

//	env linked list
t_lenv	*get_env(char **env);
t_lenv	*ft_new_lenv(char *line);
int		ft_addback_lenv(t_lenv **begin, t_lenv *new);
void	print_lenv(t_lenv **lst);
void	free_lenv(t_lenv **lst);

//	env linked list utils
int		ft_strnlen(char *str);

//	builtins
int		ft_pwd(char **cmd, t_lenv **env);
int		ft_cd(char **cmd, t_lenv **env);
int		ft_echo(char **cmd, t_lenv **env);
int		ft_exit(char **cmd, t_lenv **env);
int		ft_export(char **cmd, t_lenv **env);
int		is_bad_identifier(char c);
int		check_key(char *key);
int		c_c(char *key);
char	*get_key(char *key);
int		ft_env(char **cmd, char ***env);
int		ft_unset(char **cmd, t_lenv **env);
int		add_var_env(t_lenv **env, char *var);
int		check_env_var(t_lenv **env, char *var);
int		rep_var_env(t_lenv **env, char *var, char *str, int n);
int		con_var_env(t_lenv **env, char *var, char *str, int n);
int		unset_var_env(t_lenv **env, char *var, int n);
int		check_cd_access(char **cmd);
int		get_line(t_lenv **env, char *str, int n);
int		go_home(t_lenv **env, char *home);
int		update_env(t_lenv **env);
int		update_pwd(t_lenv **env, char *pwd);
int		update_old_pwd(t_lenv **env);
char	*get_var_from_env(t_lenv **env, char *str, size_t n);
#endif
