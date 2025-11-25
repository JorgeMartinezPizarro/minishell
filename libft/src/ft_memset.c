/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 15:38:21 by jomarti3          #+#    #+#             */
/*   Updated: 2025/10/05 22:43:12 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memset(void *dest, int c, size_t len)
{
	unsigned char	uc;
	unsigned char	*destiny;
	size_t			i;

	destiny = (unsigned char *)dest;
	uc = (unsigned char)c;
	i = 0;
	while (i < len)
	{
		destiny[i] = uc;
		i++;
	}
	return (dest);
}
