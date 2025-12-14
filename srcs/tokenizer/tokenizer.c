/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maanguit <maanguit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 22:29:57 by maanguit          #+#    #+#             */
/*   Updated: 2025/12/14 03:18:50 by maanguit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/tokenizer.h"

void	add_last_token(t_token_list **tokens, t_token_list *new_token)
{
	t_token_list	*tmp;

	if (!tokens || !*tokens)
	{
		*tokens = new_token;
		return ;
	}
	tmp = *tokens;
	while (tmp && tmp->next)
		tmp = tmp->next;
	tmp->next = new_token;
}

void	add_token_to_list(t_token_list **tokens, char *str, int type)
{
	t_token_list	*new_token;

	new_token = malloc(sizeof(t_token_list));
	if (!new_token)
	{
		free_tokens(*tokens);
		perror("malloc error");
		exit(1);
	}
	new_token->type = type;
	new_token->str = str;
	new_token->next = NULL;
	add_last_token(tokens, new_token);
}

/*
añade al final de la lista un nuevo nodo que contiene la información
de qué tipo de token es, el string del token y la dirección del siguiente nodo
*/
void	add_token(t_token_list **tokens, char *str)
{
	char	*token_str;
	int		type;
	int		i;

	i = 0;
	type = which_operator(str);
	if (type == WORD)
	{
		while (str[i] != ' ' && which_operator(str + i) == WORD)
			i++;
		token_str = ft_substr(str, 0, i);
	}
	else if (type <= 4)
		token_str = ft_substr(str, 0, 2);
	else
		token_str = ft_substr(str, 0, 1);
	if (!token_str)
	{
		free_tokens(*tokens);
		perror("malloc error");
		exit(1);
	}
	add_token_to_list(tokens, token_str, type);
}

void	add_quotes(t_token_list **tokens, char *str)
{
	char	*string;
	char	quote;
	int		type;
	int		len;

	quote = *str;
	str++;
	len = 0;
	while (str[len] != quote)
		len++;
	if (len == 0)
		return ;
	if (quote == '\"')
		type = DOUBLE_QUOTE;
	else
		type = SINGLE_QUOTE;
	string = ft_substr(str, 0, len);
	if (!string)
	{
		free_tokens(*tokens);
		perror("malloc error");
		exit(1);
	}	
	add_token_to_list(tokens, string, type);
}

/*
esta función crea una lista enlazada en la cual cada nodo contiene
un string, el tipo de token y la dirección del siguiente nodo
*/
int	tokenize(char *line, t_token_list **tokens)
{
	if (!valid_quotes(line))//también se debe comprobar si los paréntesis son inválidos
		return (write(2, "Invalid quotes\n", 15), 0);
	if (*line == ' ')
		line = iter_line(line);
	while (line && *line)
	{
		if (*line == '\"' || *line == '\'')
			add_quotes(tokens, line);
		else if (which_operator(line) != WORD)
			add_token(tokens, line);
		else
			add_token(tokens, line);
		line = iter_line(line);
	}
	return (1);
}

/*int main(int ac, char **av)
{
	t_token_list	*tokens;

	if (ac < 1)
		return (1);
	tokens = NULL;
	tokenize(av[1], &tokens);
	print_tokens(tokens);
	return (0);
}
*/