#include "lexer.h"

void		unset_key(t_list *enviroment, char *key)
{
	t_list	*link;

	link = NULL;
	while (enviroment)
		if (ft_strequ(enviroment->content, key))
		{
			if (link)
			{
				link->next = enviroment->next;
				ft_lstdelone(&enviroment, ft_del);
			}
			else
				ft_memset(enviroment->content, 0, enviroment->content_size);
			return ;
		}
		else
		{
			link = enviroment;
			enviroment = enviroment->next;
		}
}

//**env pitäis updatee

void	set_key(t_list *enviroment, char *key, char *value)
{
	size_t	len1;
	size_t	len2;
	char	*str;
	t_list	*node;

	if (!key || !value)
		return ;
	unset_key(enviroment, key);
	len1 = ft_strlen(key);
	len2 = ft_strlen(value);
	str = ft_strnew(len1 + len2 + 1);
	ft_memmove(str, key, len1);
	ft_memmove(str + len1, "\0", 1);
	ft_memmove(str + len1 + 1, value, len2);
	node = ft_lstnew(NULL, 0);
	node->content = str;
	node->content_size = len1 + len2 + 2;
	ft_lstaddback(&enviroment, node);
}

char			*value_lookup(t_list *enviroment, char *key)
{
	while (enviroment)
	{
		if (ft_strequ(enviroment->content, key))
			return (ft_strchr(enviroment->content, '\0') + 1);
		enviroment = enviroment->next;
	}
	return (NULL);
}
