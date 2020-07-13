/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtran <vtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 18:59:01 by vkuokka           #+#    #+#             */
/*   Updated: 2020/06/17 13:51:01 by vtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "halfsh.h"
#include "lexer.h"

static void		print_banner(void)
{
	ft_putendl(" _____  __      _          _ _");
	ft_putendl("/ __  \\/  |    | |        | | |");
	ft_putendl("   / /  | | ___| |__   ___| | |");
	ft_putendl("  / /   | |/ __|  _ \\ / _ \\ | |");
	ft_putendl(" / /____| |\\__ \\ | | |  __/ | |");
	ft_putendl("\\_____/\\___/___/_| |_|\\___|_|_|");
	ft_putendl("Use at your own risk!");
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
** positon. The while loop takes care of multiple essential things:
** 1. Initializes the input struct.
** 2. Starts the line editor.
** 3. In case of the command being empty string, skips lexing and history.
** 4. Starts lexer.
** 5. Pushes the command into history.
*/

static void		command_line(t_terminal *term)
{
	term->in = (t_input *)malloc(sizeof(t_input));
	!term->in ? program_exit(term, 1) : 0;
	while (term)
	{
		init_input(term->in);
		start_editor(term);
		if (term->in->string[0])
		{
			if (ft_strequ(term->in->string, "exit"))
				return ;
			init_lexer(term);
			ft_lstadd(&term->history, ft_lstnew(term->in->string, \
			ft_strlen(term->in->string)));
		}
		else
			ft_putchar('\n');
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
	config_termcaps();
	tputs(tgetstr("ti", NULL), 1, print_char);
	tputs(tgetstr("ho", NULL), 1, print_char);
	term = (t_terminal *)malloc(sizeof(t_terminal));
	!term ? program_exit(term, 1) : 0;
	copy_enviroment(term, env);
	term->in = NULL;
	term->history = NULL;
	print_banner();
	close_fd();
	command_line(term);
	program_exit(term, 0);
}
