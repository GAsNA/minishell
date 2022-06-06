/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasli <aasli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 08:12:10 by aasli             #+#    #+#             */
/*   Updated: 2022/06/06 16:10:26 by aasli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage.h"

static t_glist	*ft_glast(t_glist *lst)
{
	t_glist	*tmp;

	tmp = lst;
	if (!tmp)
		return (NULL);
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		return (tmp);
	}
}

static int	ft_gaddback(t_glist **lst, t_glist *el)
{
	t_glist	*last;

	(void)last;
	if ((*lst)->el == NULL)
	{
		printf("First element\n");
		if (*lst != NULL)
			free(*lst);
		*lst = el;
	}
	else
	{
		last = ft_glast(*lst);
		printf("Other element\n");
		last->next = el;
		el->prev = last;
	}
	return (1);
}

void	*ft_malloc(size_t size, size_t len, t_glist **lst)
{
	void	*ptr;
	t_glist	*new;

	new = malloc(sizeof(t_glist) * 1);
	ptr = malloc(sizeof(size) * len);
	if (!ptr || !new)
	{
		printf("Malloc error\n");
		ft_free_all(lst);
		return (NULL);
	}
	else
	{
		new->el = ptr;
		new->prev = NULL;
		new->next = NULL;
		ft_gaddback(lst, new);
		printf("Add backed\n");
	}
	return (ptr);
}

void	ft_gfree(t_glist **lst, void *ptr)
{
	t_glist	*tmp;
	t_glist	*prev;
	t_glist	*next;

	tmp = *lst;
	while (tmp)
	{
		if (tmp->el == ptr)
			break ;
		tmp = tmp->next;
	}
	prev = tmp->prev;
	next = tmp->next;
	prev->next = next;
	next->prev = prev;
	free (tmp->el);
	free (tmp);
}

int	ft_free_all(t_glist **lst)
{
	t_glist	*tmp;
	t_glist	*tmp2;

	tmp = *lst;
	tmp2 = NULL;
	while (tmp)
	{
		tmp2 = tmp->next;
		free(tmp->el);
		free(tmp);
		tmp = tmp2;
	}
	return (0);
}
