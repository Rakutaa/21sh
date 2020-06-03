#include "lexer.h"

t_token	*get_t_list_token(t_list *node)
{
	if (node)
		return (node->content);
	return NULL;
}

t_list	*move_t_list_n_times(t_list *list, int n)
{
	int	count;

	count = -1;
	while (++count < n)
		list = list->next;
	return (list);
}