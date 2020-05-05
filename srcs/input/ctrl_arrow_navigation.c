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

static void move_cursor_right_word(t_terminal *term)
{
    int len;

    len = term->in->index + ft_strlen(PROMPT);
    while (term->in->string[term->in->index] && term->in->string[term->in->index] == ' ')
        navigate_right(term, len, term->size.ws_col);
    while (term->in->string[term->in->index] && term->in->string[term->in->index] != ' ')
        navigate_right(term, len, term->size.ws_col);
}

static void move_cursor_left_word(t_terminal *term)
{
    int len;

    len = term->in->index + ft_strlen(PROMPT);
    while (term->in->string[term->in->index - 1] && term->in->string[term->in->index - 1] == ' ')
        navigate_left(term, len, term->size.ws_col);
    while (term->in->string[term->in->index - 1] && term->in->string[term->in->index - 1] != ' ')
        navigate_left(term, len, term->size.ws_col);
}

void		ctrl_arrow_navigation(t_terminal *term, int sum)
{
    if (sum == CTRL_UP)
        move_cursor_up(term);
    else if (sum == CTRL_DOWN)
        move_cursor_down(term);
    else if (sum == CTRL_RIGHT)
        move_cursor_right_word(term);
    else if (sum == CTRL_LEFT)
        move_cursor_left_word(term);
}