/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleseur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 10:11:37 by rleseur           #+#    #+#             */
/*   Updated: 2022/06/10 10:12:35 by rleseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_syntax(char c)
{
	printf("Rovidshell: syntax error near unexpected token `");
	if (!c)
		printf("newline'\n");
	else
		printf("%c'\n", c);
	return (0);
}
