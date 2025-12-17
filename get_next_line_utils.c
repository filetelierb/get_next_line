/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fletelie <fletelie@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 16:00:55 by fletelie          #+#    #+#             */
/*   Updated: 2025/12/17 17:48:24 by fletelie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (1)
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		if (s[i] == '\0')
			return (0);
		i++;
	}
}

t_handler	*expand_tempstore(t_handler *td)
{
	char	*new_s;
	ssize_t	new_size;
	ssize_t	i;

	new_size = td->cap + BUFFER_SIZE;
	i = 0;
	new_s = malloc(new_size);
	if (!new_s)
		return (NULL);
	while (td->tempstore[i])
	{
		new_s[i] = td->tempstore[i];
		i ++;
	}
	new_s[i] = '\0';
	free(td->tempstore);
	td->tempstore = new_s;
	td->cap = new_size;
	return (td);
}

void	free_handler(t_handler *h, int free_all, int free_nl, int free_tmp)
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

t_handler	*init_handler(t_handler *h, int fd)
{
	if (fd < 0 || BUFFER_SIZE < 0 || read(fd, 0, 0))
	{
		free_handler(h, 1, 0, 0);
		return (NULL);
	}
	if (!h->tempstore)
	{
		h->tempstore = malloc(BUFFER_SIZE + 1);
		if (!(h->tempstore))
			return (NULL);
		h->tempstore[0] = '\0';
		h->len = 0;
		h->cap = BUFFER_SIZE + 1;
		h->next_line = NULL;
	}
	return (h);
}
