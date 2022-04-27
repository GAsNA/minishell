/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasli <aasli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 09:43:07 by aasli             #+#    #+#             */
/*   Updated: 2022/04/26 17:02:37 by aasli            ###   ########.fr       */
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

int		ft_pwd(char **cmd, char ***env);
int		ft_cd(char **cmd, char ***env);
int		ft_echo(char **cmd, char ***env);
int		ft_env(char **cmd, char ***env);
int		ft_unset(char **cmd, char ***env);
char	**get_env(char **env);
char	**add_var_env(char **env, char *var);
int		check_env_var(char **env, char *var);
char	**rep_var_env(char **env, char *var, char *str, int n);
char	**unset_var_env(char ***env, char *var, int n);
void	free_env(char **env);
int		check_cd_access(char **cmd);
int		get_line(char **env, char *str, int n);
int		go_home(char ***env, char *home);
int		update_env(char ***env);
int		env_size(char **env);
char	**update_pwd(char **env, char *pwd);
char	**update_old_pwd(char **env);
char	*get_var_from_env(char **env, char *str, size_t n);
#endif
