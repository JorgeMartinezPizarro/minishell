/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnchar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 16:53:00 by jomarti3          #+#    #+#             */
/*   Updated: 2025/10/10 00:39:26 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_putnchar(char c, int n)
{
	int	count;

	count = 0;
	while (n-- > 0)
	{
		write(1, &c, 1);
		count++;
	}
	return (count);
}
