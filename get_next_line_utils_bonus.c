/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 19:06:15 by gmachado          #+#    #+#             */
/*   Updated: 2022/05/07 20:43:32 by gmachado         ###   ########.fr       */
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

t_hash	*create_hash(t_hash *old_hash, size_t capacity_power)
{
	t_hash			*new_hash;
	size_t			index;
	unsigned int	capacity;

	capacity = 1 << capacity_power;
	if (old_hash->length < capacity)
		return (old_hash);
	new_hash = (t_hash *)malloc(sizeof(t_hash));
	new_hash->capacity_power = capacity_power;
	new_hash->table = (t_hash *)malloc(capacity * sizeof(t_hash_node));
	index = 0;
	while (index < capacity)
		new_hash->table[index] = NULL;
	if (old_hash != NULL)
	{
		index = 0;
		new_hash->length = old_hash->length;
		while (index < (1 << old_hash->capacity_power))
			add_to_hash(&new_hash, old_hash->table[index]);
		return (new_hash);
	}
	new_hash->length = 0;
	return (new_hash);
}

// Hashing function from:
// https://stackoverflow.com/questions/11871245/knuth-multiplicative-hash
int	add_to_hash(t_hash **hash_p, int key)
{
	unsigned long	key_hash;
	unsigned int	capacity;
	unsigned int	count;

	if (!hash_p || !*hash_p)
		return (ERROR);
	while (TRUE)
	{
		count = 0;
		capacity = 1 << (*hash_p)->capacity_power;
		key_hash = (key * 2654435769L) >> (32 - (*hash_p)->capacity_power);
		while (count++ < capacity && !(*hash_p)->table[key_hash])
			key_hash = (key_hash + 1) % capacity;
		if (count == capacity)
			*hash_p = create_hash(*hash_p, (*hash_p)->capacity_power * 2);
		else
			break ;
	}
	(*hash_p)->table[key_hash] = (t_hash_node *)malloc(sizeof(t_hash_node));
	(*hash_p)->table[key_hash]->buffer[0] = '\0';
	(*hash_p)->table[key_hash]->fd = key;
	(*hash_p)->length++;
}

int	remove_from_hash(t_hash *hash, int key)
{
	unsigned long	key_hash;
	unsigned int	capacity;
	unsigned int	count;

	if (hash == NULL)
		return (FALSE);
	count = 0;
	capacity = 1 << hash->capacity_power;
	key_hash = (key * 2654435769L) >> (32 - hash->capacity_power);
	while (count++ < capacity && !hash->table[key_hash]->fd != key)
		key_hash = (key_hash + 1) % capacity;
	if (count < capacity)
	{
		free(hash->table[key_hash]);
		hash->table[key_hash] = NULL;
		return (TRUE);
	}
	return (FALSE);
}

t_hash_node	*get_node(t_hash *hash, int key)
{
	unsigned long	key_hash;
	unsigned int	capacity;
	unsigned int	count;

	if (hash == NULL)
		return (NULL);
	count = 0;
	capacity = 1 << hash->capacity_power;
	key_hash = (key * 2654435769L) >> (32 - hash->capacity_power);
	while (count++ < capacity && !hash->table[key_hash]->fd != key)
		key_hash = (key_hash + 1) % capacity;
	if (count < capacity)
		return (hash->table[key_hash]);
	return (NULL);
}
