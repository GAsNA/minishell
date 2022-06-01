/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleseur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 16:15:15 by rleseur           #+#    #+#             */
/*   Updated: 2022/06/01 13:31:05 by rleseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

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
typedef struct s_lenv		t_lenv;
typedef struct s_cmd		t_cmd;

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
	char		**cmd;
	int		fd_in;
	int		fd_out;
	int		pipe_fd[2];
	pid_t		pid;// NULL
	struct s_cmd	*prev;
	struct s_cmd	*next;
};

struct s_lenv
{
	char	*k;
	char	*v;
	t_lenv	*next;
};

/********************************************/
/*		  Protoypes		    */
/********************************************/

/* lexing.c */
t_lexing	*get_lexing(char *line);

/* regroup */
t_regroup	*get_regroup(t_lexing *lex);

/* parsing.c */
t_cmd		*parsing(t_regroup *reg, t_lenv *lenv);

/* expand.c */
t_cmd		*get_expands(t_cmd *cmd, t_lenv *lenv);

/* heredoc.c */
int		make_heredoc(void);

/* manage_lists_lexing.c */
t_lexing	*ft_create_elem_lex(char letter, enum e_type type);
void		ft_list_push_back_lex(t_lexing **begin_list,
				char letter, enum e_type type);
void		ft_list_clear_lex(t_lexing *begin_list);

/* manage_lists_regroup.c */
t_regroup	*ft_create_elem_reg(char *str);
void		ft_list_push_back_reg(t_regroup **begin_list, char *str);
void		ft_list_clear_reg(t_regroup *begin_list);

/* manage_lists_cmd.c */
t_cmd		*ft_create_elem_cmd(char **av, int fd_in);
void		ft_list_push_back_cmd(t_cmd **begin_list, char **av, int fd_in);

/* manage_lists_lenv.c */
t_lenv		*ft_create_elem_lenv(char *k, char *v);
void		ft_list_push_back_lenv(t_lenv **begin_list, char *k, char *v);
void		ft_list_clear_lenv(t_lenv *begin_list);

#endif
