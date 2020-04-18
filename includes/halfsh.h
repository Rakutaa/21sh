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
	char		string[ARG_MAX];
	size_t		index;
	size_t		line;
}			t_input;

typedef struct		s_terminal
{
	struct termios	original;
	struct termios	shell;
	struct winsize	size;
	char		**env;
	t_input		*in;
}			t_terminal;

int			print_char(int c);
int			config_terminal(int reset, t_terminal *term);
void			config_signal(t_terminal *term);
void			user_input(t_terminal *term);
void			check_other(t_terminal *term, int sum);
void			print_input(t_terminal *term);
void			arrow_navigation(t_terminal *term, int sum);

#endif
