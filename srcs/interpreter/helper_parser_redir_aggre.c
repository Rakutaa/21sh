/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_parser_redir_aggre.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtran <vtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 17:49:53 by vtran             #+#    #+#             */
/*   Updated: 2020/06/10 19:12:15 by vtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_ast.h"

/*
**adding into a simple cmds redirection or aggregation as a linked list
*/

static void							add_redir_aggre_list(
t_redirection_aggregation **list, t_redirection_aggregation *node)
{
	t_redirection_aggregation	*tmp;

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

/*
**previous list node
*/

static t_redirection_aggregation	*create_redir_aggre_node(int type,
t_token *file, t_token *sign)
{
	t_redirection_aggregation	*node;
	char						*str;
	int							i;

	node = malloc(sizeof(t_redirection_aggregation));
	node->e_flag = type == 0 ? 0 : 1;
	if (type == 0)
	{
		node->node.t_redirection.file = file->value;
		node->node.t_redirection.redir = sign->value;
		node->next = NULL;
	}
	else
	{
		str = sign->value;
		i = 0;
		while (str[i] != '<' && str[i] != '>')
			i++;
		node->node.t_ag.n = i == 0 ? NULL : ft_strsub(str, 0, i);
		node->node.t_ag.sign = ft_strsub(str, i, 2);
		i = i + 2;
		node->node.t_ag.word = str[i] == '-' ? ft_strdup("-") :
		ft_strdup(&str[i]);
	}
	return (node);
}

t_redirection_aggregation			*tokens_to_redirection(
t_list *head, t_list *last)
{
	t_token						*sign;
	t_redirection_aggregation	*rhead;

	rhead = NULL;
	while (head && head != last)
	{
		if (get_t_list_token(head)->e_type == TOKEN_REDIRECT)
		{
			add_redir_aggre_list(&rhead, create_redir_aggre_node(0,
			get_t_list_token(head->next), get_t_list_token(head)));
			head = move_t_list_n_times(head, 2);
		}
		else
		{
			add_redir_aggre_list(&rhead,
			create_redir_aggre_node(1, NULL, get_t_list_token(head)));
			head = move_t_list_n_times(head, 1);
		}
	}
	sign = NULL;
	if (last)
		sign = last->content;
	if (sign && sign->e_type == TOKEN_AGG)
		add_redir_aggre_list(&rhead, create_redir_aggre_node(1, NULL, sign));
	return (rhead);
}
