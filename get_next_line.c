/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fletelie <fletelie@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 15:59:23 by fletelie          #+#    #+#             */
/*   Updated: 2025/12/05 14:56:40 by fletelie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

void	free_filedata(t_filedata *fdata)
{
	if (fdata->tempstore)
		free(fdata->tempstore);
	free(fdata);
}

void	read_chunk(int fd, char *dest)
{
	
}

char	*find_line(t_filedata fdata, int fd)
{
	char	*next_line;
	size_t	bytes_read;
	size_t	t_index;

	temp_index = 0;
	if (fdata->tempstore)
	{
		while(fdata->tempstore[t_index])
		{
			
		}
	}

}

char	*get_next_line(int fd)
{
	static t_filedata	*filedata;

	if (!filedata)
	{
		filedata = malloc(sizeof(*filedata));
		if (!filedata)
			return (NULL);
		filedata->fd = fd;
		filedata->tempstore = NULL;
	}
	return (find_line(filedata, fd));
}
