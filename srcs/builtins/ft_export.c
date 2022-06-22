/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasli <aasli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 12:37:38 by aasli             #+#    #+#             */
/*   Updated: 2022/06/22 17:36:47 by aasli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../headers/builtins.h"
#include "../libft/libft.h"

static int	print_export_error(char *s1, char *s2, char *s3)
{
	char	*tmp;

	tmp = ft_strdjoin(s1, s2, s3);
	if (!tmp)
		return (1);
	write(2, tmp, ft_strlen(tmp));
	free(tmp);
	return (1);
}

static void	make_export(t_data *data, char *cmd)
{
	int		j;
	char	*k;

	j = check_key(cmd);
	k = get_key(cmd);
	if (!k)
		return ;
	if (is_bad_identifier(cmd[0]) == 1)
		print_export_error("Rovidshell: export: '",
			cmd, "': not a valid identifier\n");
	else if (check_env_con(&data->env, k) == 1 && k && c_c(k) == 1)
		con_var_env(&data->env, cmd + j + 1, k, ft_strlen(k) - 2);
	else if (k && check_env_var(&data->env, k))
		rep_var_env(&data->env, cmd + j + 1, k, ft_strlen(k));
	else if (*k)
		add_var_env(data, cmd);
	free(k);
}

int	ft_export(char **cmd, t_data *data)
{
	int		i;

	i = 1;
	if (cmd[1])
	{
		if (cmd[1][0] == '-')
			return (print_export_error("Rovidshell: export: '", cmd[1],
					"': options are not handled\n"), 2);
		while (cmd[i])
		{	
			make_export(data, cmd[i]);
			i++;
		}
		return (0);
	}
	else
		write(2, "Rovidshell: export: undefined behavior on bash posix\n",
			ft_strlen("Rovidshell: export: undefined behavior on bash posix\n"));
	return (2);
}
