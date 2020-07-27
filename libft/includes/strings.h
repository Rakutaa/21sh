/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 19:02:47 by vkuokka           #+#    #+#             */
/*   Updated: 2020/06/29 15:54:20 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRINGS_H

# define STRINGS_H

# include <stdlib.h>

typedef struct	s_lens
{
	int			len_org;
	int			len_rep;
	int			len_with;
	int			delta;
	int			count;
}				t_lens;

char			*ft_strcat(char *s1, const char *s2);
char			*ft_strchr(const char *s, int c);
size_t			ft_strclen(const char *s, int c);
void			ft_strclr(char *s);
int				ft_strcmp(const char *s1, const char *s2);
char			*ft_strcpy(char *dst, const char *src);
void			ft_strdel(char **as);
char			*ft_strdup(const char *s1);
int				ft_strequ(char const *s1, char const *s2);
void			ft_striter(char *s, void (*f)(char *));
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
char			*ft_strjoin(char const *s1, char const *s2);
size_t			ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t			ft_strlen(const char *s);
char			*ft_strmap(char const *s, char (*f)(char));
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char			*ft_strncat(char *s1, const char *s2, size_t n);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strncpy(char *dst, const char *src, size_t len);
int				ft_strnequ(char const *s1, char const *s2, size_t n);
char			*ft_strnew(size_t size);
char			*ft_strnstr(const char *hay, const char *needle, size_t len);
char			*ft_strrchr(const char *s, int c);
char			*ft_strreplace(char *org, char *rep, char *with);
char			**ft_strsplit(char const *s, char c);
size_t			ft_strspn(const char *s1, const char *s2);
char			*ft_strstr(const char *hay, const char *needle);
char			*ft_strsub(char const *s, unsigned int start, size_t len);
char			*ft_strtrim(char const *s);

#endif
