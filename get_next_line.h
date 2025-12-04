/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fletelie <fletelie@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 16:00:58 by fletelie          #+#    #+#             */
/*   Updated: 2025/12/04 11:24:58 by fletelie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFFER_SIZE 10
# include <unistd.h>
//# include <stddef.h>
typedef struct s_filedata
{
	int			last_read_i;
	char		**file_lines;
	size_t		*file_len;
}	t_filedata;

char	*get_next_line(int fd);

char	**ft_split(char const *s, char c);

size_t	ft_strlcat(char *dst, const char *src, size_t size);

#endif