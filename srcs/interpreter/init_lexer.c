/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hege <hege@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 14:53:00 by vkuokka           #+#    #+#             */
/*   Updated: 2020/07/23 01:29:52 by hege             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_ast.h"
#include "lexer.h"

t_lexer				*lexa(t_terminal *term)
{
	t_lexer			*lexer;

	lexer = (t_lexer *)malloc(sizeof(t_lexer));
	!lexer ? program_exit(term, 1) : 0;
	ft_bzero(lexer->data, ARG_MAX);
	ft_strcat(lexer->data, term->in->string);
	lexer->i = 0;
	lexer->tokens = NULL;
	return (lexer);
}

void				get_strange_redirections(int i, t_lexer *lexer)
{
	int		counter;
	char	*str;

	counter = 0;
	str = lexer->data;
	while (ft_isdigit(lexer->data[lexer->i + counter]))
		counter++;
	if (i == 3 || i == 5)
		counter = counter + 1;
	else
		counter = counter + 2;
	add_token(&lexer->tokens,
	create_token(TOKEN_REDIRECT, ft_strsub(str, lexer->i, counter)));
	lexer->i = lexer->i + counter;
}

void				if_is_ag_re_do_ag_re(int i, t_lexer *lexer)
{
	if (i == 0)
		return ;
	if (i == 1 || i == 2)
	{
		lexer->i = lexer->i + 2;
		if (i == 1)
			add_token(&lexer->tokens,
			create_token(TOKEN_REDIRECT, ft_strdup(":>")));
		else
			add_token(&lexer->tokens,
			create_token(TOKEN_REDIRECT, ft_strdup("&>")));
	}
	else if (i > 2 && i < 8)
		get_strange_redirections(i, lexer);
	else
		add_token(&lexer->tokens, get_agr(lexer));
}

void				init_lexer(t_terminal *term)
{
	t_lexer			*lexer;

	lexer = lexa(term);
	while (lexer->data[lexer->i])
	{
		if (ft_isspace(lexer->data[lexer->i]))
		{
			lexer->i++;
			if (lexer->i > 0)
				if_is_ag_re_do_ag_re(is_re_ag(lexer), lexer);
			continue ;
		}
		else
			add_token(&lexer->tokens, get_token(lexer, term));
		if (term->in->sigint)
			break ;
	}
	if (!term->in->sigint && ok_to_parser(lexer->tokens, term))
		parse_tokens(term, lexer);
	free_tokens(lexer->tokens);
	free(lexer);
}
