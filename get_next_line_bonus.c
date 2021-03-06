/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 19:05:57 by gmachado          #+#    #+#             */
/*   Updated: 2022/05/05 15:05:26 by gmachado         ###   ########.fr       */
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

char	*process_line(t_node **fd_list_ptr, char *remaining, int fd)
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
			*fd_list_ptr = remove_node(*fd_list_ptr, fd);
			return (result);
		}
		if (bytes_read <= 0)
		{
			*fd_list_ptr = remove_node(*fd_list_ptr, fd);
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
	static t_node	*fd_list;
	t_node			*fd_node;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	fd_node = get_node_by_fd(fd_list, fd);
	if (fd_node == NULL)
		fd_node = add_node(fd_list, fd);
	if (fd_list == NULL)
		fd_list = fd_node;
	return (process_line(&fd_list, fd_node->buffer, fd));
}
