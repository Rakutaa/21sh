/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 11:10:28 by vkuokka           #+#    #+#             */
/*   Updated: 2020/07/23 14:35:47 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "halfsh.h"

int			print_char(int c)
{
	return (write(STDIN_FILENO, &c, 1));
}

char		*search_env(t_list *enviroment, char *key)
{
	while (enviroment)
	{
		if (ft_strequ(enviroment->content, key))
			return (ft_strchr(enviroment->content, '\0') + 1);
		enviroment = enviroment->next;
	}
	return (NULL);
}

char		**update_enviroment(t_list *enviroment)
{
	char	**env;
	size_t	len;
	size_t	i;

	len = ft_lstlen(&enviroment);
	env = (char **)malloc(sizeof(char *) * len + 1);
	if (!env)
		return (NULL);
	i = 0;
	while (enviroment)
	{
		env[i] = ft_strnew(enviroment->content_size);
		ft_memmove(env[i], enviroment->content, enviroment->content_size);
		*ft_strchr(env[i], '\0') = '=';
		i++;
		enviroment = enviroment->next;
	}
	env[i] = NULL;
	return (env);
}

void		copy_enviroment(t_terminal *term, char **env)
{
	size_t	i;
	t_list	*start;
	t_list	*node;

	term->env = (t_env *)malloc(sizeof(t_env));
	i = 0;
	start = NULL;
	while (env[i])
	{
		node = ft_lstnew(env[i], ft_strlen(env[i]) + 1);
		!node ? program_exit(term, 1) : 0;
		*ft_strchr(node->content, '=') = '\0';
		!start ? start = node : ft_lstaddback(&start, node);
		i++;
	}
	term->env->linked = start;
	term->env->table = update_enviroment(term->env->linked);
}
