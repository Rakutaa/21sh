#include "parser_ast.h"

void	add_node_to_redirection_list(t_redirection **list, t_redirection *node)
{
	t_redirection	*tmp;

	if (!*list)
		(*list) = node;
	else
	{
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = node;
	}
}