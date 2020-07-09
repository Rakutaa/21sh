/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtran <vtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 09:59:44 by vkuokka           #+#    #+#             */
/*   Updated: 2020/06/17 13:45:53 by vtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser_ast.h"

t_ast_node		*tokens_to_factor(t_token *head, int i,
t_redirection_aggregation *redir, t_list *env)
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

t_ast_node		*tokens_to_ast_node(t_token *head, t_token *last, t_list *env)
{
	t_token						*tmp;
	t_redirection_aggregation	*redir;
	int							i;

	redir = NULL;
	tmp = head;
	i = 0;
	while (tmp)
	{
		if (tmp->e_type == TOKEN_REDIRECT || tmp->e_type == TOKEN_AGG)
		{
			redir = tokens_to_redirection(tmp, last);
			break ;
		}
		if (tmp == last && (tmp->next || tmp->e_type == TOKEN_SEMI))
			break ;
		i++;
		tmp = move_token_n_times(tmp, 1);
	}
	return (tokens_to_factor(head, i, redir, env));
}

void			tokens_to_parser_node(t_parser_node_list **list,
t_token *head, t_token *last, t_list *env)
{
	t_parser_node				*ast_nodeobj;
	t_parser_node				*token_nodeobj;

	ast_nodeobj = malloc(sizeof(t_parser_node));
	token_nodeobj = NULL;
	ast_nodeobj->e_node = AST;
	ast_nodeobj->nodes.ast_nodeobj = tokens_to_ast_node(head, last, env);
	if ((last->e_type == 3 || last->e_type == 5) && last->next) //tässä
	{
		token_nodeobj = malloc(sizeof(t_parser_node));
		token_nodeobj->e_node = TOKEN;
		token_nodeobj->nodes.token = last;
	}
	add_node_to_parser_node_list(list, ast_nodeobj, token_nodeobj);
}

void			tiger_king_stealing_ur_loot(t_ast *ast, t_parser_node_list *head)
{
	free_ast(ast);
	free_parser(head);
}

void			parse_tokens(t_terminal *term, t_token *tokens)
{
	t_token						*current;
	t_token						*head;
	t_parser_node_list			*nhead;
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
			tokens_to_parser_node(&nhead, head, current, term->env->linked);
			head = move_token_n_times(current, 1);
		}
		current = move_token_n_times(current, 1);
	}
	ast = create_ast_list(nhead);
	execute_ast(ast, term);
	tiger_king_stealing_ur_loot(ast, nhead);
}
