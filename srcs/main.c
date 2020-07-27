/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 18:59:01 by vkuokka           #+#    #+#             */
/*   Updated: 2020/07/27 14:47:21 by vkuokka          ###   ########.fr       */
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

static void		program_loop(t_terminal *term)
{
	term->in = (t_input *)malloc(sizeof(t_input));
	!term->in ? program_exit(term, 1) : 0;
	while (term)
	{
		term->h_current = NULL;
		init_input(term->in);
		start_editor(term);
		if (term->in->sigeof)
			break ;
		ft_putchar('\n');
		if (term->in->string[0] && !term->in->sigint)
		{
			if (isatty(STDIN_FILENO))
				add_history(term);
			init_lexer(term);
		}
	}
}

int				main(int argc, char **argv, char **env)
{
	t_terminal	*term;

	(void)argc;
	(void)argv;
	config_termcaps();
	term = (t_terminal *)malloc(sizeof(t_terminal));
	!term ? program_exit(term, 1) : 0;
	ft_bzero(term->clipboard, ARG_MAX);
	copy_enviroment(term, env);
	term->in = NULL;
	init_history(term);
	tputs(tgetstr("ho", NULL), 1, print_char);
	print_banner();
	program_loop(term);
	program_exit(term, 0);
	return (0);
}
