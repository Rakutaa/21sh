/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_ag.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hege <hege@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 18:02:46 by vtran             #+#    #+#             */
/*   Updated: 2020/07/23 00:16:00 by hege             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_ast.h"

void		do_redirection(t_ast **ast, t_re_ag *node)
{
	char						*file;
	char						*redir;

	file = node->node.t_re.file;
	redir = node->node.t_re.redir;
	if (ft_isdigit(redir[0]))
		n_redirection(ast, file, redir);
	if (redir[0] == '&')
		and_greater(ast, file);
	if (redir[0] == '>')
		greater_and_double(ast, file, redir);
	if (redir[0] == '<' && !redir[1])
		less_than(ast, file);
	if (redir[0] == '<' && redir[1] == '<' && !redir[2])
		heredoc(ast, node);
	if (redir[0] == '<' && redir[1] == '>')
		less_greater_than(ast, file);
}

void		bad_fd(char *str)
{
	ft_printf("21sh bad fd, %s\n", str);
	close(2);
}

void		do_aggregaation(t_re_ag *node)
{
	if (node->node.t_ag.sign[0] == '<')
	{
		if (node->node.t_ag.word[0] == '-')
			close(!node->node.t_ag.n ? 0 :
			ft_atoi(node->node.t_ag.n));
		else
			dup2(ft_atoi(node->node.t_ag.word),
			!node->node.t_ag.n ? 1 : ft_atoi(node->node.t_ag.n));
	}
	else
	{
		if (node->node.t_ag.word[0] == '-')
			close(!node->node.t_ag.n ? 1 : ft_atoi(node->node.t_ag.n));
		else
		{
			if (fcntl(ft_atoi(node->node.t_ag.word), F_GETFL) == -1)
				bad_fd(node->node.t_ag.word);
			else
				dup2(ft_atoi(node->node.t_ag.word), !node->node.t_ag.n ?
				1 : ft_atoi(node->node.t_ag.n));
		}
	}
}

/*
**doing adding redirection or aggregation if some
*/

void		visit_re_ag(t_ast_n *obj, t_ast **ast)
{
	t_re_ag	*head;

	head = obj->nodes.t_factor.list;
	while (head)
	{
		if (head->e_flag == 0)
			do_redirection(ast, head);
		else
			do_aggregaation(head);
		head = head->next;
	}
}
