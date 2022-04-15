/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleseur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 10:28:13 by rleseur           #+#    #+#             */
/*   Updated: 2022/04/15 16:57:38 by rleseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// NORME
static int	is_quotes_close(char *line)
{
	int	i;
	int	s_quote;
	int	d_quote;

	s_quote = 0;
	d_quote = 0;
	i = -1;
	while (line[++i])
	{
		if (line[i] == '\'')
		{
			if (s_quote == 0 && d_quote == 0)
				s_quote = 1;
			else
				s_quote = 0;
		}
		else if (line[i] == '"')
		{
			if (d_quote == 0 && s_quote == 0)
				d_quote = 1;
			else
				d_quote = 0;
		}
	}
	if (s_quote == 1 || d_quote == 1)
		return (0);
	return (1);
}

static int	counter_words(char *str)
{
	int	i;
	int	in_quote;
	int	nb_words;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	in_quote = 0;
	nb_words = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
			in_quote = 1;
		while (str[i] && (str[i] != ' ' || in_quote == 1))
		{
			if (str[i] == '"' || str[i] == '\'')
				in_quote = 0;
			i++;
		}
		nb_words++;
		while (str[i] && (str[i] == ' ' && in_quote == 0))
		{
			if (str[i] == '"' || str[i] == '\'')
				in_quote = 1;
			i++;
		}
	}
	return (nb_words);
}

static char	*ft_strdup(char *src)
{
	char	*dest;
	int		i;
	int		len;
	int		in_quote;

	len = 0;
	in_quote = 1;
	while (src[len] && (src[len] != ' ' || in_quote == 1))
	{
		if (src[i] == '"' || src[i] == '\'')
			in_quote = 0;
		len++;
	}
	dest = malloc((len + 1) * sizeof(char));
	if (!dest)
		return (0);
	i = 0;
	while (src[i] && src[i] != ' ')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

static char	**ft_split(char *str)
{
	char	**tab;
	int		nb_words;
	int		i;
	int		j;

	nb_words = counter_words(str);
	tab = malloc((nb_words + 1) * sizeof(char *));
	if (!tab)
		return (0);
	i = 0;
	j = 0;
	while (str[i] && j < nb_words)
	{
		while (str[i] && str[i] == ' ')
			i++;
		tab[j] = ft_strdup(&str[i]);
		if (!tab[j])
			return (0);
		j++;
		while (str[i] && str[i] != ' ')
			i++;
	}
	tab[j] = 0;
	return (tab);
}

// Separer all words (except "" et '')
char	**get_commands(char *line)
{
	char	**commands;

	commands = ft_split(line);
	if (!is_quotes_close(line))
	{
		printf("C'est pas bon.\n");
		return (0);
	}

	return (commands);
}
