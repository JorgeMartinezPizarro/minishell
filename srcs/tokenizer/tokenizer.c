/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maanguit <maanguit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 22:29:57 by maanguit          #+#    #+#             */
/*   Updated: 2025/12/25 17:11:40 by maanguit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/tokenizer.h"

void	add_last_token(t_tokens **tokens, t_tokens *new_token)
{
	t_tokens	*tmp;

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

void	add_token_to_list(t_tokens **tokens, char *str, int type)
{
	t_tokens	*new_token;

	new_token = malloc(sizeof(t_tokens));
	if (!new_token)
	{
		free_tokens(*tokens);
		perror("malloc error");
		exit(1);
	}
	new_token->type = type;
	new_token->str = ft_strdup(str);
	new_token->next = NULL;
	add_last_token(tokens, new_token);
}

int	count_word_len(char *str)
{
	char	quote;
	int		len;

	len = 0;
	quote = 0;
	while (quote || (str[len] != ' '
		&& which_operator(str + len) == T_WORD))
	{
		if (!quote && (str[len] == '\"' || str[len] == '\''))
			quote = str[len];
		else if (quote && str[len] == quote)
			quote = 0;
		len++;
	}
	return (len);
}

/*
añade al final de la lista un nuevo nodo que contiene la información
de qué tipo de token es, el string del token y la dirección del siguiente nodo
*/
void	add_token(t_tokens **tokens, char *str)
{
	char	*token_str;
	int		type;
	int		len;

	len = 0;
	type = which_operator(str);
	if (type == T_WORD)
		len = count_word_len(str);
	else if (type <= 4)
		len = 2;
	else
		len = 1;
	token_str = ft_substr(str, 0, len);
	if (!token_str)
	{
		free_tokens(*tokens);
		perror("malloc error");
		exit(1);
	}
	add_token_to_list(tokens, token_str, type);
	free(token_str);
}

/*
esta función crea una lista enlazada en la cual cada nodo contiene
un string, el tipo de token y la dirección del siguiente nodo
*/
int	tokenize(char *line, t_tokens **tokens)
{
	if (!valid_quotes(line) || !valid_paren(line))
		return (write(2, "Invalid quotes\n", 15), 0);
	if (*line == ' ')
		line = iter_line(line);
	while (line && *line)
	{
		add_token(tokens, line);
		line = iter_line(line);//revisar
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