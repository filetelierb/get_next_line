/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fletelie <fletelie@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 16:00:58 by fletelie          #+#    #+#             */
/*   Updated: 2025/12/04 18:40:39 by fletelie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif
# include <unistd.h>
//# include <stddef.h>
typedef struct s_filedata
{
	char	*tempstore;
	char	*curline;
}	t_filedata;

char	*get_next_line(int fd);

#endif