/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fletelie <fletelie@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 16:00:55 by fletelie          #+#    #+#             */
/*   Updated: 2025/12/04 11:28:55 by fletelie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	**sp_malloc(char const *s, char c, size_t *len)
{
	size_t	i;
	size_t	count;
	char	**sp_mem;

	i = 0;
	count = 0;
	if (!s)
		return (NULL);
	*len = ft_strlen(s);
	while (s[i])
	{
		if (s[i] != c)
		{
			while (s[i] != c && s[i])
				i ++;
			count ++;
		}
		else
			i ++;
	}
	sp_mem = ft_calloc((count + 1), sizeof(char *));
	if (sp_mem == NULL)
		return (NULL);
	return (sp_mem);
}

static char	*get_word(char const *s, char c, size_t *start, size_t len)
{
	char	*w_end;
	char	*new_word;
	size_t	w_len;

	w_len = 0;
	w_end = ft_strchr(&s[*start], c);
	if (w_end == 0)
		w_len = (size_t)(&s[len] - &s[*start]);
	else
		w_len = (size_t)(w_end - &s[*start]);
	new_word = ft_substr(s, *start, w_len);
	*start = *start + w_len - 1;
	return (new_word);
}

static void	free_sp(char **sp)
{
	size_t	i;

	i = 0;
	while (sp[i])
	{
		free(sp[i]);
		i ++;
	}
	free(sp);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	len;
	size_t	sp_i;
	char	**split;

	i = 0;
	sp_i = 0;
	split = sp_malloc(s, c, &len);
	if (split == 0)
		return (NULL);
	while (s[i])
	{
		if (s[i] != c)
		{
			split[sp_i] = get_word(s, c, &i, len);
			if (split[sp_i] == NULL)
			{
				free_sp(split);
				return (NULL);
			}
			sp_i ++;
		}
		i ++;
	}
	return (split);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t		dst_len;
	size_t		src_len;
	size_t		i;
	size_t		init_l;

	src_len = ft_strlen(src);
	i = 0;
	if (size == 0)
		return (src_len);
	dst_len = ft_strlen(dst);
	if (dst_len < size)
		init_l = dst_len;
	else
		init_l = size;
	while (dst_len + i < size - 1 && i < src_len)
	{
		dst[dst_len + i] = src[i];
		i ++;
	}
	dst[dst_len + i] = '\0';
	return (init_l + src_len);
}
