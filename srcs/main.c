/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 18:59:01 by vkuokka           #+#    #+#             */
/*   Updated: 2020/07/13 13:53:29 by vkuokka          ###   ########.fr       */
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

static void		copy_enviroment(t_terminal *term, char **env)
{
	size_t		i;
	t_list		*start;
	t_list		*node;
	
//	start = (t_list *)malloc(sizeof(t_list));
	term->env = (t_env *)malloc(sizeof(t_env));
	i = 0;
	start = NULL;
	while (env[i])
	{
		node = ft_lstnew(env[i], ft_strlen(env[i]) + 1);
		!node ? program_exit(term, 1) : 0;
		*ft_strchr(node->content, '=') = '\0';
		!start ? start = node : ft_lstaddback(&start, node);
		i++;
	}
	term->env->linked = start;
	term->env->table = update_enviroment(term->env->linked);
}

/*
** This is the "core" part of the program. It allocates memory for the input
** struct which keeps the information about the current command and cursor
** positon.
*/

static void		cut_tail(t_terminal *term)
{
	t_dlist		*tmp;

	if (!term->h_tail)
		return ;
	tmp = term->h_tail;
	term->h_tail = term->h_tail->prev;
	term->h_tail->next = NULL;
	ft_ddel(tmp->content, tmp->content_size);
	free(tmp);
}

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
			init_lexer(term);
			ft_dlstadd(&term->h_head, ft_dlstnew(term->in->string, \
			ft_strlen(term->in->string) + 1));
			if (!term->h_tail)
				term->h_tail = term->h_head;
			if (ft_dlstlen(&term->h_head) > HISTSIZE)
				cut_tail(term);
		}
	}
}


/*
** Configurates termcaps and allocates memory for term struct. 
** The program should always return to main function if the exit
** is done without errors. Termcaps `ti' command puts the terminal
** into whatever special modes are needed or appropriate for programs
** that move the cursor nonsequentially around the screen and `ho'
** moves the cursor to the upper left corner of the screen.
*/

/*
**env pitää muuttaa t_env muotoon.
*/

void			close_fd()
{
	int i = 3;

	while (i < 43)
	{
		close(i);
		i++;
	}
}

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
		//tputs(tgetstr("ti", NULL), 1, print_char); //Screws up text editors
		tputs(tgetstr("ho", NULL), 1, print_char);
		init_history(term);
		print_banner();
		command_line(term);
		save_history(term);
	}
	program_exit(term, 0);
}
