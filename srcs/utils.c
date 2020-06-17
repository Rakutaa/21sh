/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtran <vtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 11:10:28 by vkuokka           #+#    #+#             */
/*   Updated: 2020/06/17 13:25:01 by vtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "halfsh.h"

int			print_char(int c)
{
	return (write(0, &c, 1));
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

char	**update_enviroment(t_list *enviroment)
{
	char	**env;
	size_t	len;
	size_t	i;

	len = ft_lstlen(&enviroment);
	env = (char **)malloc(sizeof(char **) * len + 1);
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
