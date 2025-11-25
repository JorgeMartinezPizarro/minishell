# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/07 12:41:09 by jomarti3          #+#    #+#              #
#    Updated: 2025/11/20 22:08:41 by jomarti3         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re

CC      = cc
CFLAGS  = -Wall -Wextra -Werror -I. -I../src

BASE_FUNCTIONS = \
	ft_is_valid_base \
	ft_dispatch_format ft_printf ft_putnchar

PARSE_FUNCTIONS = \
	ft_parse_decimal_bonus ft_parse_unsigned_bonus \
	ft_parse_char_bonus ft_parse_string_bonus \
	ft_parse_format_bonus

OBJS = $(BASE_FUNCTIONS:=.o) $(PARSE_FUNCTIONS:=.o)

all: $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean

re: fclean all
