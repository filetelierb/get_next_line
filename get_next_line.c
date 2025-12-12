/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fletelie <fletelie@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 15:59:23 by fletelie          #+#    #+#             */
/*   Updated: 2025/12/12 16:55:18 by fletelie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void free_handler(t_handler *h, int free_all, int free_nl, int free_tmp)
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
	}
}

static t_handler	*extract_substr(t_handler *h, char *end)
{
	ssize_t	len;
	ssize_t	i;
	ssize_t	j;

	i = 0;
	j = 0;
	len = end - h->tempstore;
	h->next_line = malloc(len + 2);
	if (!h->next_line)
		return (NULL);
	while (i <= len)
	{
		h->next_line[i] = h->tempstore[i];
		i ++;
	}
	h->next_line[i] = '\0';
	if (h->tempstore[len] == '\0')
    {
        h->tempstore[0] = '\0';
        h->len = 0;
        return (h);
    }
	while (h->tempstore[i + j])
	{
		h->tempstore[j] = h->tempstore[i + j];
		j ++;
	}
	h->tempstore[j] = '\0';
	h->len = j;
	return (h);
}

// static t_handler	*load_chunk(t_handler *h, char *buffer, int fd, ssize_t *b)
// {
// 	ssize_t	new_len;

// 	*b = read(fd, buffer, BUFFER_SIZE);
// 	new_len = h->len;
// 	if (*b > 0)
// 	{
// 		if (*b + h->len + 1 > h->cap)
// 		{
// 			expand_tempstore(h);
// 			if (!h->tempstore)
// 				return (NULL);
// 		}
// 		while (new_len < h->len + *b)
// 		{
// 			h->tempstore[new_len] = buffer[new_len - h->len];
// 			new_len ++;
// 		}
// 		h->tempstore[new_len] = '\0';
// 		h->len = new_len;
// 	}
// 	return (h);
// }

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

static char	*fetch_line(t_handler *td, int fd)
{
	char	*line_end;
	ssize_t	bytes;

	line_end = ft_strchr(td->tempstore, '\n');
	if (line_end)
	{
		if (!extract_substr(td, line_end))
			return (NULL);
		return (td->next_line);
	}
	if (!load_chunk(td, fd, &bytes))
		return (NULL);
	if (bytes == 0 && td->len > 0)
	{
		extract_substr(td, td->tempstore + td->len);
		return (td->next_line);
	}
	else if (bytes <= 0)
		return (NULL);
	return (fetch_line(td, fd));
}

char	*get_next_line(int fd)
{
	static t_handler	h;
	char				*line;
	
	if (fd < 0 || BUFFER_SIZE < 0 || read(fd, 0, 0))
	{
		free_handler(&h, 1, 0 ,0);
		return (NULL);
	}
	if (!h.tempstore)
	{
		h.tempstore = malloc(BUFFER_SIZE + 1);
		if (!(h.tempstore))
			return (NULL);
		h.tempstore[0] = '\0';
		h.len = 0;
		h.cap = BUFFER_SIZE + 1;
		h.next_line = NULL;
	}
	line = fetch_line(&h, fd);
	if (!line)
	{
		free_handler(&h, 1, 0 ,0);
		return (NULL);
	}
	h.next_line = NULL;
	return (line);
}
