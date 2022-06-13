/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasli <aasli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 08:57:16 by aasli             #+#    #+#             */
/*   Updated: 2022/06/13 08:57:37 by aasli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage.h"

int	main(void)
{
	t_glist	*list;
	t_glist	*test;
	char	**split;
	char	*james;

	list = malloc(sizeof(t_glist));
	list->el = NULL;
	list->next = NULL;
	list->prev = NULL;
	ft_strgdup(&list, "Hello toi");
	ft_strgdup(&list, "Hello moi");
	james = ft_strgjoin(&list, "Hello vous", " et moi");
	ft_subgstr(&list, "Hello vous", 3, 5);
	ft_gfree(&list, (void *)james);
	ft_subgstr(&list, "Hellotghyr", 3, 5);
	split = ft_gsplit(&list, "fregtep/gty65y /yuyt uyuyt/frgt", '/');
	printf("%s\n", (char *)list->el);
	printf("%s\n", (char *)list->next->el);
	printf("%s\n", (char *)list->next->next->el);
	printf("%s\n", (char *)list->next->next->next->el);
	test = list->next->next->next;
	test = test->prev;
	printf("%s\n", (char *)test->el);
	printf("%s\n", split[0]);
	printf("%s\n", split[1]);
	ft_free_all(&list);
}
