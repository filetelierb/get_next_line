/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fletelie <fletelie@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 15:59:23 by fletelie          #+#    #+#             */
/*   Updated: 2025/12/12 10:01:04 by fletelie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_handler *free_handler(t_handler *h, int free_all, int free_nl, int free_tmp)
{
	if (h)
	{
		if (h->next_line && (free_all > 0 || free_nl > 0))
		{
			free(h->next_line);
			h->next_line = NULL;
		}
		if (h->tempstore && (free_all > 0 || free_tmp > 0))
		{
			free(h->tempstore);
			h->tempstore = NULL;
		}
		if (free_all > 0)
		{
			free(h);
			return (NULL);
		}
	}
	return (h);
}

static t_handler	*extract_substr(t_handler *h, char *end)
{
	ssize_t	len;
	ssize_t	i;
	ssize_t	j;

	i = 0;
	j = 0;
	len = end - h->tempstore;
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

static t_handler	*load_chunk(t_handler *h, char *buffer, int fd, ssize_t *b)
{
	ssize_t	new_len;

	*b = read(fd, buffer, BUFFER_SIZE);
	new_len = h->len;
	if (*b > 0)
	{
		if (*b + h->len + 1 > (ssize_t)sizeof((h->tempstore)))
		{
			expand_tempstore(h);
			if (!h->tempstore)
				return (NULL);
		}
		while (new_len < h->len + *b)
		{
			h->tempstore[new_len] = buffer[new_len - h->len];
			new_len ++;
		}
		h->tempstore[new_len] = '\0';
		h->len = new_len;
	}
	return (h);
}

static char	*update_next_line(t_handler *td, int fd)
{
	char	*line_end;
	char	buffer[BUFFER_SIZE + 1];
	ssize_t	bytes;

	line_end = ft_strchr(td->tempstore, '\n');
	if (line_end)
	{
		if (!extract_substr(td, line_end))
			return (NULL);
		return (td->next_line);
	}
	if (!load_chunk(td, buffer, fd, &bytes))
		return (NULL);
	if (bytes < BUFFER_SIZE)
	{
		if (!extract_substr(td, &(td->tempstore[td->len])))
			return (NULL);
		return (td->next_line);
	}
	return (update_next_line(td, fd));
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
			free(h);
			return (NULL);
		}
		h->tempstore[0] = '\0';
		h->len = 0;
		h->cap = BUFFER_SIZE + 1;
		h->next_line = NULL;
	}
	if (!update_next_line(h, fd))
	{
		h = free_handler(h, 1, 0, 0);
		return (NULL);
	}
	return (h->next_line);
}
