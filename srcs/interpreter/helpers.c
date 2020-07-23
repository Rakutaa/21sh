/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hege <hege@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 17:48:00 by vtran             #+#    #+#             */
/*   Updated: 2020/07/23 00:16:00 by hege             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token		*move_token_n_times(t_token *list, int n)
{
	int	count;

	count = -1;
	while (++count < n)
		list = list->next;
	return (list);
}

t_token		*get_re(t_lexer *lexer)
{
	if (lexer->data[lexer->i] == '>')
	{
		if (lexer->data[lexer->i + 1] == '>')
		{
			lexer->i = lexer->i + 1;
			return (create_token(TOKEN_REDIRECT, ft_strdup(">>")));
		}
		return (create_token(TOKEN_REDIRECT, ft_strdup(">")));
	}
	else
	{
		if (lexer->data[lexer->i + 1] == '<')
		{
			lexer->i = lexer->i + 1;
			return (create_token(TOKEN_REDIRECT, ft_strdup("<<")));
		}
		return (create_token(TOKEN_REDIRECT, ft_strdup("<")));
	}
}

t_token		*get_agr(t_lexer *lexer)
{
	int		i;
	int		counter;
	char	*str;

	i = lexer->i;
	counter = i;
	str = lexer->data;
	while (ft_isdigit(str[i]))
		i++;
	i = i + 2;
	if (str[i] == '-')
	{
		i++;
		lexer->i = i;
		return (create_token(TOKEN_AGG, ft_strsub(str, counter, i - counter)));
	}
	while (ft_isdigit(str[i]))
		i++;
	lexer->i = i;
	return (create_token(TOKEN_AGG, ft_strsub(str, counter, i - counter)));
}

int			is_aggre(char *str, int i)
{
	if (str[i] && str[i] == '>' && str[i + 1] && str[i + 1] == '&' &&
	str[i + 2] && (str[i + 2] == ' ' || str[i + 2] == '|' || str[i + 2] == '-'
	|| str[i + 2] == ';' || ft_isdigit(str[i + 2])))
		return (8);
	if (str[i] && str[i] == '<' && str[i + 1] && str[i + 1] == '&' && str[i + 2]
	&& (str[i + 2] == ' ' || str[i + 2] == '|' || str[i + 2] == '-' ||
	str[i + 2] == ';'))
		return (9);
	return (0);
}

int			is_re_ag(t_lexer *lexer)
{
	int		i;
	char	*s;

	i = lexer->i;
	s = lexer->data;
	if (s[i] == ':' && s[i + 1] == '>')
		return (1);
	if (s[i] == '&' && s[i + 1] == '>')
		return (2);
	while (ft_isdigit(s[i]))
		i++;
	if (s[i] && s[i] == '>' && s[i + 1] && s[i + 1] == '>' && s[i + 2])
		return (4);
	if (s[i] && s[i] == '>' && s[i + 1] && s[i + 1] != '&')
		return (3);
	if (s[i] && s[i] == '<' && s[i + 1] && s[i + 1] == '<' && s[i + 2])
		return (6);
	if (s[i] && s[i] == '<' && s[i + 1] && s[i + 1] == '>' && s[i + 2])
		return (7);
	if (s[i] && s[i] == '<' && s[i + 1] && s[i + 1] != '&')
		return (5);
	return (is_aggre(s, i));
}
