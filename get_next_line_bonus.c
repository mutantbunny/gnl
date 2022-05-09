/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 19:05:57 by gmachado          #+#    #+#             */
/*   Updated: 2022/05/07 23:50:21 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	append(char **s1, char *s2, size_t s2_len)
{
	size_t	s1_len;
	size_t	index;
	char	*result;

	if (!(*s1))
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
	while (index < s1_len + s2_len)
		result[index++] = *s2++;
	result[index] = '\0';
	free(*s1);
	*s1 = result;
}

void	shift_buffer(char *buffer, size_t pos)
{
	while (*(buffer + pos))
	{
		*buffer = *(buffer + pos);
		buffer++;
	}
	*buffer = '\0';
}

int	split_remaining(char **result, char *remaining)
{
	size_t	pos;

	pos = 0;
	while (remaining[pos] && remaining[pos] != '\n')
		pos++;
	if (remaining[pos] == '\n')
	{
		append(result, remaining, pos + 1);
		if (!(*result))
			return (ERROR);
		shift_buffer(remaining, pos + 1);
		return (FALSE);
	}
	append(result, remaining, pos);
	if (!(*result))
		return (ERROR);
	remaining[0] = '\0';
	return (TRUE);
}

char	*process_line(t_hash **fd_hash_ptr, char *remaining, int fd)
{
	char	*result;
	ssize_t	bytes_read;
	int		should_read;

	result = NULL;
	should_read = split_remaining(&result, remaining);
	while (should_read == TRUE)
	{
		bytes_read = read(fd, remaining, BUFFER_SIZE);
		if (!bytes_read && *result)
		{
			remove_from_hash(fd_hash_ptr, fd);
			return (result);
		}
		if (bytes_read <= 0)
		{
			remove_from_hash(fd_hash_ptr, fd);
			free(result);
			return (NULL);
		}
		remaining[bytes_read] = '\0';
		should_read = split_remaining(&result, remaining);
	}
	return (result);
}

char	*get_next_line(int fd)
{
	static t_hash	*fd_hash;
	t_hash_node		*fd_node;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	fd_node = get_node(fd_hash, fd);
	if (fd_hash == NULL)
		fd_hash = create_hash(NULL, MIN_CAP_POWER);
	if (fd_node == NULL)
	{
		fd_node = (t_hash_node *)malloc(sizeof(t_hash_node));
		fd_node->buffer[0] = '\0';
		fd_node->fd = fd;
		if (add_to_hash(&fd_hash, fd_node) == ERROR)
			return (NULL);
	}
	return (process_line(&fd_hash, fd_node->buffer, fd));
}
