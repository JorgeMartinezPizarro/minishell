/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 17:08:04 by jomarti3          #+#    #+#             */
/*   Updated: 2025/10/13 02:33:05 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"
#include "ft_printf.h"
#include <unistd.h>

int	parse_char(t_fmt *fmt, va_list *args)
{
	char	c;

	c = (char)va_arg(*args, int);
	(void)*fmt;
	return (write(1, &c, 1));
}
