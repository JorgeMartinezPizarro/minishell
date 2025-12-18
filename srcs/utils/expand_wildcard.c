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
** Recursive expansion by path segments
*/
static void	expand_recursive(const char *base,
				char **segments, int idx, char ***out)
{
	DIR				*dir;
	struct dirent	*ent;
	char			*path;

	if (!segments[idx])
	{
		*out = str_array_add(*out, ft_strdup(base));
		return ;
	}
	dir = opendir(base);
	if (!dir)
		return ;
	while ((ent = readdir(dir)))
	{
		if (ent->d_name[0] == '.' && segments[idx][0] != '.')
			continue ;
		if (!match_star(ent->d_name, segments[idx]))
			continue ;
		path = join_paths(base, ent->d_name);
		if (!segments[idx + 1])
			*out = str_array_add(*out, path);
		else if (is_directory(path))
		{
			expand_recursive(path, segments, idx + 1, out);
			free(path);
		}
		else
			free(path);
	}
	closedir(dir);
}

static void	free_str_array(char **arr)
{
	int i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

/*
** Public API
*/
char	**expand_wildcard(const char *cwd, const char *pattern)
{
	char	**segments;
	char	**result;

	result = NULL;
	segments = ft_split(pattern, '/');
	if (!segments)
		return (str_array_add(NULL, ft_strdup(pattern)));
	expand_recursive(cwd, segments, 0, &result);
	free_str_array(segments);
	if (!result)
		result = str_array_add(NULL, ft_strdup(pattern));
	return (result);
}
