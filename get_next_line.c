/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fletelie <fletelie@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 15:59:23 by fletelie          #+#    #+#             */
/*   Updated: 2025/12/09 21:03:53 by fletelie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	set_tempdata_len(t_tempstore *tempdata, ssize_t new_len)
{
	tempdata->tempstore[new_len] = '\0';
	tempdata->next_line[tempdata->len - new_len] = '\0';
	tempdata->len = new_len;
}

char	*extract_substr(t_tempstore *tempdata, char *end)
{
	ssize_t	len;
	ssize_t	i;
	ssize_t	j;

	i = 0;
	j = 0;
	len = (ssize_t)(&end - &(tempdata->tempstore[i]));
	tempdata->next_line = malloc(len + 1);
	if (!tempdata->next_line)
		return (NULL);
	while(i < len)
	{
		tempdata->next_line[i] = tempdata->tempstore[i];
		i ++;
	}
	while (tempdata->tempstore[i + j])
	{
		tempdata->tempstore[j] = tempdata->tempstore[i + j];
		j ++;
	}
	tempdata->tempstore[j] = '\0';
	tempdata->len = j;
	tempdata->next_line[i] = '\0';
	return (tempdata);
}

t_tempstore	*load_chunk(t_tempstore *tempdata, char *buffer, int fd, ssize_t *b)
{
	ssize_t new_len;
	
	*b = read(fd, buffer, BUFFER_SIZE);
	new_len = tempdata->len;
	if (*b > 0)
	{
		if(*b + tempdata->len + 1 > sizeof(tempdata->tempstore))
		{
			tempdata->tempstore = expand_mem(tempdata->tempstore);
			if (!tempdata->tempstore)
			{
				free_tmpdata(tempdata->tempstore);
				return (NULL);
			}
		}
		while(new_len < tempdata->len + *b)
		{
			tempdata->tempstore[new_len] = buffer[new_len - tempdata->len];
			new_len ++;
		}
		tempdata->tempstore[new_len] = '\0';
		tempdata->len = new_len;
		return (tempdata);
	}
}

char	*get_line(t_tempstore *td, int fd)
{
	char	*line_end;
	char	buffer[BUFFER_SIZE + 1];
	ssize_t	bytes;

	line_end = ft_strchr(td->tempstore, '\n');
	if (line_end)
	{
		td->next_line = extract_substr(&td, line_end);
		if (!td->next_line)
		{
			free_tmpdata(td);
			return (NULL);
		}
		return (td->next_line);
	}
	if (!load_chunk(td, buffer, fd, &bytes))
		return (NULL);
	if (bytes < BUFFER_SIZE)
	{
		td->next_line = extract_substr(&td, &(td->tempstore[td->len]));
		{
			free_tmpdata(td);
			return (NULL);
		}
	}
		
}

char	*get_next_line(int fd)
{
	static t_tempstore	*tempdata;

	if (!tempdata)
	{
		tempdata = malloc(sizeof(t_tempstore));
		if (!tempdata)
			return (NULL);
		tempdata->tempstore = malloc(BUFFER_SIZE + 1);
		if (!(tempdata->tempstore))
		{
			free_tmpdata(tempdata);
			return (NULL);
		}
		tempdata->tempstore[0] = '\0';
		tempdata->len = 0;
		tempdata->next_line = NULL;
	}
	else
		free(tempdata->next_line);
	return (get_line(&tempdata, fd));
}
