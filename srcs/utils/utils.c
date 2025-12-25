/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 16:41:41 by jomarti3          #+#    #+#             */
/*   Updated: 2025/12/25 21:22:10 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_jorge.h"

void	malloc_failed(void)
{
	g_exit_code = 1;
	perror("malloc");
}

char	**str_array_add(char **arr, char *s)
{
	char	**new;
	int		i;

	i = 0;
	while (arr && arr[i])
		i++;
	new = ft_calloc(i + 2, sizeof(char *));
	if (!new)
		return (NULL);
	i = 0;
	while (arr && arr[i])
	{
		new[i] = arr[i];
		i++;
	}
	new[i] = s;
	free(arr);
	return (new);
}

int	is_directory(const char *path)
{
	struct stat	st;

	if (stat(path, &st) == -1)
		return (0);
	return (S_ISDIR(st.st_mode));
}
