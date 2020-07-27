/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strreplace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 23:05:49 by mtuomine          #+#    #+#             */
/*   Updated: 2020/06/29 14:49:34 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "strings.h"

static int	set_lens(t_lens *lens, char *org, char *rep, char *with)
{
	lens->len_org = ft_strlen(org);
	lens->len_rep = ft_strlen(rep);
	lens->len_with = ft_strlen(with);
	lens->count = 0;
	if (lens->len_org == 0 || lens->len_rep == 0)
		return (1);
	return (0);
}

static char	*allocate_mem(t_lens lens)
{
	char *res;

	res = (char *)malloc(sizeof(char) * \
	(lens.len_org + (lens.len_with - lens.len_rep) * lens.count + 1));
	return (res);
}

char		*ft_strreplace(char *org, char *rep, char *with)
{
	char	*res;
	char	*ins;
	char	*temp;
	t_lens	lens;

	if (set_lens(&lens, org, rep, with))
		return (NULL);
	ins = org;
	while ((temp = ft_strstr(ins, rep)))
	{
		ins = temp + lens.len_rep;
		lens.count++;
	}
	res = allocate_mem(lens);
	temp = res;
	while (lens.count--)
	{
		ins = ft_strstr(org, rep);
		lens.delta = ins - org;
		temp = ft_strncpy(temp, org, lens.delta) + lens.delta;
		temp = ft_strcpy(temp, with) + lens.len_with;
		org += lens.delta + lens.len_rep;
	}
	ft_strcpy(temp, org);
	return (res);
}
