# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/07 12:41:09 by jomarti3          #+#    #+#              #
#    Updated: 2025/11/21 12:51:48 by jomarti3         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re

CC      = cc
CFLAGS  = -Wall -Wextra -Werror -I./src/ -I./ft_printf -I./gnl
NAME    = libft.a

LIBFT_DIR   = src
PRINTF_DIR  = ft_printf
GNL_DIR     = gnl

FUNCTIONS = \
	ft_isalnum ft_isalpha ft_isdigit ft_isascii \
	ft_strlen ft_memset ft_isprint ft_bzero \
	ft_memcpy ft_strlcpy ft_toupper ft_strlcat \
	ft_tolower ft_strdup ft_strncmp ft_atoi \
	ft_memmove ft_memcmp ft_memchr ft_strnstr \
	ft_strchr ft_strrchr ft_calloc ft_substr \
	ft_putnbr_fd ft_itoa ft_strjoin ft_strtrim \
	ft_split ft_strmapi ft_striteri ft_putchar_fd \
	ft_putstr_fd ft_putendl_fd ft_itoa_base ft_utoa_base \
	ft_strcmp ft_strreplace

BONUS_FUNCTIONS = \
	ft_lstnew ft_lstadd_front ft_lstsize ft_lstdelone \
	ft_lstadd_back ft_lstlast ft_lstclear ft_lstiter \
	ft_lstmap

LIBFT_FUNCTIONS = \
	${FUNCTIONS} \
	$(BONUS_FUNCTIONS:=_bonus)

PRINTF_FUNCTIONS = \
	ft_is_valid_base \
	ft_dispatch_format ft_printf ft_putnchar \
	ft_parse_decimal_bonus ft_parse_unsigned_bonus \
	ft_parse_char_bonus ft_parse_string_bonus \
	ft_parse_format_bonus

GNL_FUNCTIONS = \
	get_next_line \
	get_next_line_utils

LIBFT_OBJS	= $(addprefix $(LIBFT_DIR)/,	$(LIBFT_FUNCTIONS:=.o) )

PRINTF_OBJS = $(addprefix $(PRINTF_DIR)/,	$(PRINTF_FUNCTIONS:=.o))

GNL_OBJS 	= $(addprefix $(GNL_DIR)/, 		$(GNL_FUNCTIONS:=_bonus.o))

all: $(NAME)

$(NAME): $(LIBFT_OBJS)
	@$(MAKE) -C $(PRINTF_DIR)
	@$(MAKE) -C $(GNL_DIR)
	ar rcs $(NAME) $(LIBFT_OBJS) $(PRINTF_OBJS) $(GNL_OBJS)

clean:
	rm -f $(LIBFT_OBJS)
	@$(MAKE) -C $(PRINTF_DIR) clean
	@$(MAKE) -C $(GNL_DIR) clean

fclean: clean
	rm -f $(NAME)
	@$(MAKE) -C $(PRINTF_DIR) fclean
	@$(MAKE) -C $(GNL_DIR) fclean

re: fclean all