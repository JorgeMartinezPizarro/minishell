# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/20 21:38:45 by jomarti3          #+#    #+#              #
#    Updated: 2025/11/20 22:01:26 by jomarti3         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re

CC      = cc
CFLAGS  = -Wall -Wextra -Werror -I. -I..

GNL_FILES = get_next_line_bonus get_next_line_utils_bonus
OBJS      = $(GNL_FILES:=.o)

all: $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean

re: fclean all
