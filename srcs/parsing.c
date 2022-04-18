/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleseur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 10:28:13 by rleseur           #+#    #+#             */
/*   Updated: 2022/04/18 13:45:30 by rleseur          ###   ########.fr       */
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

static int	is_char(char c, char *charset)
{
	int	i;

	i = -1;
	while (charset[++i])
		if (c == charset[i])
			return (1);
	return (0);
}

static int	count_words(char const *s, char *charset)
{
	int	i;
	int	words;

	i = 0;
	while (s[i] && is_char(s[i], charset))
		i++;
	words = 0;
	while (s[i])
	{
		while (s[i] && !is_char(s[i], charset))
			i++;
		words++;
		while (s[i] && is_char(s[i], charset))
			i++;
	}
	return (words);
}

static char	*ft_strdup_mod(char const *s, char *charset)
{
	char	*dup;
	int		i;

	i = 0;
	while (s[i] && !is_char(s[i], charset))
		i++;
	dup = malloc((i + 1) * sizeof(char));
	if (!dup)
		return (0);
	i = -1;
	while (s[++i] && !is_char(s[i], charset))
		dup[i] = s[i];
	dup[i] = '\0';
	return (dup);
}

char	**to_free(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
	return (0);
}

char	**ft_split(char const *s, char *charset)
{
	int		words;
	char	**tab;
	int		i;
	int		j;

	if (!s)
		return (0);
	words = count_words(s, charset);
	tab = malloc((words + 1) * sizeof(char *));
	if (!tab)
		return (0);
	i = 0;
	j = 0;
	while (s[i] && j < words)
	{
		while (s[i] && is_char(s[i], charset))
			i++;
		tab[j] = ft_strdup_mod(&s[i], charset);
		if (!tab[j++])
			return (to_free(tab));
		while (s[i] && !is_char(s[i], charset))
			i++;
	}
	tab[j] = 0;
	return (tab);
}

// Separer all words (except "" et '')
char	**get_commands(char *line)
{
	char	**commands;

	commands = ft_split(line, " '\"");
	if (!is_quotes_close(line))
	{
		printf("C'est pas bon.\n");
		return (0);
	}

	return (commands);
}
