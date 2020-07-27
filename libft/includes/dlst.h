/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlst.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 21:43:06 by vkuokka           #+#    #+#             */
/*   Updated: 2020/06/24 22:01:55 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DLST_H

# define DLST_H

# include <stdlib.h>

typedef struct		s_dlist
{
	void			*content;
	size_t			content_size;
	struct s_dlist	*next;
	struct s_dlist	*prev;
}					t_dlist;

void				ft_ddel(void *content, size_t size);
void				ft_dlstadd(t_dlist **alst, t_dlist *new);
void				ft_dlstaddback(t_dlist **alst, t_dlist *new);
void				ft_dlstdel(t_dlist **alst, void (*del)(void *, size_t));
void				ft_dlstdelone(t_dlist **alst, void (*del)(void *, size_t));
void				ft_dlstiter(t_dlist *lst, void (*f)(t_dlist *elem));
size_t				ft_dlstlen(t_dlist **alst);
t_dlist				*ft_dlstmap(t_dlist *lst, t_dlist *(*f)(t_dlist *elem));
t_dlist				*ft_dlstnew(void const *content, size_t content_size);

#endif
