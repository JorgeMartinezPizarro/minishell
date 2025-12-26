/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_program_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 16:32:35 by jomarti3          #+#    #+#             */
/*   Updated: 2025/12/26 22:46:43 by jomarti3         ###   ########.fr       */
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

	if (stat(path, &st) != 0 || !S_ISREG(st.st_mode) || access(path, X_OK) != 0)
		return (print_error(path, "file not found"), NULL);
	return (ft_strdup(path));
}

static char	*search_path(char *path_env, const char *cmd)
{
	char		**dirs;
	char		*full;
	int			i;
	struct stat	st;

	dirs = ft_split(path_env, ':');
	if (!dirs)
		return (NULL);
	i = 0;
	while (dirs[i])
	{
		full = join_paths(dirs[i], cmd);
		if (stat(full, &st) == 0 && S_ISREG(st.st_mode)
			&& access(full, X_OK) == 0)
			return (free_str_array(dirs), full);
		free(full);
		i++;
	}
	free_str_array(dirs);
	return (print_error(cmd, "command not found"), NULL);
}

char	*find_executable(const char *cmd, t_list *env)
{
	char	*path_env;

	if (ft_strchr(cmd, '/'))
		return (check_file(cmd));
	path_env = get_env_value(env, "PATH");
	if (!path_env)
		return (print_error(cmd, "command not found"), NULL);
	return (search_path(path_env, cmd));
}
