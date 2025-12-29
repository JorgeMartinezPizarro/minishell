/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_sorted_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 22:44:23 by jomarti3          #+#    #+#             */
/*   Updated: 2025/12/29 14:07:20 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	env_cmp(t_variable *a, t_variable *b)
{
	return (ft_strcmp(a->name, b->name));
}

static int	list_len(t_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

static t_variable	**list_to_array(t_list *lst, int len)
{
	t_variable	**arr;
	int			i;

	arr = malloc(sizeof(t_variable *) * (len + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (lst)
	{
		arr[i++] = (t_variable *)lst->content;
		lst = lst->next;
	}
	arr[i] = NULL;
	return (arr);
}

static void	sort_env_array(t_variable **arr)
{
	t_variable	*tmp;
	int			i;
	int			j;

	i = 0;
	while (arr[i])
	{
		j = i + 1;
		while (arr[j])
		{
			if (env_cmp(arr[i], arr[j]) > 0)
			{
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	print_sorted_env(t_list *env)
{
	t_variable	**arr;
	int			len;
	int			i;

	len = list_len(env);
	arr = list_to_array(env, len);
	if (!arr)
		return ;
	sort_env_array(arr);
	i = 0;
	while (arr[i])
	{
		if (arr[i]->exported == 1)
		{
			if (arr[i]->assigned)
				ft_printf("declare -x %s=\"%s\"\n", arr[i]->name,
					arr[i]->value);
			else
				ft_printf("declare -x %s\n", arr[i]->name);
		}
		i++;
	}
	free(arr);
}
