/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: voldemort <voldemort@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 17:46:05 by nismayil          #+#    #+#             */
/*   Updated: 2026/09/15 19:13:04 by voldemort        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_linelen(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] == '\n')
		i++;
	return (i);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*empty;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	empty = (char *)malloc(ft_linelen(s1) + ft_linelen(s2) + 1);
	if (!empty)
		return (free(s1), NULL);
	while (s1 && s1[i])
	{
		empty[i] = s1[i];
		i++;
	}
	while (s2 && s2[j] && s2[j] != '\n')
	{
		empty[i + j] = s2[j];
		j++;
	}
	if (s2 && s2[j] == '\n')
		empty[i + j++] = '\n';
	empty[i + j] = '\0';
	free(s1);
	return (empty);
}

void	ft_buff_move(char *buffer)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (buffer[i] != '\n' && buffer[i] != '\0')
		i++;
	if (buffer[i] == '\n')
		i++;
	while (buffer[j] != '\0')
		buffer[j++] = buffer[i++];
	buffer[j] = '\0';
}
