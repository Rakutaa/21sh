#include "lexer.h"

static void	free_linked(t_list	*list)
{
	t_list	*next;

	while (list)
	{
		next = NULL;
		if (list->next)
			next = list->next;
		free(list->content);
		free(list);
		list = next;
	}
}

void	    free_table(char	**table)
{
	int	i;
	
	i = -1;
	while(table[++i])
		free(table[i]);
    free(table);
}

void	    free_env(t_env *env)
{
	t_list	*perkele;
	char	**vittu;

	perkele = env->linked;
	vittu = env->table;
	free_linked(perkele);
	free_table(vittu);
	free(env);
}
