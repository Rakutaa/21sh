/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_for_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hege <hege@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 09:59:44 by vkuokka           #+#    #+#             */
/*   Updated: 2020/07/23 01:40:27 by hege             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser_ast.h"

t_free		*init_willy(t_lexer *lexer, t_ast *ast, t_parser_l *parser)
{
	t_free	*willy;

	willy = malloc(sizeof(t_free));
	willy->ast = ast;
	willy->parser = parser;
	willy->lexer = lexer;
	return (willy);
}

void		free_willy(t_free *willy, t_terminal *term)
{
	free_ast(willy->ast);
	free_parser(willy->parser);
	free_tokens(willy->lexer->tokens);
	free(willy->lexer);
	program_exit(term, 0);
}
