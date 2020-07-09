#include "lexer.h"

void			free_tokens(t_token *list)
{
	if (list->next)
		free_tokens(list->next);
	free(list->value);
	list->value = NULL;
	free(list);
	list = NULL;
}
