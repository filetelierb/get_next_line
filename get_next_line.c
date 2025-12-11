/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fletelie <fletelie@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 15:59:23 by fletelie          #+#    #+#             */
/*   Updated: 2025/12/11 16:37:04 by fletelie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	free_handler(t_handler *h)
{
	if (h)
	{
		if (h->next_line)
			free(h->next_line);
		if (h->tempstore)
			free(h->tempstore);
		free(h);
	}
}

char	*extract_substr(t_handler *h, char *end)
{
	ssize_t	len;
	ssize_t	i;
	ssize_t	j;

	i = 0;
	j = 0;
	len = (ssize_t)(&end - &(h->tempstore[i]));
	h->next_line = malloc(len + 1);
	if (!h->next_line)
		return (NULL);
	while (i < len)
	{
		h->next_line[i] = h->tempstore[i];
		i ++;
	}
	while (h->tempstore[i + j])
	{
		h->tempstore[j] = h->tempstore[i + j];
		j ++;
	}
	h->tempstore[j] = '\0';
	h->len = j;
	h->next_line[i] = '\0';
	return (h);
}

t_handler	*load_chunk(t_handler *h, char *buffer, int fd, ssize_t *b)
{
	ssize_t	new_len;

	*b = read(fd, buffer, BUFFER_SIZE);
	new_len = h->len;
	if (*b > 0)
	{
		if (*b + h->len + 1 > sizeof(h->tempstore))
		{
			h->tempstore = expand_mem(h->tempstore);
			if (!h->tempstore)
			{
				free_tmpdata(h->tempstore);
				return (NULL);
			}
		}
		while (new_len < h->len + *b)
		{
			h->tempstore[new_len] = buffer[new_len - h->len];
			new_len ++;
		}
		h->tempstore[new_len] = '\0';
		h->len = new_len;
		return (h);
	}
}

char	*update_next_line(t_handler *td, int fd)
{
	char	*line_end;
	char	buffer[BUFFER_SIZE + 1];
	ssize_t	bytes;

	line_end = ft_strchr(td->tempstore, '\n');
	if (line_end)
	{
		td->next_line = extract_substr(&td, line_end);
		if (!td->next_line)
			return (NULL);
		return (td->next_line);
	}
	if (!load_chunk(td, buffer, fd, &bytes))
		return (NULL);
	if (bytes < BUFFER_SIZE)
	{
		td->next_line = extract_substr(&td, &(td->tempstore[td->len]));
		if (!td->next_line)
			return (NULL);
	}
	return (td->next_line);
}

char	*get_next_line(int fd)
{
	static t_handler	*h;

	if (!h)
	{
		h = malloc(sizeof(t_handler));
		if (!h)
			return (NULL);
		h->tempstore = malloc(BUFFER_SIZE + 1);
		if (!(h->tempstore))
		{
			free_tmpdata(h);
			return (NULL);
		}
		h->tempstore[0] = '\0';
		h->len = 0;
		h->next_line = NULL;
	}
	else
		free(h->next_line);
	if (!update_next_line(&h, fd))
	{
		free_tmpdata(&h);
		return (NULL);
	}
	return (h->next_line);
}
