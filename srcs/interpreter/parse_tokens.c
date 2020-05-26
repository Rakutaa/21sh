/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 09:59:44 by vkuokka           #+#    #+#             */
/*   Updated: 2020/05/26 11:19:33 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static char	*check_tilde(t_list *enviroment, char *str)
{
	char	*temp;
	char	*value;

	value = search_env(enviroment, "HOME");
	!value ? value = "" : 0;
	if (ft_strequ(str, "~"))
	{
		free(str);
		str = ft_strdup(value);
	}
	else if (str[0] == '~')
	{
		temp = str;
		str = ft_strjoin(value, &str[1]);
		free(temp);
	}
	return (str);
}

static void	free_temp(char *temp, char *temp2)
{
	free(temp);
	free(temp2);
}

static char	*check_dollar(t_list *enviroment, char *str)
{
	size_t	i;
	char	c;
	char	*temp;
	char	*temp2;

	i = -1;
	while (str[++i])
		if (str[i] == '$')
		{
			str[i++] = '\0';
			temp2 = str + i;
			while (ft_isalpha(str[++i]))
				continue ;
			c = str[i];
			str[i] = '\0';
			temp = search_env(enviroment, temp2);
			!temp ? temp = "" : 0;
			temp = ft_strjoin(str, temp);
			str[i] = c;
			temp2 = str;
			str = ft_strjoin(temp, str + i);
			free_temp(temp, temp2);
			i = -1;
		}
	return (str);
}

void		parse_tokens(t_terminal *term, t_list *tokens)
{
	t_list	*cur_list;
	t_token	*content;

	cur_list = tokens;
	while (cur_list)
	{
		content = cur_list->content;
		if (content->e_type == TOKEN_DQUOTE || content->e_type == TOKEN_WORD)
		{
			content->value = check_dollar(term->env, content->value);
			content->value = check_tilde(term->env, content->value);
		}
		cur_list = cur_list->next;
	}
}
