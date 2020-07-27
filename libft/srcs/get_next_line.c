/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 13:50:15 by vkuokka           #+#    #+#             */
/*   Updated: 2020/06/25 00:54:56 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "strings.h"
#include <unistd.h>

static char	*set_line(char *bline, char **line)
{
	size_t	i;
	char	*tmp;

	if (bline[0] == '\0')
	{
		free(bline);
		return (NULL);
	}
	i = 0;
	while (bline[i] != '\n' && bline[i] != '\0')
		i++;
	*line = ft_strsub(bline, 0, i);
	tmp = bline;
	if (bline[i] == '\0')
		bline = ft_strdup(bline + i);
	else
		bline = ft_strdup(bline + i + 1);
	free(tmp);
	return (bline);
}

int			get_next_line(const int fd, char **line)
{
	static char	*bline[FD_MAX];
	char		rline[BUFF_SIZE + 1];
	ssize_t		count;
	char		*tmp;

	if (fd < 0 || fd > FD_MAX || line == NULL)
		return (-1);
	if (!bline[fd])
		if (!(bline[fd] = ft_strnew(0)))
			return (-1);
	while (0 < (count = read(fd, rline, BUFF_SIZE)))
	{
		rline[count] = '\0';
		tmp = bline[fd];
		bline[fd] = ft_strjoin(bline[fd], rline);
		free(tmp);
		if (ft_strchr(bline[fd], '\n'))
			break ;
	}
	if (count < 0)
		return (-1);
	bline[fd] = set_line(bline[fd], line);
	if (!count && !bline[fd])
		return (0);
	return (1);
}
