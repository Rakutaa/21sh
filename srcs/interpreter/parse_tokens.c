/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hege <hege@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 09:59:44 by vkuokka           #+#    #+#             */
/*   Updated: 2020/07/23 00:26:18 by hege             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser_ast.h"

t_ast_n		*tokens_to_factor(t_token *head, int i,
t_re_ag *redir, t_list *env)
{
	char						**cmd;
	int							count;

	count = -1;
	cmd = (char **)malloc(sizeof(char *) * (i + 1));
	cmd[i] = NULL;
	while (++count < i)
	{
		cmd[count] = head->value;
		head = move_token_n_times(head, 1);
	}
	return (create_factor(cmd, redir, env));
}

t_ast_n		*tokens_to_ast_node(t_token *head, t_token *last,
t_list *env, t_terminal *term)
{
	t_token						*tmp;
	t_re_ag	*redir;
	int							i;

	redir = NULL;
	tmp = head;
	i = 0;
	while (tmp)
	{
		if (tmp->e_type == TOKEN_REDIRECT || tmp->e_type == TOKEN_AGG)
		{
			redir = tokens_to_redirection(tmp, last, term);
			break ;
		}
		if (tmp == last && (tmp->next || tmp->e_type == TOKEN_SEMI))
			break ;
		i++;
		tmp = move_token_n_times(tmp, 1);
	}
	return (tokens_to_factor(head, i, redir, env));
}

void			tokens_to_parser_node(t_parser_l **list,
t_token *head, t_token *last, t_terminal *term)
{
	t_parser_n				*ast_nodeobj;
	t_parser_n				*token_nodeobj;

	ast_nodeobj = malloc(sizeof(t_parser_n));
	token_nodeobj = NULL;
	ast_nodeobj->e_node = AST;
	ast_nodeobj->nodes.ast_nodeobj =
	tokens_to_ast_node(head, last, term->env->linked, term);
	if ((last->e_type == 3 || last->e_type == 5) && last->next)
	{
		token_nodeobj = malloc(sizeof(t_parser_n));
		token_nodeobj->e_node = TOKEN;
		token_nodeobj->nodes.token = last;
	}
	add_node_to_parser_node_list(list, ast_nodeobj, token_nodeobj);
}

void			tiger_king_stealing_ur_loot(t_ast *ast,
t_parser_l *head)
{
	free_ast(ast);
	free_parser(head);
}

void			parse_tokens(t_terminal *term, t_token *tokens)
{
	t_token						*current;
	t_token						*head;
	t_parser_l			*nhead;
	t_ast						*ast;

	head = tokens;
	current = tokens;
	nhead = NULL;
	while (current)
	{
		check_dollar_tilde(term->env->linked, current);
		if (current->e_type == TOKEN_PIPE || current->e_type == TOKEN_SEMI ||
		!current->next)
		{
			tokens_to_parser_node(&nhead, head, current, term);
			head = move_token_n_times(current, 1);
		}
		current = move_token_n_times(current, 1);
	}
	ast = create_ast_list(nhead);
	execute_ast(ast, term);
	tiger_king_stealing_ur_loot(ast, nhead);
}
