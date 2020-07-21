/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 18:59:01 by vkuokka           #+#    #+#             */
/*   Updated: 2020/07/21 13:12:09 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "halfsh.h"
#include "lexer.h"

static void		print_banner(void)
{
	tputs(tgetstr("cl", NULL), 1, print_char);
	ft_putendl(" _____  __      _          _ _");
	ft_putendl("/ __  \\/  |    | |        | | |");
	ft_putendl("   / /  | | ___| |__   ___| | |");
	ft_putendl("  / /   | |/ __|  _ \\ / _ \\ | |");
	ft_putendl(" / /____| |\\__ \\ | | |  __/ | |");
	ft_putendl("\\_____/\\___/___/_| |_|\\___|_|_|");
	ft_putchar('\n');
}

/*
** Adds node into history doubly list and cuts the tail
** if history length exceeds HISTSIZE defined in header.
*/

static void		add_history(t_terminal *term)
{
	t_dlist		*tmp;

	ft_dlstadd(&term->h_head, ft_dlstnew(term->in->string, \
	ft_strlen(term->in->string) + 1));
	if (!term->h_tail)
		term->h_tail = term->h_head;
	if (ft_dlstlen(&term->h_head) > HISTSIZE)
	{
		if (!term->h_tail)
			return ;
		tmp = term->h_tail;
		term->h_tail = term->h_tail->prev;
		term->h_tail->next = NULL;
		ft_ddel(tmp->content, tmp->content_size);
		free(tmp);
	}
}

/*
** This is the "core" part of the program. It allocates memory for the input
** struct which keeps the information about the current command and cursor
** positon.
*/

static void		command_line(t_terminal *term)
{
	term->in = (t_input *)malloc(sizeof(t_input));
	!term->in ? program_exit(term, 1) : 0;
	while (term)
	{
		term->h_current = NULL;
		init_input(term->in);
		start_editor(term);
		ft_putchar('\n');
		if (term->in->string[0] && !term->in->sigint)
		{
			if (ft_strequ(term->in->string, "exit"))	// DELETE
				return ;								// DELETE
			if (isatty(STDIN_FILENO))
				add_history(term);
			init_lexer(term);
		}
	}
}

/*
** env pitää muuttaa t_env muotoon.
// What is this and what is it doing in my backyard???
*/

void			close_fd(void)
{
	int			i;

	i = 3;
	while (i < 43)
	{
		close(i);
		i++;
	}
}

/*
** Configurates termcaps and allocates memory for term struct.
** The program should always return to main function if the exit
** is done without errors. Termcaps command `ho' moves the cursor
** to the upper left corner of the screen.
*/

int				main(int argc, char **argv, char **env)
{
	t_terminal	*term;

	(void)argc;
	(void)argv;
	term = (t_terminal *)malloc(sizeof(t_terminal));
	!term ? program_exit(term, 1) : 0;
	ft_bzero(term->clipboard, ARG_MAX);
	copy_enviroment(term, env);
	term->in = NULL;
	term->h_head = NULL;
	term->h_tail = NULL;
	if (!isatty(STDIN_FILENO))
		execute_pipe(term);
	else
	{
		config_termcaps();
		tputs(tgetstr("ho", NULL), 1, print_char);
		init_history(term);
		print_banner();
		command_line(term);
		save_history(term);
	}
	program_exit(term, 0);
}
