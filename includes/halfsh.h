/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   halfsh.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 11:08:20 by vkuokka           #+#    #+#             */
/*   Updated: 2020/06/24 15:52:25 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HALFSH_H

# define HALFSH_H

# include "ft_printf.h"
# include <sys/ioctl.h>
# include <termios.h>
# include <term.h>
# include <signal.h>
# include <fcntl.h>

# define H_FILE ".history"
# define H_LEN 10
# define ARG_MAX 262144
# define INIT "$> "
# define QUOTE "q> "
# define PIPE "p> "

typedef struct		s_input
{
	int				h_index;
	char			prompt[4];
	char			string[ARG_MAX];
	int				index;
	int				line;
}					t_input;

typedef struct		s_terminal
{
	struct termios	original;
	struct termios	shell;
	struct winsize	size;
	t_list			*env;
	t_input			*in;
	t_list			*history;
}					t_terminal;

int					print_char(int c);
char				*search_env(t_list *enviroment, char *key);
char				**update_enviroment(t_list *enviroment);
void				config_termcaps(void);
void				config_terminal(int reset, t_terminal *term);
void				config_signal(t_terminal *term);
void				program_exit(t_terminal *term, int num);
void				user_input(t_terminal *term);
void				print_input(t_terminal *term);
void				cursor_movement_1(t_terminal *term, int sum);
void				cursor_movement_2(t_terminal *term, int sum);
void				browse_history(t_terminal *term, int sum);
void				search_action(t_terminal *term, int sum);
void				start_editor(t_terminal *term);
void				init_input(t_input *input);
void				clipboard(t_terminal *term, int sum);
void				init_history(t_terminal *term);
void				save_history(t_terminal *term);


#endif
