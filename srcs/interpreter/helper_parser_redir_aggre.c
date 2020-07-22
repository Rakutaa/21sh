/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_parser_redir_aggre.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hege <hege@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 17:49:53 by vtran             #+#    #+#             */
/*   Updated: 2020/07/23 00:16:00 by hege             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_ast.h"

/*
**adding into a simple cmds redirection or aggregation as a linked list
*/

static void							add_redir_aggre_list(
t_re_ag **list, t_re_ag *node)
{
	t_re_ag	*tmp;

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

void								write_heredoc(char *sign,
t_re_ag *node, char *file, t_terminal *term)
{
	if (!ft_strequ(sign, "<<"))
	{
		node->node.t_re.heredoc = NULL;
		return ;
	}
	node->node.t_re.heredoc = malloc(sizeof(int) * 2);
	pipe(node->node.t_re.heredoc);
	while (1)
	{
		init_input(term->in);
		ft_memmove(term->in->prompt, HEREDOC, 4);
		start_editor(term);
		ft_putchar('\n');
		if (ft_strequ(term->in->string, file))
			break ;
		ft_putendl_fd(term->in->string, node->node.t_re.heredoc[1]);
	}
	close(node->node.t_re.heredoc[1]);
}

static t_re_ag	*create_redir_aggre_node(int type,
t_token *file, t_token *sign, t_terminal *term)
{
	t_re_ag	*node;
	int							i;

	node = malloc(sizeof(t_re_ag));
	node->e_flag = type == 0 ? 0 : 1;
	if (type == 0)
	{
		node->node.t_re.file = file->value;
		node->node.t_re.redir = sign->value;
		write_heredoc(sign->value, node, file->value, term);
	}
	else
	{
		i = 0;
		while (sign->value[i] != '<' && sign->value[i] != '>')
			i++;
		node->node.t_ag.n = i == 0 ? NULL : ft_strsub(sign->value, 0, i);
		node->node.t_ag.sign = ft_strsub(sign->value, i, 2);
		i = i + 2;
		node->node.t_ag.word = sign->value[i] == '-' ? ft_strdup("-") :
		ft_strdup(&sign->value[i]);
	}
	node->next = NULL;
	return (node);
}

t_re_ag			*tokens_to_redirection(
t_token *head, t_token *last, t_terminal *term)
{
	t_re_ag	*rhead;

	rhead = NULL;
	while (head && head != last)
	{
		if (head->e_type == TOKEN_REDIRECT)
		{
			add_redir_aggre_list(&rhead, create_redir_aggre_node(0,
			head->next, head, term));
			head = move_token_n_times(head, 2);
		}
		else
		{
			add_redir_aggre_list(&rhead,
			create_redir_aggre_node(1, NULL, head, term));
			head = move_token_n_times(head, 1);
		}
	}
	if (last && last->e_type == TOKEN_AGG)
		add_redir_aggre_list(&rhead,
		create_redir_aggre_node(1, NULL, last, term));
	return (rhead);
}
