/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasli <aasli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 12:32:57 by aasli             #+#    #+#             */
/*   Updated: 2022/06/22 17:41:31 by aasli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../headers/builtins.h"
#include "../libft/libft.h"

extern int	g_status;

char	*try_access_path(char *cmd, char **paths, int i)
{
	char	*path;
	char	*tmp;

	tmp = ft_strjoin(paths[i], "/");
	if (!tmp)
		return (NULL);
	path = ft_strjoin(tmp, cmd);
	if (!path)
		return (NULL);
	free(tmp);
	printf("%s\n", path);
	if (access(path, X_OK) == 0)
	{
		free_split(paths);
		return (path);
	}
	free(path);
	return (NULL);
}

char	*get_exec_path(char *cmd, t_data *data)
{
	char	**paths;
	int		i;
	char	*path;

	i = 0;
	if (data->min_env == 1)
		paths = ft_split(data->hidden_path, ':');
	else
		paths = ft_get_paths(&data->env);
	if (!paths)
		return (NULL);
	printf("%s\n", paths[0]);
	while (paths[i])
	{
		path = try_access_path(cmd, paths, i);
		if (path != NULL)
			return (path);
		i++;
	}
	free_split(paths);
	return (NULL);
}
