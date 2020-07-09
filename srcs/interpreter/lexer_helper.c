#include "lexer.h"

void		add_null_redirection(t_token *tokens)
{
	t_token	*head;
	t_token	*tail;
	t_token	*prev;
	t_token	*del;

	head = create_token(TOKEN_WORD, ft_strdup("cat"));
	head->next = create_token(TOKEN_SEMI, ft_strdup(";"));
	tail = tokens->next;
	del = tail;
	tokens->next = head;
	while (tail)
	{
		if (tail->e_type == TOKEN_SEMI)
		{
			head->next->next = tail->next;
			prev->next->next = NULL;
			break ;
		}
		prev = tail;
		tail = tail->next;
	}
	free_tokens(del);
}

void		add_token(t_token *tokens, t_token *new)
{
	while(tokens->next)
		tokens = tokens->next;
	tokens->next = new;
}
