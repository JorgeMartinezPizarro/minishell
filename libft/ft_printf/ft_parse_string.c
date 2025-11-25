/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_string.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 17:31:19 by jomarti3          #+#    #+#             */
/*   Updated: 2025/10/13 02:33:05 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"
#include "ft_printf.h"
#include <unistd.h>

int	parse_string(t_fmt *fmt, va_list *args)
{
	char	*str;

	(void)fmt;
	str = va_arg(*args, char *);
	if (!str)
		str = "(null)";
	return (write(1, str, ft_strlen(str)));
}
