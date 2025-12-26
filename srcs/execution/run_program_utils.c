/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_program_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 00:51:37 by jomarti3          #+#    #+#             */
/*   Updated: 2025/12/27 00:53:23 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(const char *str1, const char *str2)
{
	ft_putstr_fd((char *)str1, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd((char *)str2, 2);
	ft_putstr_fd("\n", 2);
}

static char	*check_file(const char *path)
{
	struct stat	st;

	if (stat(path, &st) != 0)
		return (g_exit_code = EXIT_NOT_FOUND,
			print_error(path, "No such file or directory"), NULL);
	if (S_ISDIR(st.st_mode))
		return (g_exit_code = EXIT_CANT_EXEC,
			print_error(path, "Is a directory"), NULL);
	if (access(path, X_OK) != 0)
		return (g_exit_code = EXIT_CANT_EXEC,
			print_error(path, "Permission denied"), NULL);
	return (ft_strdup(path));
}

static char	*search_in_dirs(char **dirs, const char *cmd)
{
	char		*full;
	int			i;
	struct stat	st;

	i = 0;
	while (dirs[i])
	{
		full = join_paths(dirs[i], cmd);
		if (stat(full, &st) == 0)
		{
			if (S_ISREG(st.st_mode) && access(full, X_OK) == 0)
				return (free_str_array(dirs), full);
			free(full);
			free_str_array(dirs);
			g_exit_code = EXIT_CANT_EXEC;
			print_error(cmd, "Permission denied");
			return (NULL);
		}
		free(full);
		i++;
	}
	free_str_array(dirs);
	return (NULL);
}

static char	*search_path(char *path_env, const char *cmd)
{
	char	**dirs;
	char	*res;

	if (!path_env)
		return (g_exit_code = EXIT_NOT_FOUND,
			print_error(cmd, "command not found"), NULL);
	dirs = ft_split(path_env, ':');
	if (!dirs)
		return (g_exit_code = EXIT_GENERAL_ERROR, NULL);
	res = search_in_dirs(dirs, cmd);
	if (!res)
	{
		g_exit_code = EXIT_NOT_FOUND;
		print_error(cmd, "command not found");
	}
	return (res);
}

char	*find_executable(const char *cmd, t_list *env)
{
	char	*path_env;

	if (ft_strchr(cmd, '/'))
		return (check_file(cmd));
	path_env = get_env_value(env, "PATH");
	if (!path_env)
		return (g_exit_code = EXIT_NOT_FOUND,
			print_error(cmd, "command not found"), NULL);
	return (search_path(path_env, cmd));
}
