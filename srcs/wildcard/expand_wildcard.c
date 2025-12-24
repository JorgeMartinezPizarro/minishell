/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maanguit <maanguit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 16:56:55 by jomarti3          #+#    #+#             */
/*   Updated: 2025/12/24 00:51:37 by maanguit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "libft.h"
#include "minishell_jorge.h"

/*
** Match string against pattern with '*' (multiple allowed)
*/
static int	match_star(const char *str, const char *pat)
{
	if (*pat == '\0')
		return (*str == '\0');
	if (*pat == '*')
	{
		while (*pat == '*')
			pat++;
		if (*pat == '\0')
			return (1);
		while (*str)
		{
			if (match_star(str, pat))
				return (1);
			str++;
		}
		return (0);
	}
	if (*str && *str == *pat)
		return (match_star(str + 1, pat + 1));
	return (0);
}

/*
** Add string to NULL-terminated array
*/
static char	**str_array_add(char **arr, char *s)
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

/*
** Check if path is directory
*/
static int	is_directory(const char *path)
{
	struct stat	st;

	if (stat(path, &st) == -1)
		return (0);
	return (S_ISDIR(st.st_mode));
}

/*
** Join two path segments for relative output
*/
static char	*join_relpath(const char *base, const char *name)
{
	char	*tmp;
	char	*res;

	if (!base || base[0] == '\0')
		return (ft_strdup(name));
	tmp = ft_strjoin(base, "/");
	res = ft_strjoin(tmp, name);
	free(tmp);
	return (res);
}

/*
** Recursive helper for wildcard expansion
*/
static void	expand_recursive_rel(const char *fs_base,
				const char *rel_base, char **segments, int idx, char ***out)
{
	DIR				*dir;
	struct dirent	*ent;
	char			*next_fs;
	char			*next_rel;

	if (!segments[idx])
	{
		*out = str_array_add(*out, ft_strdup(rel_base));
		return;
	}
	dir = opendir(fs_base);
	if (!dir)
		return;
	while ((ent = readdir(dir)))
	{
		if (ent->d_name[0] == '.' && segments[idx][0] != '.')
			continue;
		if (!match_star(ent->d_name, segments[idx]))
			continue;
		next_fs = join_paths(fs_base, ent->d_name);
		next_rel = join_relpath(rel_base, ent->d_name);
		if (!segments[idx + 1])
		{
			*out = str_array_add(*out, ft_strdup(next_rel));
		}
		else if (is_directory(next_fs))
		{
			expand_recursive_rel(next_fs, next_rel, segments, idx + 1, out);
		}
		free(next_fs);
		free(next_rel);
	}
	closedir(dir);
}

/*
** Public API.
*/
char	**expand_wildcard(const char *cwd, const char *pattern)
{
	char	**segments;
	char	**result;

	result = NULL;
	segments = ft_split(pattern, '/');
	if (!segments)
		return (str_array_add(NULL, ft_strdup(pattern)));
	expand_recursive_rel(cwd, "", segments, 0, &result);
	free_str_array(segments);
	if (!result)
		result = str_array_add(NULL, ft_strdup(pattern));
	return (result);
}
