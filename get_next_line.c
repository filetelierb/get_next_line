/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fletelie <fletelie@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 15:59:23 by fletelie          #+#    #+#             */
/*   Updated: 2025/12/04 11:53:27 by fletelie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*expand_mem(char *s, ssize_t *buff_size)
{
	char	*new_s;
	ssize_t	i;

	*buff_size = *buff_size + BUFFER_SIZE;
	new_s = malloc(*buff_size + 1);
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

char	**extract_file_lines(int fd)
{
	char		*chunk_buffer[BUFFER_SIZE];
	char		*file_buffer;
	char		**lines;
	ssize_t		bytes_read;
	ssize_t		file_len;
	ssize_t		file_buff_size;

	file_buff_size = BUFFER_SIZE;
	file_buffer = malloc(file_buff_size + 1);
	if (!file_buffer)
		return (NULL);
	file_len = 0;
	bytes_read = read(fd, chunk_buffer, BUFFER_SIZE);
	while (bytes_read)
	{
		file_len = ft_strlcat(file_buffer, chunk_buffer, bytes_read + file_len + 1);
		bytes_read = read(fd, chunk_buffer, BUFFER_SIZE);
		if (bytes_read > 0)
			file_buffer = expand_mem(file_buffer, file_buff_size);
	}
	lines = ft_split((const char *)file_buffer,'\n');
	free(file_buffer);
	if (!lines)
		return (NULL);
	return (lines);	
}

char	*get_next_line(int fd)
{
	static t_filedata	*filedata;

	if (!filedata)
		filedata = malloc(sizeof(*filedata));
	if (!filedata)
		return (NULL);
	filedata->file_lines = extract_file_lines(fd);
}