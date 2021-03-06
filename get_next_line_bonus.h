/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 19:06:58 by gmachado          #+#    #+#             */
/*   Updated: 2022/05/09 22:38:10 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>

# define FALSE 0
# define TRUE 1
# define ERROR -1

typedef struct s_node
{
	char			buffer[BUFFER_SIZE + 1];
	int				fd;
	struct s_node	*next;
}	t_node;

char	*get_next_line(int fd);
char	*process_line(t_node **fd_list_ptr, char *remaining, int fd);
size_t	ft_strlen(const char *s);
void	append(char **s1, char *s2, size_t s2_len);
int		split_remaining(char **result, char *remaining);
t_node	*remove_node(t_node *fd_list, int fd);
t_node	*add_node(t_node *fd_list, int fd);
t_node	*get_node_by_fd(t_node *fd_list, int fd);

#endif
