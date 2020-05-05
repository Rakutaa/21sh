#ifndef HALFSH_H

# define HALFSH_H

# include "ft_printf.h"
# include <sys/ioctl.h>
# include <termios.h>
# include <term.h>
# include <signal.h>

# define ARG_MAX 2097152
# define PROMPT "$>"

typedef struct		s_input
{
	t_list			*history;
	int				h_index;
	char			string[ARG_MAX];
	int				index;
	int				line;
}					t_input;

typedef struct		s_terminal
{
	struct termios	original;
	struct termios	shell;
	struct winsize	size;
	char			**env;
	t_input			*in;
}					t_terminal;

int					print_char(int c);
void				config_terminal(int reset, t_terminal *term);
void				config_signal(t_terminal *term);
void				program_exit(t_terminal *term, int num);
void				user_input(t_terminal *term);
void				print_input(t_terminal *term);
void				cursor_movement_1(t_terminal *term, int sum);
void				cursor_movement_2(t_terminal *term, int sum);
void				browse_history(t_terminal *term, int sum);
void				search_action(t_terminal *term, int sum);
void				init_input(t_terminal *term);

#endif
