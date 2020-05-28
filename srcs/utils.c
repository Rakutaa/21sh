/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 11:10:28 by vkuokka           #+#    #+#             */
/*   Updated: 2020/05/28 13:11:38 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "halfsh.h"

int		print_char(int c)
{
	return (write(0, &c, 1));
}

char	*search_env(t_list *enviroment, char *key)
{
	while (enviroment)
	{
		if (ft_strequ(enviroment->content, key))
			return (ft_strchr(enviroment->content, '\0') + 1);
		enviroment = enviroment->next;
	}
	return (NULL);
}
