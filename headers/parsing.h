/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleseur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 16:15:15 by rleseur           #+#    #+#             */
/*   Updated: 2022/06/22 10:26:01 by rleseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

# include <errno.h>

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

typedef struct s_lexing		t_lexing;
typedef struct s_regroup	t_regroup;
typedef struct s_cmd		t_cmd;
typedef struct s_lenv		t_lenv;

struct s_lexing
{
	char		letter;
	enum e_type	type;
	t_lexing	*next;
};

struct s_regroup
{
	char		*str;
	t_regroup	*next;
};

struct s_cmd
{
	char			**cmd;
	int				fd_in;
	int				fd_out;
	int				to_free;
	int				pipe_fd[2];
	pid_t			pid;
	struct s_cmd	*prev;
	struct s_cmd	*next;
};

/********************************************/
/*				  Protoypes					*/
/********************************************/

/* checks_before_all.c */
int			is_quotes_close(char *line);
int			has_no_double_pipe(char *line);
int			has_no_multiple_redir(char *line);

/* lexing.c */
t_lexing	*get_lexing(char *line);

/* regroup */
t_regroup	*get_regroup(t_lexing *lex);

/* parsing.c */
t_cmd		*parsing(t_regroup *reg, t_lenv *lenv);

/* parsing_utils.c */
int			check_status(t_regroup *reg, t_cmd *cmd);
t_regroup	*free_and_pass(t_regroup *reg, int redir);
t_regroup	*make_redir(t_regroup *reg, int *fd_in, int *fd_out,
				int *to_free);

/* last_splits.c */
t_cmd		*last_splits(t_cmd *cmd);

/* last_quotes.c */
t_cmd		*supp_useless_quotes(t_cmd *cmd);

/* calcul_divide_cmd.c */
int			calcul_av(t_regroup *reg);
t_regroup	*divide_cmd(t_regroup *reg, char ***av, int *fd, t_lenv *lenv);

/* get_check_fd.c */
void		check_fd_out(int *fd_in, int *fd_out, t_regroup *reg, int *to_free);
void		check_fd_in(int *fd_in, int *fd_out, t_regroup *reg, int *to_free);

/* expand.c */
char		*make_expand(char *str, int n, t_lenv *lenv, int inte);
t_cmd		*get_expands(t_cmd *cmd, t_lenv *lenv);

/* expand_utils.c */
int			is_valid_iden(char c);
int			there_are_expand(char *av);
int			get_k_n(char *line, int *i, int *inte);

/* heredoc.c */
int			make_heredoc(char *s, t_lenv *lenv);

/* manage_lists_lexing.c */
t_lexing	*ft_create_elem_lex(char letter, enum e_type type);
void		ft_list_push_back_lex(t_lexing **begin_list,
				char letter, enum e_type type);
void		ft_list_clear_lex(t_lexing *begin_list);

/* manage_lists_regroup.c */
t_regroup	*ft_create_elem_reg(char *str);
void		ft_list_push_back_reg(t_regroup **begin_list, char *str);
void		ft_list_clear_reg(t_regroup *begin_list, int clear_str);

/* manage_lists_cmd.c */
t_cmd		*ft_create_elem_cmd(char **av, int fd_in);
void		ft_list_push_back_cmd(t_cmd **begin_list, char **av, int fd_in);
void		ft_list_clear_cmd(t_cmd *begin_list);

/* manage_lists_lenv.c */
t_lenv		*ft_create_elem_lenv(char *k, char *v);
void		ft_list_push_back_lenv(t_lenv **begin_list, char *k, char *v);
void		ft_list_clear_lenv(t_lenv *begin_list);

/* print_error.c */
int			error_syntax(char c);

#endif
