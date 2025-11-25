/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_char_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 17:39:02 by jomarti3          #+#    #+#             */
/*   Updated: 2025/10/13 02:33:05 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"
#include "ft_printf.h"
#include <unistd.h>

int	parse_char(t_fmt *fmt, va_list *args)
{
	char	c;
	int		count;

	count = 0;
	c = (char)va_arg(*args, int);
	if (!fmt->flag_minus && fmt->width > 1)
		count += ft_putnchar(' ', fmt->width - 1);
	count += write(1, &c, 1);
	if (fmt->flag_minus && fmt->width > 1)
		count += ft_putnchar(' ', fmt->width - 1);
	return (count);
}
