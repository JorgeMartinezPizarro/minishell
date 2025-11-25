/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_decimal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 23:55:22 by jomarti3          #+#    #+#             */
/*   Updated: 2025/10/13 02:33:05 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "ft_printf_utils.h"
#include "ft_printf.h"

int	parse_decimal(t_fmt *fmt, va_list *args)
{
	int		count;
	int		value;
	char	*str;
	int		len;

	(void)*fmt;
	value = va_arg(*args, int);
	str = ft_itoa_base(value, "0123456789");
	if (!str)
		return (0);
	len = ft_strlen(str);
	count = write(1, str, len);
	free(str);
	return (count);
}
