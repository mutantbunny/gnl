/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 19:06:58 by gmachado          #+#    #+#             */
/*   Updated: 2022/05/09 19:42:56 by gmachado         ###   ########.fr       */
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
# define MIN_CAP_POWER 10U
# define KNUTH_CONST 2654435769U
# define UINT_SZ 32U

typedef struct s_hash_node
{
	char	buffer[BUFFER_SIZE + 1];
	int		fd;
}	t_hash_node;

typedef struct s_hash
{
	unsigned int	capacity_power;
	unsigned int	length;
	t_hash_node		**table;
}	t_hash;

char		*get_next_line(int fd);
char		*process_line(t_hash **fd_hash_ptr, char *remaining, int fd);
size_t		ft_strlen(const char *s);
void		append(char **s1, char *s2, size_t s2_len);
int			split_remaining(char **result, char *remaining);
t_hash		*create_hash(t_hash *old_hash, unsigned int capacity_power);
int			add_to_hash(t_hash **hash_p, t_hash_node *node);
int			remove_from_hash(t_hash **hash, int key);
t_hash_node	*get_node(t_hash *hash, int key);

#endif
