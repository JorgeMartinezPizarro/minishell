/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 15:35:51 by jomarti3          #+#    #+#             */
/*   Updated: 2025/10/05 22:42:33 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	const unsigned char	*src;
	unsigned char		ch;

	i = 0;
	ch = (unsigned char)c;
	src = (const unsigned char *)s;
	while (i < n)
	{
		if (src[i] == ch)
			return ((void *)(src + i));
		i++;
	}
	return (NULL);
}
