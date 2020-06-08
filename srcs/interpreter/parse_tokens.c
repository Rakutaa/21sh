/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtran <vtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 09:59:44 by vkuokka           #+#    #+#             */
/*   Updated: 2020/06/02 16:14:16 by vtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser_ast.h"

void	add_redir_aggre_list(t_redirection_aggregation **list, t_redirection_aggregation *node)
{
	t_redirection_aggregation *tmp;

	if (!*list)
		*list = node;
	else
	{
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = node;
	}
}

t_redirection_aggregation	*create_redir_aggre_node(int type, t_token *file, t_token *sign)
{
	t_redirection_aggregation	*node;
	char						*str;
	int							i;

	node = malloc(sizeof(t_redirection_aggregation));
	if (type == 0)
	{
		node->flag = 0;
		node->token.redirection.file = file->value;
		node->token.redirection.redir = sign->value;
		node->next = NULL;
	}
	else 
	{
		node->flag = 1;
		str = sign->value;
		i = 0;
		while (str[i] != '<' && str[i] != '>')
			i++;
		node->token.aggregation.n = i == 0 ? NULL : ft_strsub(str, 0, i);
		node->token.aggregation.sign = ft_strsub(str, i, 2);
		i = i + 2;
		node->token.aggregation.word = str[i] == '-' ? ft_strdup("-") : ft_strdup(&str[i]);
	}
	return node;
}

t_redirection_aggregation	*tokens_to_redirection(t_list *head, t_list *last)
{
	t_token							*sign;
	t_redirection_aggregation		*rhead;

	rhead = NULL;
	while(head && head != last)
	{
		sign = get_t_list_token(head);
		if (sign->e_type == TOKEN_REDIRECT)
		{
			add_redir_aggre_list(&rhead, create_redir_aggre_node(0, get_t_list_token(head->next), sign));
			head = move_t_list_n_times(head, 2);
		}
		else
		{
			add_redir_aggre_list(&rhead, create_redir_aggre_node(1, NULL, sign));
			head = move_t_list_n_times(head, 1);
		}
	}
	sign = NULL;
	if (last)
		sign = last->content;
	if (sign && sign->e_type == TOKEN_AGGRE)
		add_redir_aggre_list(&rhead, create_redir_aggre_node(1, NULL, sign));
	return (rhead);
}

t_ast_node		*tokens_to_factor(t_list *head, int i, t_redirection_aggregation *redir)
{
	char				**cmd;
	int					count;
	t_token				*token;

	count = -1;
	cmd = malloc(sizeof(char *) * i + 1);
	cmd[i] = NULL;
	while (++count < i)
	{
		token = get_t_list_token(head);
		cmd[count] = token->value;
		head = move_t_list_n_times(head, 1);
	}
	return (create_factor(cmd, redir));
}

t_ast_node		*tokens_to_ast_node(t_list *head, t_list *last)
{
	t_list				*tmp;
	t_token				*token;
	t_redirection_aggregation		*redir;
	int					i;

	redir = NULL;
	tmp = head;
	i = 0;
	while (tmp)
	{
		token = get_t_list_token(tmp);
		if (token->e_type == TOKEN_REDIRECT)
		{
			redir = tokens_to_redirection(tmp, last);
			break ;
		}
		if (tmp == last && tmp->next)
			break ;
		i++;
		tmp = move_t_list_n_times(tmp, 1);
	}
	return (tokens_to_factor(head, i, redir));
}

//int type = 3 or 5 meaning pipe or semi 
//e_type 0 or 1 means pipe or semi
//enums in two different structs

void			tokens_to_parser_node(t_parser_node_list **list, t_list *head, t_list *last, int type)
{
	t_parser_node 		*ast_nodeobj;
	t_parser_node 		*token_nodeobj;

	ast_nodeobj = malloc(sizeof(t_parser_node));
	token_nodeobj = NULL;
	ast_nodeobj->node = ast;
	ast_nodeobj->nodes.ast.ast_nodeobj = tokens_to_ast_node(head, last);
	if (type == 3 || type == 5)
	{
		token_nodeobj = malloc(sizeof(t_parser_node));
		token_nodeobj->node = token;
		token_nodeobj->nodes.token.e_type = type == 3 ? 0 : 1;
	}
	add_node_to_parser_node_list(list, ast_nodeobj, token_nodeobj);
}

void			parse_tokens(t_terminal *term, t_list *tokens)
{
	t_list				*current;
	t_list				*head;
	t_token				*content;
	t_parser_node_list	*nhead;
	t_ast				*ast;

	head = tokens;
	current = tokens;
	nhead = NULL;
	while (current)
	{
		content = get_t_list_token(current);
		check_dollar_tilde(term->env, content);
		if (content->e_type == TOKEN_PIPE || content->e_type == TOKEN_SEMI || !current->next)
		{
			tokens_to_parser_node(&nhead, head, current, content->e_type);
			head = move_t_list_n_times(current, 1);
		}
		current = move_t_list_n_times(current, 1);
	}
	ast = create_ast_list(nhead);
	execute_ast(ast);
	}
