#include "lexer.h"

void		add_token(t_token **tokens, t_token *new)
{
	t_token *tmp;

	if (!*tokens)
		*tokens = new;
	else
	{
		tmp = *tokens;
		while(tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}
