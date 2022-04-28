/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasli <aasli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 09:43:07 by aasli             #+#    #+#             */
/*   Updated: 2022/04/28 14:17:06 by rleseur          ###   ########.fr       */
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

typedef struct s_data		t_data;
typedef struct s_lexing		t_lexing;
typedef struct s_regroup	t_regroup;
typedef struct s_pipe		t_pipe;
typedef struct s_cmd		t_cmd;
typedef struct s_redir		t_redir;
typedef struct s_lenv		t_lenv;

struct s_data
{
	int		run;
	int		exit_code;
	char	**env;
	char	*line;
};

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
t_pipe		*parsing(t_regroup *reg, t_lenv *lenv);

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

/* manage_lists_redir.c */
t_redir		*ft_create_elem_redir(char *str, enum e_type type);
void		ft_list_push_back_redir(t_redir **begin_list,
				char *str, enum e_type type);
t_redir		*ft_create_elem_redir_null(void);
void		ft_list_clear_redir(t_redir *begin_list);

/* manage_lists_lenv.c */
t_lenv		*ft_create_elem_lenv(char *k, char *v);
void		ft_list_push_back_lenv(t_lenv **begin_list, char *k, char *v);

/* utils.c */
int			ft_strcmp(char *s1, char *s2);
int			ft_strncmp(char *s1, char *s2, unsigned int n);
int			ft_strlen(char *s);

#endif
