/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clipboard.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 22:51:44 by vkuokka           #+#    #+#             */
/*   Updated: 2020/06/26 15:20:25 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "halfsh.h"
#include "keyboard.h"
#include "parser_ast.h"

/*
** The paste is appended to the current command from the cursor
** position. The command contents are moved to the right by ret value
** so the second memmove does not overwrite any important data.
*/

static void add_paste(t_input *input, char *paste, int ret)
{
	ft_memmove(input->string + input->index + ret, \
	input->string + input->index, ft_strlen(input->string) + input->index);
	ft_memmove(input->string + input->index, paste, ret);
	input->index += ret;
}

/*
** Fetches clipboard contents using pbpaste command.
** read functions third parameter makes sure that the
** end result does not exceed the ARG_MAX and end up in
** segmentation fault in add_paste function.
*/

static void	paste_clipboard(t_terminal *term)
{
	char	*cmd[] = {"pbpaste", NULL};
	pid_t	pid;
	int		p[2];
	char	paste[ARG_MAX];
	int		ret;

	pipe(p);
	pid = fork();
	if (!pid)
	{
		dup2(p[1], 1);
		close(p[0]);
		execvp(cmd[0], cmd);
	}
	else
	{
		wait(&pid);
		close(p[1]);
		ret = read(p[0], paste, ARG_MAX - ft_strlen(term->in->string));
		paste[ret] = '\0';
		add_paste(term->in, paste, ret);
		close(p[0]);
	}
}

/*
** Copies contents of the current command to the clipboard.
*/

static void	copy_clipboard(t_terminal *term)
{
	t_ast_node	*ex;
	t_ast		*head;
	char		*echon[] = {"echo", "-n", term->in->string, NULL};
	char		*copyn[] = {"pbcopy", NULL};

	head = init_ast();
	ex = create_expression(create_factor(echon, NULL), \
	create_factor(copyn, NULL));
	head->parent = ex;
	execute_ast(head);
}

/*
** Copies contents of the current command to the clipboard and
** clears current command.
*/

static void	cut_clipboard(t_terminal *term)
{
	t_ast_node	*ex;
	t_ast		*head;
	char		*echon[] = {"echo", "-n", term->in->string, NULL};
	char		*copyn[] = {"pbcopy", NULL};

	head = init_ast();
	ex = create_expression(create_factor(echon, NULL), \
	create_factor(copyn, NULL));
	head->parent = ex;
	execute_ast(head);
	ft_bzero(term->in->string, ARG_MAX);
	term->in->index = 0;
}

void		clipboard(t_terminal *term, int sum)
{
	if (sum == OPT_C)
		copy_clipboard(term);
	else if (sum == OPT_X)
		cut_clipboard(term);
	else if (sum == OPT_V)
		paste_clipboard(term);
}
