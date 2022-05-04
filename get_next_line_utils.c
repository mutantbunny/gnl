/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 22:10:41 by gmachado          #+#    #+#             */
/*   Updated: 2022/05/02 22:02:02 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	int	len;

	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}

void	append(char **s1, char *s2, size_t s2_len)
{
	size_t	s1_len;
	size_t	index;
	char	*result;

	if (*s1 == NULL)
		s1_len = 0;
	else
		s1_len = ft_strlen(*s1);
	result = (char *)malloc((s1_len + s2_len + 1) * sizeof(char));
	index = 0;
	while (index < s1_len)
	{
		result[index] = (*s1)[index];
		index++;
	}
	index = 0;
	while (index < s2_len)
	{
		result[s1_len + index] = s2[index];
		index++;
	}
	result[s1_len + s2_len] = '\0';
	free(*s1);
	*s1 = result;
}

void	shift_buffer(char *buffer, size_t pos)
{
	size_t	index;

	index = 0;
	while (index + pos <= BUFFER_SIZE && buffer[index + pos] != '\0')
	{
		buffer[index] = buffer[pos + index];
		index++;
	}
	buffer[index] = '\0';
}

int	split_remaining(char **result, char *remaining)
{
	size_t	pos;

	pos = 0;
	while (remaining[pos] != '\n' && remaining[pos] != '\0')
		pos++;
	if (remaining[pos] == '\n')
	{
		append(result, remaining, pos + 1);
		if (*result == NULL)
			return (ERROR);
		shift_buffer(remaining, pos + 1);
		return (FALSE);
	}
	append(result, remaining, pos);
	if (*result == NULL)
		return (ERROR);
	remaining[0] = '\0';
	return (TRUE);
}
