/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasli <aasli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 12:01:24 by aasli             #+#    #+#             */
/*   Updated: 2022/06/23 10:51:11 by rleseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <dirent.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>

typedef struct s_cmd	t_cmd;

void	ft_loop_cmds(t_cmd *cmds, t_data *data);

//	free
void	free_split(char **cmd);

//	path
char	**ft_get_paths(t_lenv **lenv);

//	env linked list
t_lenv	*get_env(t_data *data, char **env);
t_lenv	*get_min_env(t_data *data);
t_lenv	*ft_new_lenv(char *line);
int		ft_addback_lenv(t_data *data, t_lenv *new);
void	print_lenv(t_lenv **lst);
void	free_lenv(t_lenv **lst);

//	env linked list utils
int		ft_strnlen(char *str);

//	builtins
int		ft_pwd(char **cmd, t_lenv **env);
int		ft_cd(char **cmd, t_lenv **env);
int		ft_echo(char **cmd, t_lenv **env);
int		ft_exit(char **cmd, t_data *data, t_cmd *cmds, int fork);
int		exit_in_error(char **cmd, t_data *data, t_cmd *cmds, int fork);
int		no_exit_in_error(char **cmd, int fork);
int		ft_export(char **cmd, t_data *data);
int		is_bad_identifier(char c);
int		check_key(char *key);
int		c_c(char *key);
char	*get_key(char *key);
int		ft_env(char **cmd, t_lenv **env, int hidden);
int		ft_unset(char **cmd, t_lenv **env);
int		add_var_env(t_data *data, char *var);
int		check_env_var(t_lenv **env, char *var);
int		check_env_con(t_lenv **env, char *var);
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
int		nb_isminus(int nb);
int		get_exit(int nb);
int		ft_is_integer(char *av);
#endif
