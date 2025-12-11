# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fletelie <fletelie@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/11 17:21:51 by fletelie          #+#    #+#              #
#    Updated: 2025/12/11 17:30:56 by fletelie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

FLAGS = -Wall -Werror -Wextra -c

SRCS = get_next_line.c get_next_line_utils.c

OFILES = $(SRCS:.c=.o)

NAME = get_next_line.a

$(NAME): $(OFILES)
	ar -crs $(NAME) $(OFILES)

%.o: %.c
	$(CC) $(FLAGS) $< -o $@

.PHONY: clean fclean all re bonus

bonus: $(OFILES) $(BONUS_OFILES)
	ar -crs $(NAME) $(OFILES) $(BONUS_OFILES)

clean:
	$(RM) $(OFILES)

fclean: clean
	$(RM) $(NAME)

re: fclean $(NAME)

all: $(NAME)
