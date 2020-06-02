/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtran <vtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 09:59:44 by vkuokka           #+#    #+#             */
/*   Updated: 2020/06/02 16:14:16 by vtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "header.h"
#include "../nodeobj.c"

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

// ks onko redirectioneita
//muista exit jos ei oo filee
//file = check file exit if not

t_redirection	*make_redir(t_list *head, t_list *cur_list)
{
	t_token	*sign;
	t_token *file;
	t_redirection *rhead;
	t_redirection *rtmp;

	sign = head->content;
	file = head->next->content;
	rhead = mkredir(file->value, sign->value);
	rtmp = rhead->next;
	head = head->next->next;
	while(head != cur_list->next)
	{

		sign = head->content;
		file = head->next->content;
		rtmp = mkredir(file->value, sign->value);
		head = head->next->next;
		rtmp = rtmp->next;
	}
	return (rhead);
}

t_nodeobj	*list_to_factor(t_list *head, int i, t_redirection *redir)
{
	char		**cmd;
	int			count;
	t_token		*token;

	count = -1;
	cmd = malloc(sizeof(char *) * i + 1);
	cmd[i] = NULL;
	while (++count < i)
	{
		token = head->content;
		cmd[count] = token->value;
		head = head->next;
	}
	count = -1;
	return (mkfactor(cmd, redir));
}

t_nodeobj		*make_simple(t_list *head, t_list *cur_list)
{
	t_list	*tmp;
	t_token	*token;
	t_redirection	*redir;
	int		i;

	redir = NULL;
	tmp = head;
	i = 0;
	while (tmp)
	{
		token = tmp->content;
		if (token->e_type == TOKEN_REDIRECT)
		{
			redir = make_redir(tmp, cur_list);
			break ;
		}
		
		if (cur_list && tmp == cur_list)
		{
			i++;
			break ;
		}
		i++;
		tmp = tmp->next;
	}
	return (list_to_factor(head, i, redir));
}

t_nodelist *init_nodelist()
{
	t_nodelist *nodelist;

	nodelist = malloc(sizeof(t_nodelist));
	nodelist->e_type = TOKEN_N;
	nodelist->nodeobj = NULL;
	nodelist->next = NULL;
	return nodelist;
}

void		add_to_nodelist(t_nodelist **head, t_nodeobj *nobj, int i)
{
	t_nodelist *tmp;
	t_nodelist *print;

	if (!*head)
	{
		// ft_printf("kakka");
		// ft_printf("%d ", i);
		*head = init_nodelist();
		tmp = *head;
		tmp->e_type = i; 
		tmp->nodeobj = nobj;
		tmp->next = NULL;
	}
	else
	{
		// ft_printf("yo");
		// ft_printf("%d ", i);
//		ft_printf("%d yoyoy", (*head)->e_type);
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		print = init_nodelist();
		print->e_type = i; 
		print->nodeobj = nobj;
		print->next = NULL;
		tmp->next = print;
	}
}

t_ast	*create_ast(t_nodelist *list)
{
	t_ast	*ast;
	t_ast	*tmp;

	ast = NULL;
	tmp = ast;
	while (list)
	{
		if (!tmp)
		{
			tmp = malloc(sizeof(t_ast));
			tmp->parent = list->nodeobj;
			tmp->in= 0;
			tmp->out = 1;
			tmp->err = 2;
			if (!ast)
				ast = tmp;
		}
		if (list->e_type == TOKEN_P)
		{
			tmp->parent = mkexpr(tmp->parent, list->next->nodeobj);
			list = list->next;
		}
		else if (list->e_type == TOKEN_S)
			tmp = tmp->next;
		else if (list->e_type == TOKEN_N)
		{
			return ast;
		}
			
	}
	return (ast);
}

//token quoten ja token_wordin vois tehda muualla
//mm. check quotes

void		check_dollar_tilde(t_list *env, t_token *token)
{
	if (token->e_type == TOKEN_DQUOTE || token->e_type == TOKEN_WORD)
	{
		token->value = check_dollar(env, token->value);
		token->value = check_tilde(env, token->value);
	}
}

void		parse_tokens(t_terminal *term, t_list *tokens)
{
	t_list	*cur_list;
	t_list	*head;
	t_token	*content;
	t_nodelist	*nhead;
	t_ast		*ast;
	t_list	*prev;

	head = tokens;
	cur_list = tokens;
	nhead = NULL;
	ast = NULL;
	while (cur_list)
	{
		content = cur_list->content;
		check_dollar_tilde(term->env, content);
		if (content->e_type == TOKEN_PIPE || content->e_type == TOKEN_SEMI || !cur_list->next)
		{
			if (!cur_list->next)
				add_to_nodelist(&nhead, make_simple(head, cur_list), 0);
			else
				add_to_nodelist(&nhead, make_simple(head, prev), content->e_type == TOKEN_PIPE ? 1 : 2);
			head = cur_list->next;
		}
		prev = cur_list;
		cur_list = cur_list->next;
	}
	ast = create_ast(nhead);
	while (ast)
    {
        switch(ast->parent->node)
		{
            case factor:
                visit_f(ast->parent, &ast);
                break;
            case expr:
                visit_e(ast->parent, &ast);
                break;
        }
		ast = ast->next;
	}
}
