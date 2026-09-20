/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_split_spaces.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abraz-ab <abraz-ab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 18:25:46 by abraz-ab          #+#    #+#             */
/*   Updated: 2026/09/20 18:30:43 by abraz-ab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <parser.h>

static int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

static int	count_words(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && is_space(str[i]))
			i++;
		if (str[i])
		{
			count++;
			while (str[i] && !is_space(str[i]))
				i++;
		}
	}
	return (count);
}

static char	*word_dup(char *str, int start, int end)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc(end - start + 1);
	if (!word)
		return (NULL);
	while (start < end)
		word[i++] = str[start++];
	word[i] = '\0';
	return (word);
}

static char	**split_alloc(char *str)
{
	char	**res;

	res = malloc(sizeof(char *) * (count_words(str) + 1));
	if (!res)
		return (NULL);
	return (res);
}

char	**ft_split_spaces(char *str)
{
	char	**res;
	int		i;
	int		j;
	int		start;

	i = 0;
	j = 0;
	res = split_alloc(str);
	while (str[i])
	{
		while (str[i] && is_space(str[i]))
			i++;
		if (!str[i])
			break ;
		start = i;
		while (str[i] && !is_space(str[i]))
			i++;
		res[j] = word_dup(str, start, i);
		if (!res[j])
			return (free_split(res, j));
		j++;
	}
	res[j] = NULL;
	return (res);
}
