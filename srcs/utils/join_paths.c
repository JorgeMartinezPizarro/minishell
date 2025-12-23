/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 11:30:09 by jomarti3          #+#    #+#             */
/*   Updated: 2025/12/23 16:15:50 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Añade un segmento normal.
** Maneja ".", vacío y ".." igual que bash:
**   ""  -> ignorar
**   "." -> ignorar
**   ".." -> eliminar un nivel si existe, nunca añadir ".."
*/
static void	append_segment(char **arr, int *count, const char *seg)
{
	if (ft_strcmp(seg, "") == 0 || ft_strcmp(seg, ".") == 0)
		return ;
	if (ft_strcmp(seg, "..") == 0)
	{
		if (*count > 0)
			(*count)--;
		return ;
	}
	arr[*count] = ft_strdup(seg);
	if (!arr[*count])
		return ;
	(*count)++;
}

/*
** Divide un path por "/", procesa cada segmento.
** ft_split elimina múltiples '/', lo cual es correcto.
*/
static int	process_path(char **arr, int *count, const char *path)
{
	char	**tmp;
	int		i;

	tmp = ft_split(path, '/');
	if (!tmp)
		return (0);
	i = 0;
	while (tmp[i])
	{
		append_segment(arr, count, tmp[i]);
		free(tmp[i]);
		i++;
	}
	free(tmp);
	return (1);
}

/*
** Reconstruye: "/a/b/c"
*/
static char	*build_path(char **arr, int count)
{
	char	*res;
	char	*tmp;
	int		i;

	if (count == 0)
		return (ft_strdup("/"));
	res = ft_strdup("");
	if (!res)
		return (NULL);
	i = 0;
	while (i < count)
	{
		tmp = ft_strjoin(res, "/");
		free(res);
		if (!tmp)
			return (NULL);
		res = ft_strjoin(tmp, arr[i]);
		free(tmp);
		if (!res)
			return (NULL);
		i++;
	}
	return (res);
}

/*
** Igual a bash:
**   - Si 'relative' empieza con '/', ignora base.
**   - Normaliza ".", "..", y múltiples "/".
**   - Nunca permite subir por encima de "/".
**   - No conserva nunca ".." en el resultado final.
*/
char	*join_paths(const char *base, const char *relative)
{
	char	**segments;
	char	*result;
	int		count;

	if (!base || !relative)
		return (NULL);
	segments = (char **)malloc(sizeof(char *) * 512);
	if (!segments)
		return (NULL);
	count = 0;
	if (relative[0] != '/')
	{
		/* Arreglo crítico: un base vacío debe considerarse "/" */
		if (base[0] == '\0')
			base = "/";
		if (!process_path(segments, &count, base))
			return (free(segments), NULL);
	}
	if (!process_path(segments, &count, relative))
		return (free(segments), NULL);
	result = build_path(segments, count);
	while (count-- > 0)
		free(segments[count]);
	free(segments);
	return (result);
}
