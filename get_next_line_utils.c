/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 22:10:41 by gmachado          #+#    #+#             */
/*   Updated: 2022/04/25 21:36:40 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int get_remaining_length(t_buffer *buf_ptr, int *length);
int get_read_length(t_buffer *buf_ptr, int *length);
size_t copy_remaining(char *s, t_buffer *buf_ptr, int length);
void copy_line(char *s, t_buffer *buf_ptr);
int append_line(char *s, t_buffer *buf_ptr);
