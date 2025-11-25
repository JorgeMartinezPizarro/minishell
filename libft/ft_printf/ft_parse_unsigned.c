/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_unsigned.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 23:55:53 by jomarti3          #+#    #+#             */
/*   Updated: 2025/10/13 02:33:05 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include "ft_printf_utils.h"
#include "ft_printf.h"

int	parse_unsigned(t_fmt *fmt, uintmax_t value, const char *base, char *prefix)
{
	char	*str;
	int		len;
	int		prefix_len;

	if (fmt->spec == 'p' && value == 0)
		return (write(1, "(nil)", 5));
	str = ft_utoa_base(value, base);
	if (!str)
		return (0);
	len = ft_strlen(str);
	prefix_len = ft_strlen(prefix);
	write(1, prefix, prefix_len);
	write(1, str, len);
	free(str);
	return (len + prefix_len);
}
