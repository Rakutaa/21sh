#include "lexer.h"

void		add_token(t_token *tokens, t_token *new)
{
	while(tokens->next)
		tokens = tokens->next;
	tokens->next = new;
}
