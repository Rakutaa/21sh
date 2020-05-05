#include "halfsh.h"
#include "keyboard.h"

static void move_cursor_up(t_terminal *term)
{
        term->in->index = term->in->index - term->size.ws_col;
        if (term->in->index < 0)
            term->in->index = 0;
}

static void move_cursor_down(t_terminal *term)
{
    int     len;

    len = ft_strlen(term->in->string);

        term->in->index = term->in->index + term->size.ws_col;
        if (term->in->index > len)
            term->in->index = len;
}

void		ctrl_arrow_navigation(t_terminal *term, int sum)
{
    if (sum == CTRL_UP)
        move_cursor_up(term);
    if (sum == CTRL_DOWN)
        move_cursor_down(term);
}