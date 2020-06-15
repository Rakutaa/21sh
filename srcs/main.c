/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 18:59:01 by vkuokka           #+#    #+#             */
/*   Updated: 2020/06/15 16:51:28 by vkuokka          ###   ########.fr       */
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
}

static t_list	*copy_enviroment(t_terminal *term, char **env)
{
	size_t		i;
	size_t		len;
	t_list		*start;
	t_list		*node;

	i = 0;
	start = NULL;
	while (env[i])
	{
		len = ft_strlen(env[i]);
		node = ft_lstnew(env[i], len + 1);
		!node ? program_exit(term, 1) : 0;
		*ft_strchr(node->content, '=') = '\0';
		!start ? start = node : ft_lstaddback(&start, node);
		i++;
	}
	return (start);
}

/*
** This is the "core" part of the program. It allocates memory for the input
** struct which keeps the information about the current command and cursor
** positon. The while loop takes care of multiple essential things:
** 1. Clears the current command.
** 2. Starts the "command input".
** 3. In case of the command being empty string, skips lexing and history.
** 4. Pushes the command into command history.
** 5. Configurates terminal before staring lexer.
*/

static void		command_line(t_terminal *term)
{
	term->in = (t_input *)malloc(sizeof(t_input));
	!term->in ? program_exit(term, 1) : 0;
	term->in->history = NULL;
	while (term)
	{
		term->in->h_index = -1;
		ft_memmove(term->in->prompt, INIT, 3);
		ft_bzero(term->in->string, ARG_MAX);
		term->in->index = 0;
		term->in->line = 0;
		init_input(term);
		if (term->in->string[0])
		{
			ft_lstadd(&term->in->history, ft_lstnew(term->in->string, \
			ft_strlen(term->in->string)));
			init_lexer(term);
		}
		else
			ft_putchar('\n');
		if (ft_strequ(term->in->string, "exit"))	//DELETE
			return ;								//DELETE
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
	tcgetattr(1, &term->original);
	term->shell = term->original;
	term->in = NULL;
	term->env = copy_enviroment(term, env);
	print_banner();
	command_line(term);
	program_exit(term, 0);
}
