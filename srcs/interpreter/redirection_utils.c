#include "parser_ast.h"

void	add_node_to_redirection_list(t_redirection *list, t_redirection *node)
{
	while (list->next)
		list = list->next;
	list->next = node;
}