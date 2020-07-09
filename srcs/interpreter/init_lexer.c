/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtran <vtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 14:53:00 by vkuokka           #+#    #+#             */
/*   Updated: 2020/06/17 15:25:30 by vtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_ast.h"
#include "lexer.h"



t_lexer				*lexa(t_terminal *term)
{
	t_lexer			*lexer;

	lexer = (t_lexer *)malloc(sizeof(t_lexer));
	!lexer ? program_exit(term, 1) : 0;
	lexer->data = term->in->string;
	lexer->i = 0;
	lexer->tokens = NULL;
	return (lexer);
}

void				init_lexer(t_terminal *term)
{
	t_lexer			*lexer;

	lexer = lexa(term);
	while (lexer->data[lexer->i] && ft_isspace(lexer->data[lexer->i]))
		lexer->i++;
	lexer->tokens = get_token(lexer, term);
	if (!not_pipe_semi_re(lexer))
		return ;
	while (lexer->data[lexer->i])
	{
		if (ft_isspace(lexer->data[lexer->i]))
		{
			while (lexer->data[lexer->i] && ft_isspace(lexer->data[lexer->i]))
				lexer->i++;
			if (is_aggre(lexer))
				add_token(lexer->tokens, get_agr(lexer));
		}
		else if (lexer->data[lexer->i])
			add_token(lexer->tokens, get_token(lexer, term));
	}
	if (ok_to_parser(lexer->tokens, term))
		parse_tokens(term, lexer->tokens);
	free_tokens(lexer->tokens);
	free(lexer);
}
