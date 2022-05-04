/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 19:06:15 by gmachado          #+#    #+#             */
/*   Updated: 2022/05/04 00:44:12 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *s)
{
	int	len;

	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}

t_node	*add_node(t_node *fd_list, int fd)
{
	t_node	*new_node;
	t_node	*cur_node;
	size_t	index;

	index = 0;
	new_node = (t_node *)malloc(sizeof(t_node));
	if (new_node == NULL)
		return (NULL);
	while (index <= BUFFER_SIZE)
		new_node->buffer[index++] = '\0';
	new_node->fd = fd;
	new_node->next = NULL;

	if (fd_list == NULL)
		return (new_node);
	cur_node = fd_list;
	while (cur_node->next != NULL)
		cur_node = cur_node->next;
	cur_node->next = new_node;
	return (fd_list);
}

t_node	*remove_node(t_node *fd_list, int fd)
{
	t_node	*cur_node;
	t_node	*tmp_node;

	if (fd_list == NULL)
		return (NULL);
	if (fd_list->fd == fd)
	{
		tmp_node = fd_list->next;
		free(fd_list);
		return (tmp_node);
	}
	cur_node = fd_list;
	while (cur_node->next != NULL && cur_node->next->fd != fd)
		cur_node = cur_node->next;
	if (cur_node->next != NULL)
	{
		tmp_node = cur_node->next->next;
		free(cur_node->next);
		cur_node->next = tmp_node;
	}
	return (fd_list);
}

t_node	*get_node_by_fd(t_node *fd_list, int fd)
{
	while (fd_list != NULL && fd_list->fd != fd)
		fd_list = fd_list->next;
	return (fd_list);
}
