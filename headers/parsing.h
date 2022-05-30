/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleseur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 16:15:15 by rleseur           #+#    #+#             */
/*   Updated: 2022/05/30 14:00:34 by rleseur          ###   ########.fr       */
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
typedef struct s_pipe		t_pipe;
typedef struct s_cmd		t_cmd;
typedef struct s_redir		t_redir;
typedef struct s_lenv		t_lenv;
typedef struct s_cmd2		t_cmd2;

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

struct s_pipe
{
	t_cmd	*left;
	t_cmd	*right;
	t_pipe	*next;
};

struct s_cmd2
{
	char		**cmd;
	int		fd_in;
	int		fd_out;
	int		pipe_fd[2];
	pid_t		pid;// NULL
	struct s_cmd2	*prev;
	struct s_cmd2	*next;
};

struct s_cmd
{
	char	**av;
	t_redir	*redir;
};

struct s_redir
{
	char		*val;
	enum e_type	type;
	t_redir		*next;
};

struct s_lenv
{
	char	*k;
	char	*v;
	t_lenv	*next;
};

/********************************************/
/*	  			   Protoypes				*/
/********************************************/

/* lexing.c */
t_lexing	*get_lexing(char *line);

/* regroup */
t_regroup	*get_regroup(t_lexing *lex);

/* parsing.c */
t_cmd2		*parsing(t_regroup *reg, t_lenv *lenv);

/* expand.c */
t_pipe		*get_expands(t_pipe *pipe, t_lenv *lenv);

/* manage_lists_lexing.c */
t_lexing	*ft_create_elem_lex(char letter, enum e_type type);
void		ft_list_push_back_lex(t_lexing **begin_list,
				char letter, enum e_type type);
void		ft_list_clear_lex(t_lexing *begin_list);

/* manage_lists_regroup.c */
t_regroup	*ft_create_elem_reg(char *str);
void		ft_list_push_back_reg(t_regroup **begin_list, char *str);
void		ft_list_clear_reg(t_regroup *begin_list);

/* manage_lists_pipe.c */
t_pipe		*ft_create_elem_pipe(char **av);
void		ft_list_push_back_pipe(t_pipe **begin_list, char **av);
void		ft_list_clear_pipe(t_pipe *begin_list);

/* manage_lists_cmd2.c */
t_cmd2		*ft_create_elem_cmd2(char **av, int fd_out);
void		ft_list_push_back_cmd2(t_cmd2 **begin_list, char **av, int fd_out);

/* manage_lists_redir.c */
t_redir		*ft_create_elem_redir(char *str, enum e_type type);
void		ft_list_push_back_redir(t_redir **begin_list,
				char *str, enum e_type type);
t_redir		*ft_create_elem_redir_null(void);
void		ft_list_clear_redir(t_redir *begin_list);

/* manage_lists_lenv.c */
t_lenv		*ft_create_elem_lenv(char *k, char *v);
void		ft_list_push_back_lenv(t_lenv **begin_list, char *k, char *v);
void		ft_list_clear_lenv(t_lenv *begin_list);

#endif
