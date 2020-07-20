/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   halfsh.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtran <vtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 11:08:20 by vkuokka           #+#    #+#             */
/*   Updated: 2020/07/20 12:54:48 by vtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HALFSH_H

# define HALFSH_H

# include "library.h"
# include <sys/ioctl.h>
# include <termios.h>
# include <term.h>
# include <signal.h>
# include <fcntl.h>
# include <stdbool.h>


# define HISTFILE ".history"
# define HISTSIZE 10
# define FCFILE "/private/tmp/21shfc"
# define ARG_MAX 262144
# define INIT "$> "
# define QUOTE "q> "
# define PIPE "p> "

typedef struct		s_input
{
	char			prompt[4];
	char			string[ARG_MAX];
	int				index;
	int				line;
	bool			sigint;
}					t_input;

typedef struct		s_env
{
	t_list			*linked;
	char			**table;
}					t_env;


typedef struct		s_terminal
{
	struct termios	original;
	struct termios	shell;
	struct winsize	size;
	char			clipboard[ARG_MAX];
	t_env			*env;
	t_input			*in;
	t_dlist			*h_head;
	t_dlist			*h_tail;
	t_dlist			*h_current;
}					t_terminal;

int					print_char(int c);
char				*search_env(t_list *enviroment, char *key);
char				**update_enviroment(t_list *enviroment);
void				copy_enviroment(t_terminal *term, char **env);
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
void				mac_clipboard(t_terminal *term, int sum);
void				shell_clipboard(t_terminal *term, int sum);
void				init_history(t_terminal *term);
void				save_history(t_terminal *term);
int					listen_keys(void);
void				mac_clipboard(t_terminal *term, int sum);
void				execute_pipe(t_terminal *term);

#endif
