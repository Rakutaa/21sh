/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtran <vtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 23:58:05 by hege              #+#    #+#             */
/*   Updated: 2020/07/24 16:07:22 by vtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int			check_syntax_error(int i, int j)
{
	if ((j == 5 || i == 5))
		if ((j == 5 && i == 5) || j == 3 || j == 4 || i == 3 || i == 4)
			return (1);
	if ((j == 3 || i == 3) && (j == 4 || i == 4))
		return (1);
	if (j == 3 && i == 3)
		return (1);
	return (0);
}

int			syntax_error(int i, int j)
{
	if (i == 5 && j == 5)
		ft_printf("21: unexpected syntax error close to keyword \";;\"\n");
	else if (j == 5)
		ft_printf("21: unexpected syntax error close to keyword \";\"\n");
	else if (j == 3)
		ft_printf("21: unexpected syntax error close to keyword \"|\"\n");
	else
		ft_printf("21: unexpected syntax error close to keyword \"nl\"\n");
	return (0);
}

static int	end_with_pipe(t_terminal *term)
{
	ft_memmove(term->in->prompt, PIPE, 3);
	start_editor(term);
	init_lexer(term);
	return (0);
}

int			not_pipe_semi_re(t_lexer *lexer)
{
	t_token			*token;

	token = lexer->tokens;
	if (token->e_type == TOKEN_PIPE || token->e_type == TOKEN_SEMI ||
	token->e_type == TOKEN_REDIRECT)
	{
		free_tokens(lexer->tokens);
		free(lexer);
		return (syntax_error(0, token->e_type));
	}
	return (1);
}

int			ok_to_parser(t_token *tokens, t_terminal *term)
{
	t_token *token;
	t_token *token_next;

	token_next = NULL;
	if (tokens->e_type == 3 || tokens->e_type == 4 || tokens->e_type == 5)
		return (syntax_error(0, tokens->e_type));
	while (tokens->next)
	{
		token = tokens;
		token_next = tokens->next;
		if (token_next)
		{
			if (check_syntax_error(token->e_type, token_next->e_type))
				return (syntax_error(token->e_type, token_next->e_type));
		}
		tokens = tokens->next;
	}
	if (token_next && token_next->e_type == TOKEN_SEMI)
	{
		free_tokens(tokens);
		token->next = NULL;
	}
	if (token_next && token_next->e_type == TOKEN_PIPE)
		return (end_with_pipe(term));
	return (1);
}
