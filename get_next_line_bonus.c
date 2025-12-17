/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fletelie <fletelie@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 15:59:23 by fletelie          #+#    #+#             */
/*   Updated: 2025/12/17 18:23:52 by fletelie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static t_handler	*extract_substr(t_handler *h, char *end, int offset)
{
	ssize_t	i;

	i = 0;
	h->next_line = malloc(end - h->tempstore + offset + 1);
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
		extract_substr(h, h->tempstore + h->len - 1, 1);
		return (h->next_line);
	}
	else if (bytes <= 0)
		return (NULL);
	return (fetch_line(h, fd));
}

static t_handler	*get_handler(t_handler *h, int fd)
{
	t_handler	*new_h;

	if (h->fd == fd)
		return (h);
	else if (h->nh)
		return (get_handler(h->nh, fd));
	else
	{
		new_h = malloc(sizeof(t_handler));
		if (!new_h)
			return (NULL);
		new_h->fd = fd;
		new_h->nh = NULL;
		new_h->tempstore = NULL;
		new_h->next_line = NULL;
		new_h->len = 0;
		new_h->cap = 0;
		h->nh = new_h;
		return (new_h);
	}
}

char	*get_next_line(int fd)
{
	static t_handler	init_h = {NULL, NULL, 0, 0, NULL, -1};
	t_handler			*h;
	char				*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	h = get_handler(&init_h, fd);
	if (!h)
		return (NULL);
	if (!init_handler(h))
	{
		free_h(&init_h, h);
		return (NULL);
	}
	line = fetch_line(h, fd);
	if (!line)
	{
		free_h(&init_h, h);
		return (NULL);
	}
	h->next_line = NULL;
	return (line);
}
