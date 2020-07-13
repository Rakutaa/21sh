#include "parser_ast.h"

static void	free_redir_aggre(t_redirection_aggregation *list)
{
	if (list->next)
		free_redir_aggre(list->next);
	if (list->e_flag == AGGRE)
	{
		free(list->node.t_ag.sign);
		if (list->node.t_ag.n)
			free(list->node.t_ag.n);
		if (list->node.t_ag.word)
			free(list->node.t_ag.word);		
	}
	free(list);
}

static void free_factor(t_ast_node *factor)
{
	free(factor->nodes.t_factor.cmds);
	if (factor->nodes.t_factor.list)
		free_redir_aggre(factor->nodes.t_factor.list);
	if (factor->nodes.t_factor.path_join)
		free(factor->nodes.t_factor.path_join);
	free(factor);
}

void		free_parser(t_parser_node_list *list)
{
	if (list->next)
		free_parser(list->next);
	if (list->parser_nodeobj->e_node != TOKEN)
		free_factor(list->parser_nodeobj->nodes.ast_nodeobj);
	free(list->parser_nodeobj);
	free(list);
}