/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasli <aasli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 08:17:07 by aasli             #+#    #+#             */
/*   Updated: 2022/06/06 16:10:23 by aasli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GARBAGE_H
# define GARBAGE_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef	struct s_glist
{
	void			*el;
	struct	s_glist *prev;
	struct	s_glist *next;
}	t_glist;

void	*ft_malloc(size_t size, size_t len, t_glist **lst);
void	ft_gfree(t_glist **lst, void *ptr);
int		ft_free_all(t_glist **lst);
char	*ft_strgdup(t_glist **lst, const char *str);
char	*ft_strgjoin(t_glist **lst, const char *s1, char const *s2);
char	*ft_subgstr(t_glist **lst, char const *s, unsigned int start, size_t len);
char	**ft_gsplit(t_glist **lst, const char *s, char c);

#endif
