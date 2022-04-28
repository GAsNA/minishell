/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasli <aasli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 09:43:07 by aasli             #+#    #+#             */
/*   Updated: 2022/04/28 18:13:39 by aasli            ###   ########.fr       */
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
//int		ft_pwd(char **cmd, char ***env);
int		ft_pwd(char **cmd, t_lenv **env);
//int		ft_cd(char **cmd, char ***env);
int		ft_cd(char **cmd, t_lenv **env);
int		ft_echo(char **cmd, char ***env);
int		ft_env(char **cmd, char ***env);
int		ft_unset(char **cmd, char ***env);
//char	**get_env(char **env);
//char	**add_var_env(char **env, char *var);
int		add_var_env(t_lenv **env, char *var);
int		check_env_var(char **env, char *var);
//char	**rep_var_env(char **env, char *var, char *str, int n);
int		rep_var_env(t_lenv **env, char *var, char *str, int n);
char	**unset_var_env(char ***env, char *var, int n);
void	free_env(char **env);
int		check_cd_access(char **cmd);
//int		get_line(char **env, char *str, int n);
int		get_line(t_lenv **env, char *str, int n);
//int		go_home(char ***env, char *home);
int		go_home(t_lenv **env, char *home);
//int		update_env(char ***env);
int		update_env(t_lenv **env);
int		env_size(char **env);
//char	**update_pwd(char **env, char *pwd);
int		update_pwd(t_lenv **env, char *pwd);
int		update_old_pwd(t_lenv **env);
//char	**update_old_pwd(char **env);
//char	*get_var_from_env(char **env, char *str, size_t n);
char	*get_var_from_env(t_lenv **env, char *str, size_t n);
#endif
