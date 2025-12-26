/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 16:56:55 by jomarti3          #+#    #+#             */
/*   Updated: 2025/12/26 22:50:04 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
void	expand_handle_entry(t_expand_ctx *ctx, const char *entry_name)
{
	char			*next_fs;
	char			*next_rel;
	t_expand_ctx	next_ctx;

	next_fs = join_paths(ctx->fs_base, entry_name);
	next_rel = join_relpath(ctx->rel_base, entry_name);
	if (!ctx->segments[ctx->idx + 1])
		*ctx->out = str_array_add(*ctx->out, ft_strdup(next_rel));
	else if (is_directory(next_fs))
	{
		next_ctx = *ctx;
		next_ctx.fs_base = next_fs;
		next_ctx.rel_base = next_rel;
		next_ctx.idx = ctx->idx + 1;
		expand_recursive_rel(&next_ctx);
	}
	free(next_fs);
	free(next_rel);
}

void	expand_recursive_rel(t_expand_ctx *ctx)
{
	DIR				*dir;
	struct dirent	*ent;

	if (!ctx->segments[ctx->idx])
	{
		*ctx->out = str_array_add(*ctx->out, ft_strdup(ctx->rel_base));
		return ;
	}
	dir = opendir(ctx->fs_base);
	if (!dir)
		return ;
	ent = readdir(dir);
	while (ent)
	{
		if (ent->d_name[0] != '.' || ctx->segments[ctx->idx][0] == '.')
			if (match_star(ent->d_name, ctx->segments[ctx->idx]))
				expand_handle_entry(ctx, ent->d_name);
		ent = readdir(dir);
	}
	closedir(dir);
}

/*
** Public API.
*/
char	**expand_wildcard(const char *cwd, const char *pattern)
{
	char			**segments;
	char			**result;
	t_expand_ctx	ctx;

	result = NULL;
	segments = ft_split(pattern, '/');
	if (!segments)
		return (str_array_add(NULL, ft_strdup(pattern)));
	ctx.fs_base = cwd;
	ctx.rel_base = "";
	ctx.segments = segments;
	ctx.idx = 0;
	ctx.out = &result;
	expand_recursive_rel(&ctx);
	free_str_array(segments);
	if (!result)
		result = str_array_add(NULL, ft_strdup(pattern));
	return (result);
}
