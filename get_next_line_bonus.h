/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fletelie <fletelie@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 16:00:58 by fletelie          #+#    #+#             */
/*   Updated: 2025/12/17 18:23:45 by fletelie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000000
# endif
# include <unistd.h>
# include <stdlib.h>

typedef struct s_nlhandler
{
	char				*tempstore;
	char				*next_line;
	ssize_t				len;
	ssize_t				cap;
	struct s_nlhandler	*nh;
	int					fd;
}	t_handler;
char		*get_next_line(int fd);
char		*ft_strchr(const char *s, int c);
t_handler	*init_handler(t_handler *h);
t_handler	*expand_tempstore(t_handler *td);
void		free_h(t_handler *head, t_handler *h);

#endif