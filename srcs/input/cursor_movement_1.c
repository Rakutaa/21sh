#include "halfsh.h"
#include "keyboard.h"

static void	move_cursor_right(t_terminal *term, size_t len, size_t cols)
{
	if (term->in->string[term->in->index])
	{
		if ((len + 1) / cols && !((len + 1) % cols))
		{
			tputs(tgetstr("do", NULL), 1, print_char);
			term->in->line++;
			tputs(tgetstr("cr", NULL), 1, print_char);
		}
		else
			tputs(tgetstr("nd", NULL), 1, print_char);
		term->in->index++;
	}
}

static void	move_cursor_left(t_terminal *term, size_t len, size_t cols)
{
	if (term->in->index > 0)
	{
		if (len / cols && !(len % cols))
		{
			tputs(tgetstr("up", NULL), 1, print_char);
			term->in->line--;
			while (cols--)
				tputs(tgetstr("nd", NULL), 1, print_char);
		}
		else
			tputs(tgetstr("le", NULL), 1, print_char);
		term->in->index--;
	}
}

static void move_cursor_right_word(t_terminal *term, size_t len)
{
    while (term->in->string[term->in->index] && term->in->string[term->in->index] == ' ')
        move_cursor_right(term, len, term->size.ws_col);
    while (term->in->string[term->in->index] && term->in->string[term->in->index] != ' ')
        move_cursor_right(term, len, term->size.ws_col);
}

static void move_cursor_left_word(t_terminal *term, size_t len)
{
    while (term->in->string[term->in->index - 1] && term->in->string[term->in->index - 1] == ' ')
        move_cursor_left(term, len, term->size.ws_col);
    while (term->in->string[term->in->index - 1] && term->in->string[term->in->index - 1] != ' ')
        move_cursor_left(term, len, term->size.ws_col);
}

void		cursor_movement_1(t_terminal *term, int sum)
{
	size_t	cols;
	size_t	len;

	len = term->in->index + ft_strlen(PROMPT);
	cols = term->size.ws_col;
	if (sum == LEFT)
		move_cursor_left(term, len, cols);
	else if (sum == RIGHT)
		move_cursor_right(term, len, cols);
	else if (sum == CTRL_RIGHT)
        move_cursor_right_word(term, len);
    else if (sum == CTRL_LEFT)
        move_cursor_left_word(term, len);
}
