#include "lexer.h"

void			free_tokens(t_list *list)
{
	t_token		*token;

	if (list->next)
	{
		free_tokens(list->next);
		token = list->content;
		free(token->value);
		free(token);
		free(list);
//		token->value = NULL;
		token = NULL;
		list = NULL;
	}
}
