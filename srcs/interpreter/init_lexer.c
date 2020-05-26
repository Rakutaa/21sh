/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 14:53:00 by vkuokka           #+#    #+#             */
/*   Updated: 2020/05/26 11:19:47 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static char			*lexer_get_word(t_lexer *lexer)
{
	unsigned int	start;

	start = lexer->i;
	while (lexer->data[lexer->i] && !ft_strchr(SEPARATORS, lexer->data[lexer->i]))
		lexer->i++;
	return (ft_strsub(lexer->data, start, lexer->i - start));
}

static char			*lexer_get_string(t_lexer *lexer, char quote, t_terminal *term)
{
	unsigned int	start;
	char			*str;

	lexer->i++;
	start = lexer->i;
	while (lexer->data[lexer->i] != quote)
	{
		if (!lexer->data[lexer->i])
		{
			ft_putstr("\n> ");
			init_input(term);
			continue ;
		}
		lexer->i++;
	}
	str = ft_strsub(lexer->data, start, lexer->i - start);
	lexer->i++;
	return (str);
}

static t_token		*lexer_create_token(int type, char *value)
{
	t_token			*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->e_type = type;
	token->value = value;
	return (token);
}

static t_token		*lexer_get_token(t_lexer *lexer, t_terminal *term)
{
	t_token			*token;

	if (ft_strchr(OPERATORS, lexer->data[lexer->i]))
	{
		if (lexer->data[lexer->i] == '|')
			token = lexer_create_token(TOKEN_PIPE, ft_strdup("|"));
		else if (lexer->data[lexer->i] == '>')
			token = lexer_create_token(TOKEN_REDIRECT, ft_strdup(">"));
		else if (lexer->data[lexer->i] == '<')
			token = lexer_create_token(TOKEN_REDIRECT, ft_strdup("<"));
		else if (lexer->data[lexer->i] == ';')
			token = lexer_create_token(TOKEN_SEMI, ft_strdup(";"));
		lexer->i++;
		return (token);
	}
	if (lexer->data[lexer->i] == '"')
		return (lexer_create_token(TOKEN_DQUOTE, lexer_get_string(lexer, '"', term)));
	if (lexer->data[lexer->i] == '\'')
		return (lexer_create_token(TOKEN_SQUOTE, lexer_get_string(lexer, '\'', term)));
	return (lexer_create_token(TOKEN_WORD, lexer_get_word(lexer)));
}

void				init_lexer(t_terminal *term)
{
	t_lexer			*lexer;

	lexer = (t_lexer *)malloc(sizeof(t_lexer));
	!lexer ? program_exit(term, 1) : 0;
	lexer->data = term->in->string;
	lexer->i = 0;
	lexer->tokens= ft_lstnew(lexer_get_token(lexer, term), sizeof(t_token));
	while (lexer->data[lexer->i])
	{
		if (ft_isspace(lexer->data[lexer->i]))
			while (lexer->data[lexer->i] && ft_isspace(lexer->data[lexer->i]))
				lexer->i++;
		if (lexer->data[lexer->i])
			ft_lstaddback(&lexer->tokens, ft_lstnew(lexer_get_token(lexer, term), sizeof(t_token)));
	}
	ft_putendl("");
	parse_tokens(term, lexer->tokens);
}
