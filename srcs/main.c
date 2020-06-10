/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 18:59:01 by vkuokka           #+#    #+#             */
/*   Updated: 2020/06/10 14:24:26 by vkuokka          ###   ########.fr       */
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
			init_lexer(term);
			ft_lstadd(&term->in->history, ft_lstnew(term->in->string, \
			ft_strlen(term->in->string)));
		}
		else
			ft_putendl("");
		if (ft_strequ(term->in->string, "exit"))	//DELETE
			return ;								//DELETE
	}
}

int				main(int argc, char **argv, char **env)
{
	t_terminal	*term;

	(void)argc;
	(void)argv;
	term = (t_terminal *)malloc(sizeof(t_terminal));
	!term ? program_exit(term, 1) : 0;
	tcgetattr(1, &term->original);
	term->shell = term->original;
	ioctl(1, TIOCGWINSZ, &term->size);
	term->in = NULL;
	term->env = copy_enviroment(term, env);
	config_terminal(0, term);
	config_signal(term);
	print_banner();
	command_line(term);
	program_exit(term, 0);
}
