/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fletelie <fletelie@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 16:00:55 by fletelie          #+#    #+#             */
/*   Updated: 2025/12/09 18:43:32 by fletelie         ###   ########.fr       */
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

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*dst_s;
	const unsigned char	*src_s;
	size_t				i;

	if (!dst && !src)
		return (NULL);
	dst_s = (unsigned char *)dst;
	src_s = (const unsigned char *)src;
	i = 0;
	while (i < n)
	{
		dst_s[i] = src_s[i];
		i++;
	}
	return (dst);
}

void	free_tmpdata(t_tempstore *td)
{
	if (td)
	{
		if (td->next_line)
			free(td->next_line);
		if (td->tempstore)
			free(td->tempstore);
		free(td);
	}
}

char	*expand_mem(char *s)
{
	char	*new_s;
	ssize_t	new_size;
	ssize_t	i;

	new_size = sizeof(s) + BUFFER_SIZE;
	new_s = malloc(new_size);
	if (!new_s)
		return (NULL);
	while (s[i])
	{
		new_s[i] = s[i];
		i ++;
	}
	new_s[i] = '\0';
	free (s);
	return (new_s);
}
