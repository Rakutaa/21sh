/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtran <vtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 17:48:00 by vtran             #+#    #+#             */
/*   Updated: 2020/06/10 18:10:33 by vtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

//tokenize2.c

// t_token		*get_t_list_token(t_list *node)
// {
// 	if (node)
// 		return (node->content);
// 	return (NULL);
// }

t_token		*move_token_n_times(t_token *list, int n)
{
	int	count;

	count = -1;
	while (++count < n)
		list = list->next;
	return (list);
}

t_token		*get_redirection(t_lexer *lexer)
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

int			is_aggre(t_lexer *lexer)
{
	int		i;
	char	*str;

	i = lexer->i;
	str = lexer->data;
	if (str[i] == ':' && str[i + 1] == '>')
		return (1);
	if (str[i] == '&' && str[i + 1] == '>')
		return (2);
	while (ft_isdigit(str[i]))
		i++;
	if (str[i] && str[i] == '>' && str[i + 1] && str[i + 1] == '>' && str[i + 2])
		return (4);
	if (str[i] && str[i] == '>' && str[i + 1] && str[i + 1] == '&' && str[i + 2] && (str[i + 2] == ' ' || str[i + 2] == '|' || str[i + 2] == ';' || ft_isdigit(str[i + 2])))
		return (8);
	if (str[i] && str[i] == '>' && str[i + 1])
		return (3);
	if (str[i] && str[i] == '<' && str[i + 1] && str[i + 1] == '<' && str[i + 2])
		return (6);	
	if (str[i] && str[i] == '<' && str[i + 1] && str[i + 1] == '>' && str[i + 2])
		return (7);
	if (str[i] && str[i] == '<' && str[i + 1] && str[i + 1] == '&' && str[i + 2] && (str[i + 2] == ' ' || str[i + 2] == '|' || str[i + 2] == ';'))
		return (9);
	if (str[i] && str[i] == '<' && str[i + 1])
		return (5);
	return (0);
}
