/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 19:06:15 by gmachado          #+#    #+#             */
/*   Updated: 2022/05/09 19:42:57 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}

t_hash	*create_hash(t_hash *old_hash, unsigned int capacity_power)
{
	t_hash			*new_hash;
	unsigned int	index;
	unsigned int	capacity;

	capacity = 1U << capacity_power;
	if (old_hash && old_hash->length < capacity)
		return (old_hash);
	new_hash = (t_hash *)malloc(sizeof(t_hash));
	new_hash->capacity_power = capacity_power;
	new_hash->table = (t_hash_node **)malloc(capacity * sizeof(t_hash_node *));
	index = 0;
	while (index < capacity)
		new_hash->table[index++] = NULL;
	if (old_hash != NULL)
	{
		index = 0;
		new_hash->length = old_hash->length;
		while (index < (1U << old_hash->capacity_power))
			add_to_hash(&new_hash, old_hash->table[index]);
		free(old_hash);
		return (new_hash);
	}
	new_hash->length = 0;
	return (new_hash);
}

// Hashing function from:
// https://stackoverflow.com/questions/11871245/knuth-multiplicative-hash
int	add_to_hash(t_hash **hash_p, t_hash_node *node)
{
	unsigned int	h;
	unsigned int	capacity;
	unsigned int	count;

	if (!hash_p || !*hash_p)
		return (ERROR);
	while (TRUE)
	{
		count = 0;
		capacity = 1U << (*hash_p)->capacity_power;
		h = (node->fd * KNUTH_CONST) >> (UINT_SZ - (*hash_p)->capacity_power);
		while (count++ < capacity && (*hash_p)->table[h])
			h = (h + 1) % capacity;
		if (count == capacity)
			*hash_p = create_hash(*hash_p, (*hash_p)->capacity_power << 1U);
		else
			break ;
	}
	(*hash_p)->table[h] = node;
	(*hash_p)->length++;
	return (TRUE);
}

int	remove_from_hash(t_hash **hash_p, int k)
{
	unsigned int	h;
	unsigned int	cap;
	unsigned int	c;

	if (!hash_p || !*hash_p)
		return (FALSE);
	c = 0;
	cap = 1U << (*hash_p)->capacity_power;
	h = (k * KNUTH_CONST) >> (UINT_SZ - (*hash_p)->capacity_power);
	while (c++ < cap && (!(*hash_p)->table[h] || (*hash_p)->table[h]->fd != k))
		h = (h + 1) % cap;
	if (c < cap)
	{
		free((*hash_p)->table[h]);
		(*hash_p)->table[h] = NULL;
		if ((--((*hash_p)->length)) == 0)
		{
			free((*hash_p)->table);
			free(*hash_p);
			*hash_p = NULL;
		}
		return (TRUE);
	}
	return (FALSE);
}

t_hash_node	*get_node(t_hash *hash, int key)
{
	unsigned int	key_hash;
	unsigned int	capacity;
	unsigned int	count;

	if (hash == NULL)
		return (NULL);
	count = 0;
	capacity = 1U << hash->capacity_power;
	key_hash = (key * KNUTH_CONST) >> (UINT_SZ - hash->capacity_power);
	if (hash->table[key_hash] == NULL)
		return (NULL);
	while (count++ < capacity && hash->table[key_hash]->fd != key)
	{
		key_hash = (key_hash + 1) % capacity;
		if (hash->table[key_hash] == NULL)
			return (NULL);
	}
	if (count < capacity)
		return (hash->table[key_hash]);
	return (NULL);
}
