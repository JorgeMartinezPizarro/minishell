/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_valid_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 18:23:46 by jomarti3          #+#    #+#             */
/*   Updated: 2025/12/04 20:45:10 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

static int	ft_isspace(char c)
{
	return (c == ' '
		|| c == '\t'
		|| c == '\n'
		|| c == '\f'
		|| c == '\r'
		|| c == '\v'
	);
}

int	ft_valid_int(const char *str)
{
	long	val;
	int		sign;

	val = 0;
	sign = 1;
	if (!str || !*str)
		return (0);
	while (ft_isspace(*str) == 1)
		str++;
	if (*str == '+' || *str == '-')
		if (*(str++) == '-')
			sign = -1;
	if (!*str)
		return (0);
	while (*str)
	{
		if (!ft_isdigit((unsigned char)*str))
			return (0);
		val = val * 10 + (*str - '0');
		if ((sign == 1 && val > INT_MAX) || (sign == -1 && (-val) < INT_MIN))
			return (0);
		str++;
	}
	return (1);
}
