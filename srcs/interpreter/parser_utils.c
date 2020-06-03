#include "lexer.h"
#include "parser_ast.h"

static t_parser_node_list	*init_parser_node_list()
{
	t_parser_node_list	*list;

	list = malloc(sizeof(t_parser_node_list));
	list->parser_nodeobj = NULL;
	list->next = NULL;
	return list;
}

void						add_node_to_parser_node_list(t_parser_node_list **list, t_parser_node *ast_nodeobj, t_parser_node *token_nodeobj)
{
	t_parser_node_list	*tmp;

	if (!*list)
	{
		(*list) = init_parser_node_list();
		(*list)->parser_nodeobj = ast_nodeobj;
		tmp = (*list);
	}
	else
	{
		tmp = (*list);
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = init_parser_node_list();
		tmp->next->parser_nodeobj = ast_nodeobj;
		tmp = tmp->next;
	}
	if (token_nodeobj)
	{
		tmp->next = init_parser_node_list();
		tmp->next->parser_nodeobj = token_nodeobj;
	}
}