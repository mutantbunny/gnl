/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 21:02:55 by gmachado          #+#    #+#             */
/*   Updated: 2022/04/25 21:36:39 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_buffer	line_buffer = {.active = 1, .start = BUFFER_SIZE};
	char			*result;
	size_t			alloc_length;
	int				new_line_reached;

	if (fd < 0)
		return (NULL);
	if (line_buffer.start < BUFFER_SIZE)
		new_line_reached = get_remaining_length(&line_buffer, &alloc_length);
	if (!new_line_reached)
		new_line_reached = get_read_length(&line_buffer, &alloc_length);
	result = (char *)malloc(alloc_length * sizeof(char));
	if (result == NULL)
		return (NULL);
	alloc_length = copy_remaining(result, &line_buffer, alloc_length);
	if (alloc_length != 0)
		copy_line(result, &line_buffer);
	while (!new_line_reached)
		new_line_reached = append_line(result, &line_buffer);
	return result;
}
