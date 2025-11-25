/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 15:25:02 by jomarti3          #+#    #+#             */
/*   Updated: 2025/10/05 22:42:43 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*str1;
	const unsigned char	*str2;
	int					i;

	str1 = (const unsigned char *)s1;
	str2 = (const unsigned char *)s2;
	i = -1;
	while ((size_t)(++i) < n)
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
	return (0);
}
