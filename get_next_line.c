/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fletelie <fletelie@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 15:59:23 by fletelie          #+#    #+#             */
/*   Updated: 2025/12/17 12:15:49 by fletelie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_handler	*extract_substr(t_handler *h, char *end, int offset)
{
	ssize_t	i;

	i = 0;
	h->next_line = malloc(end - h->tempstore + offset);
	if (!h->next_line)
		return (NULL);
	while (i <= end - h->tempstore)
	{
		h->next_line[i] = h->tempstore[i];
		i ++;
	}
	h->next_line[i] = '\0';
	h->len = 0;
	if (h->tempstore[end - h->tempstore] == '\0')
	{
		h->tempstore[0] = '\0';
		return (h);
	}
	while (h->tempstore[i + h->len])
	{
		h->tempstore[h->len] = h->tempstore[i + h->len];
		h->len = h->len + 1;
	}
	h->tempstore[h->len] = '\0';
	return (h);
}

static t_handler	*load_chunk(t_handler *h, int fd, ssize_t *b)
{
	if (h->len + BUFFER_SIZE + 1 > h->cap)
	{
		expand_tempstore(h);
		if (!h->tempstore)
			return (NULL);
	}
	*b = read(fd, h->tempstore + h->len, BUFFER_SIZE);
	if (*b > 0)
	{
		h->len += *b;
		h->tempstore[h->len] = '\0';
	}
	return (h);
}

static char	*fetch_line(t_handler *h, int fd)
{
	char	*line_end;
	ssize_t	bytes;

	line_end = ft_strchr(h->tempstore, '\n');
	if (line_end)
	{
		if (!extract_substr(h, line_end, 2))
			return (NULL);
		return (h->next_line);
	}
	if (!load_chunk(h, fd, &bytes))
		return (NULL);
	if (bytes == 0 && h->len > 0)
	{
		extract_substr(h, h->tempstore + h->len, 1);
		return (h->next_line);
	}
	else if (bytes <= 0)
		return (NULL);
	return (fetch_line(h, fd));
}

char	*get_next_line(int fd)
{
	static t_handler	h;
	char				*line;

	init_handler(&h, fd);
	if (!h.tempstore)
		return (NULL);
	line = fetch_line(&h, fd);
	if (!line)
	{
		free_handler(&h, 1, 0, 0);
		return (NULL);
	}
	h.next_line = NULL;
	return (line);
}
