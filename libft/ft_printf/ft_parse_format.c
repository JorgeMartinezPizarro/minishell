/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_format.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 17:32:25 by jomarti3          #+#    #+#             */
/*   Updated: 2025/10/13 02:33:05 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"
#include "ft_printf.h"

const char	*parse_format(const char *fmt, t_fmt *f, va_list *args)
{
	(void)args;
	f->spec = *fmt;
	if (!ft_strchr("%disxXupc", f->spec))
		f->spec = 0;
	if (f->spec != 0)
		fmt++;
	return (fmt);
}
