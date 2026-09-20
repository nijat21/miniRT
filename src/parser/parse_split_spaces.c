/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_split_spaces.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abraz-ab <abraz-ab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 18:25:46 by abraz-ab          #+#    #+#             */
/*   Updated: 2026/09/21 00:17:36 by abraz-ab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <parser.h>

static int	skip_spaces(char *str, int i)
{
	while (str[i] && is_space(str[i]))
		i++;
	return (i);
}

static int	fill_word(char *str, char **res, int *i, int j)
{
	int	start;

	*i = skip_spaces(str, *i);
	if (!str[*i])
		return (0);
	start = *i;
	while (str[*i] && !is_space(str[*i]))
		(*i)++;
	res[j] = word_dup(str, start, *i);
	if (!res[j])
		return (-1);
	return (1);
}

static int	fill_split(char *str, char **res)
{
	int	i;
	int	j;
	int	status;

	i = 0;
	j = 0;
	while (str[i])
	{
		status = fill_word(str, res, &i, j);
		if (status == -1)
		{
			free_split(res, j);
			return (0);
		}
		if (status == 0)
			break ;
		j++;
	}
	res[j] = NULL;
	return (1);
}

char	**ft_split_spaces(char *str)
{
	char	**res;

	res = malloc(sizeof(char *) * (count_words(str) + 1));
	if (!res)
		return (NULL);
	if (!fill_split(str, res))
		return (NULL);
	return (res);
}
