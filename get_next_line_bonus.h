/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 19:06:58 by gmachado          #+#    #+#             */
/*   Updated: 2022/05/07 20:42:54 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# define FALSE 0
# define TRUE 1
# define ERROR -1
# define MIN_CAPACITY 1024

typedef struct s_hash_node
{
	char	buffer[BUFFER_SIZE + 1];
	int		fd;
}	t_hash_node;

typedef struct s_hash
{
	size_t		capacity_power;
	size_t		length;
	t_hash_node	**table;
}	t_hash;

char		*get_next_line(int fd);
char		*process_line(t_hash **fd_hash_ptr, char *remaining, int fd);
size_t		ft_strlen(const char *s);
void		append(char **s1, char *s2, size_t s2_len);
int			split_remaining(char **result, char *remaining);
t_hash		*create_hash(t_hash *old_hash, size_t capacity_power);
int			add_to_hash(t_hash **hash_p, int key);
int			remove_from_hash(t_hash *hash, int key);
t_hash_node	*get_node(t_hash *hash, int key);

#endif
