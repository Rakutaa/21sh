/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_ag_dub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hege <hege@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 18:02:46 by vtran             #+#    #+#             */
/*   Updated: 2020/07/23 00:16:00 by hege             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_ast.h"

void		n_redirection(t_ast **ast, char *file, char *redir)
{
	int							n;
	int							i;

	i = 0;
	n = ft_atoi(redir);
	while (ft_isdigit(redir[i]))
		i++;
	if (redir[i] == '>')
	{
		if ((*ast)->out != 1)
			close((*ast)->out);
		(*ast)->out = open(file, O_WRONLY | O_CREAT | (redir[i + 1] == '\0' ?
		O_TRUNC : O_APPEND), S_IRUSR | S_IRGRP | S_IROTH | S_IWGRP | S_IWUSR);
		dup2((*ast)->out, n);
		close((*ast)->out);
	}
	else if (redir[i] == '<' && redir[i + 1] == '>')
	{
		(*ast)->rwfd = open(file, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR |
		S_IRGRP | S_IROTH | S_IWGRP | S_IWUSR);
		dup2((*ast)->rwfd, n);
		close((*ast)->rwfd);
	}
}

void		and_greater(t_ast **ast, char *file)
{
	if ((*ast)->out != 1)
		close((*ast)->out);
	(*ast)->out = open(file, O_WRONLY | O_CREAT |
	O_TRUNC, S_IRUSR | S_IRGRP | S_IROTH | S_IWGRP | S_IWUSR);
	dup2((*ast)->out, 1);
	dup2((*ast)->out, 2);
	close((*ast)->out);
}

void		greater_and_double(t_ast **ast, char *file, char *redir)
{
	if ((*ast)->out != 1)
		close((*ast)->out);
	(*ast)->out = open(file, O_WRONLY | O_CREAT | (redir[1] == '\0' ?
	O_TRUNC : O_APPEND), S_IRUSR | S_IRGRP | S_IROTH | S_IWGRP | S_IWUSR);
	dup2((*ast)->out, 1);
	close((*ast)->out);
}

void		less_than(t_ast **ast, char *file)
{
	if ((*ast)->in != 0)
		close((*ast)->in);
	(*ast)->in = open(file, O_RDONLY);
	dup2((*ast)->in, 0);
	close((*ast)->in);
}

void		heredoc(t_ast **ast, t_re_ag *node)
{
	if ((*ast)->in != 0)
		close((*ast)->in);
	(*ast)->in = node->node.t_re.heredoc[0];
	dup2((*ast)->in, 0);
	close((*ast)->in);
	close((node->node.t_re.heredoc[1]));
}
