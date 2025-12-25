/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strreplace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maanguit <maanguit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 19:47:34 by maanguit          #+#    #+#             */
/*   Updated: 2025/12/25 20:09:55 by maanguit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_occur(const char *s, const char *a)
{
	size_t	count;
	size_t	len_a;

	if (!*a)
		return (0);
	count = 0;
	len_a = ft_strlen(a);
	s = ft_strnstr(s, a, ft_strlen(s));
	while (s)
	{
		count++;
		s += len_a;
		s = ft_strnstr(s, a, ft_strlen(s));
	}
	return (count);
}

static size_t	final_len(const char *s, const char *a, const char *b)
{
	size_t	n;
	size_t	la;
	size_t	lb;

	la = ft_strlen(a);
	lb = ft_strlen(b);
	n = count_occur(s, a);
	return (ft_strlen(s) + n * (lb - la));
}

char	*ft_strreplace(const char *s, const char *a, const char *b)
{
	char		*r;
	size_t		la;
	size_t		lb;
	char		*p;

	if (!s || !a || !b)
		return (NULL);
	la = ft_strlen(a);
	if (la == 0)
		return (ft_strdup(s));
	lb = ft_strlen(b);
	r = malloc(final_len(s, a, b) + 1);
	if (!r)
		return (NULL);
	p = r;
	while (*s)
		if (ft_strnstr(s, a, la) == s && (p += lb))
		{
			ft_memcpy(p - lb, b, lb);
			s += la;
		}
		else
			*p++ = *s++;
	*p = '\0';
	return (r);
}
