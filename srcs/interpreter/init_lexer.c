/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 14:53:00 by vkuokka           #+#    #+#             */
/*   Updated: 2020/06/12 17:29:34 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static char			*get_word(t_lexer *lexer)
{
	unsigned int	start;

	start = lexer->i;
	while (lexer->data[lexer->i] \
	&& !ft_strchr(SEPARATORS, lexer->data[lexer->i]))
		lexer->i++;
	return (ft_strsub(lexer->data, start, lexer->i - start));
}

static char			*get_string(t_lexer *lexer, char quote, t_terminal *term)
{
	unsigned int	start;
	char			*str;

	lexer->i++;
	start = lexer->i;
	while (lexer->data[lexer->i] != quote)
	{
		if (!lexer->data[lexer->i])
		{
			ft_memmove(term->in->prompt, FILL, 3);
			ft_putchar('\n');
			init_input(term);
			continue ;
		}
		lexer->i++;
	}
	str = ft_strsub(lexer->data, start, lexer->i - start);
	lexer->i++;
	return (str);
}

static t_token		*create_token(int type, char *value)
{
	t_token			*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->e_type = type;
	token->value = value;
	return (token);
}

t_token				*redirection(t_lexer *lexer)
{
	if (lexer->data[lexer->i] == '>')
	{
		if (lexer->data[lexer->i + 1] == '>')
		{
			lexer->i = lexer->i + 1;
			return create_token(TOKEN_REDIRECT, ft_strdup(">>"));
		}
		return create_token(TOKEN_REDIRECT, ft_strdup(">"));
	}
	else
	{
		if (lexer->data[lexer->i + 1] == '<')
		{
			lexer->i = lexer->i + 1;
			return create_token(TOKEN_REDIRECT, ft_strdup("<<"));
		}
		return create_token(TOKEN_REDIRECT, ft_strdup("<"));
	}
}

static t_token		*get_token(t_lexer *lexer, t_terminal *term)
{
	t_token			*token;

	token = NULL;
	if (ft_strchr(OPERATORS, lexer->data[lexer->i]))
	{
		if (lexer->data[lexer->i] == '|')
			token = create_token(TOKEN_PIPE, ft_strdup("|"));
		else if (lexer->data[lexer->i] == '>' || lexer->data[lexer->i] == '<')
			token = redirection(lexer);
		else if (lexer->data[lexer->i] == ';')
			token = create_token(TOKEN_SEMI, ft_strdup(";"));
		lexer->i++;
		return (token);
	}
	if (lexer->data[lexer->i] == '"')
		return (create_token(TOKEN_DQUOTE, get_string(lexer, '"', term)));
	if (lexer->data[lexer->i] == '\'')
		return (create_token(TOKEN_SQUOTE, get_string(lexer, '\'', term)));
	return (create_token(TOKEN_WORD, get_word(lexer)));
}

int is_aggre(t_lexer *lexer)
{
	int i;
	char *str;

	i = lexer->i;
	str = lexer->data;
	while(ft_isdigit(str[i]))
		i++;
	if (str[i] != '<' && str[i] != '>')
		return 0;
	i++;
	if (str[i] != '&')
		return 0;
	i++;
	if (str[i] != '-' && !ft_isdigit(str[i]))
		return 0;
	if (str[i] == '-' && (!str[i + 1] || str[i + 1] == ' ' || str[i + 1] == ';' || str[i + 1] == '|'))
		return 1;
	while (ft_isdigit(str[i]))
		i++;
	if ((!str[i] || str[i] == ' ' || str[i] == ';' || str[i] == '|'))
		return 1;
	return 0;
}

static t_token		*get_agr(t_lexer *lexer)
{
	int i;
	int counter;
	char *str;

	i = lexer->i;
	counter = i;
	str = lexer->data;
	while(ft_isdigit(str[i]))
		i++;
	i = i + 2;
	if (str[i] == '-')
	{
		i++;
		lexer->i = i;
		return create_token(TOKEN_AGGRE, ft_strsub(str, counter, i - counter));
	}
	while (ft_isdigit(str[i]))
		i++;
	lexer->i = i;
	return create_token(TOKEN_AGGRE, ft_strsub(str, counter, i - counter));
}

void				init_lexer(t_terminal *term)
{
	t_lexer			*lexer;

	lexer = (t_lexer *)malloc(sizeof(t_lexer));
	!lexer ? program_exit(term, 1) : 0;
	lexer->data = term->in->string;
	lexer->i = 0;
	lexer->tokens = ft_lstnew(get_token(lexer, term), sizeof(t_token));
	while (lexer->data[lexer->i])
	{
		if (ft_isspace(lexer->data[lexer->i]))
		{
			while (lexer->data[lexer->i] && ft_isspace(lexer->data[lexer->i]))
				lexer->i++;
			if (is_aggre(lexer))
				ft_lstaddback(&lexer->tokens, \
				ft_lstnew(get_agr(lexer), sizeof(t_token)));
		}
		else if (lexer->data[lexer->i])
			ft_lstaddback(&lexer->tokens, \
			ft_lstnew(get_token(lexer, term), sizeof(t_token)));
	}
	ft_putendl("");
	parse_tokens(term, lexer->tokens);
}
