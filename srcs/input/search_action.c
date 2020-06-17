/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_action.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 11:09:33 by vkuokka           #+#    #+#             */
/*   Updated: 2020/06/17 18:16:28 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "halfsh.h"
#include "keyboard.h"
#include "parser_ast.h"

/*
** Deletes character from the command by shifting bytes after the index
** to the left once. The byte after the last character is initialized
** to zero after memmove.
*/

static void	delete_char(t_terminal *term)
{
	size_t	len;

	if (term->in->index > 0)
	{
		len = ft_strlen(term->in->string);
		term->in->index--;
		ft_memmove(term->in->string + term->in->index, \
		term->in->string + term->in->index + 1, \
		ft_strlen(term->in->string + term->in->index + 1));
		term->in->string[len - 1] = 0;
	}
}

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
	if (!(pid = fork()))
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
** Chooses right action by comparing sum and different
** definitions from keyboard.h file.
*/

void		search_action(t_terminal *term, int sum)
{
	if (sum == LEFT || sum == RIGHT \
	|| sum == CTRL_LEFT || sum == CTRL_RIGHT)
		cursor_movement_1(term, sum);
	else if (sum == CTRL_UP || sum == CTRL_DOWN \
	|| sum == HOME || sum == END)
		cursor_movement_2(term, sum);
	else if (sum == UP || sum == DOWN)
		browse_history(term, sum);
	else if (sum == BACK)
		delete_char(term);
	else if (sum == COPY)
		copy_clipboard(term);
	else if (sum == PASTE)
		paste_clipboard(term);
}
