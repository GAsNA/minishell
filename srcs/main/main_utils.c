/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasli <aasli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 13:41:09 by aasli             #+#    #+#             */
/*   Updated: 2022/06/19 13:47:31 by aasli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../headers/builtins.h"
#include "../libft/libft.h"

int	empty_cmd(t_cmd *cmd)
{
	if (cmd && !cmd->cmd)
	{
		free(cmd);
		return (1);
	}
	return (0);
}
