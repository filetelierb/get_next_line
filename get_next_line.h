/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fletelie <fletelie@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 16:00:58 by fletelie          #+#    #+#             */
/*   Updated: 2025/12/11 16:37:22 by fletelie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif
# include <unistd.h>
//# include <stddef.h>
typedef struct s_nlhandler
{
	char	*tempstore;
	char	*next_line;
	ssize_t	len;
}	t_handler;

char	*get_next_line(int fd);
char	*ft_strchr(const char *s, int c);
void	free_tmpdata(t_handler *td);
char	*expand_mem(char *s);

#endif