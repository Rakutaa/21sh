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
#include "parser_ast.h"
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

t_token			*get_t_list_token(t_list *node)
{
	if (node)
		return (node->content);
	return NULL;
}

t_list			*move_t_list_n_times(t_list *list, int n)
{
	int					count;

	count = -1;
	while (++count < n)
		list = list->next;
	return (list);
}

void			add_node_to_redirection_list(t_redirection *list, t_redirection *node)
{
	while (list->next)
		list = list->next;
	list->next = node;
}

t_redirection	*tokens_to_redirection(t_list *head, t_list *until)
{
	t_token				*sign;
	t_token				*file;
	t_redirection		*rhead;

	sign = get_t_list_token(head);
	file = get_t_list_token(head->next);
	rhead = create_redirection(file->value, sign->value);
	head = move_t_list_n_times(head, 2);
	while(head && head != until)
	{
		sign = get_t_list_token(head);
		file = get_t_list_token(head->next);
		add_node_to_redirection_list(rhead, create_redirection(file->value, sign->value));
		head = move_t_list_n_times(head, 2);
	}
	return (rhead);
}

t_ast_nodeobj	*tokens_to_factor(t_list *head, int i, t_redirection *redir)
{
	char				**cmd;
	int					count;
	t_token				*token;

	count = -1;
	cmd = malloc(sizeof(char *) * i + 1);
	cmd[i] = NULL;
	while (++count < i)
	{
		token = get_t_list_token(head);
		cmd[count] = token->value;
		head = move_t_list_n_times(head, 1);
	}
	count = -1;
	return (create_factor(cmd, redir));
}

t_ast_nodeobj		*tokens_to_ast_node(t_list *head, t_list *until)
{
	t_list				*tmp;
	t_token				*token;
	t_redirection		*redir;
	int					i;

	redir = NULL;
	tmp = head;
	i = 0;
	while (tmp)
	{
		token = get_t_list_token(tmp);
		if (token->e_type == TOKEN_REDIRECT)
		{
			redir = tokens_to_redirection(tmp, until);
			break ;
		}
		if (tmp == until && tmp->next)
			break ;
		i++;
		tmp = move_t_list_n_times(tmp, 1);
	}
	return (tokens_to_factor(head, i, redir));
}

t_parser_node_list		*init_nodelist()
{
	t_parser_node_list	*list;

	list = malloc(sizeof(t_parser_node_list));
	list->parser_nodeobj = NULL;
	list->next = NULL;
	return list;
}

void					add_node_to_nodelist(t_parser_node_list **list, t_parser_nodeobj *ast_nodeobj, t_parser_nodeobj *token_nodeobj)
{
	t_parser_node_list	*tmp;

	if (!*list)
	{
		(*list) = init_nodelist();
		(*list)->parser_nodeobj = ast_nodeobj;
		tmp = (*list);
	}
	else
	{
		tmp = (*list);
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = init_nodelist();
		tmp->next->parser_nodeobj = ast_nodeobj;
		tmp = tmp->next;
	}
	if (token_nodeobj)
	{
		tmp->next = init_nodelist();
		tmp->next->parser_nodeobj = token_nodeobj;
	}
}

t_ast					*init_ast()
{
	t_ast				*ast;

	ast = malloc(sizeof(t_ast));
	ast->in = 0;
	ast->out = 1;
	ast->err = 2;
	ast->parent = NULL;
	ast->next = NULL;
	return ast;
}

t_ast					*create_ast_node(t_ast *ast, t_parser_node_list **list)
{
	if (!ast)
	{
		ast = init_ast();
		ast->parent = (*list)->parser_nodeobj->nodes.node.ast_nodeobj;
	}
	else
	{
		ast->next = init_ast();
		ast->next->parent = (*list)->next->parser_nodeobj->nodes.node.ast_nodeobj;
		ast = ast->next;
		*list = (*list)->next;
	}
	*list = (*list)->next;
	return (ast);
}

//ajattele tama viela uusiks
//ehkä vois ajatella niin, et jos toi node on 
//token niin do smth ja jos on ast_nodeobj do smth

t_ast					*create_ast_list(t_parser_node_list *list)
{
	t_ast	*ast;
	t_ast	*tmp;

	ast = NULL;
	tmp = ast;
	while (list)
	{
		if (list->parser_nodeobj->tn != token || 
		list->parser_nodeobj->nodes.token.e_type != TOKEN_P)
		{
			tmp = create_ast_node(tmp, &list);
			if (!ast)
				ast = tmp;
		}
		else
		{
			tmp->parent = create_expression(tmp->parent, list->next->parser_nodeobj->nodes.node.ast_nodeobj);
			list = list->next->next;
		}
	}
	return (ast);
}

//token quoten ja token_wordin vois tehda muualla
//mm. check quotes

void					check_dollar_tilde(t_list *env, t_token *token)
{
	if (token->e_type == TOKEN_DQUOTE || token->e_type == TOKEN_WORD)
	{
		token->value = check_dollar(env, token->value);
		token->value = check_tilde(env, token->value);
	}
}

void					add_to_token_node_list(t_parser_node_list **list, t_list *head, t_list *cur_list, int type)
{
	t_parser_nodeobj *ast_nodeobj;
	t_parser_nodeobj *token_nodeobj;

	ast_nodeobj = malloc(sizeof(t_parser_nodeobj));
	token_nodeobj = NULL;
	ast_nodeobj->tn = node;
	ast_nodeobj->nodes.node.ast_nodeobj = tokens_to_ast_node(head, cur_list);
	if (type == 3 || type == 5)
	{
		token_nodeobj = malloc(sizeof(t_parser_nodeobj));
		token_nodeobj->tn = token;
		token_nodeobj->nodes.token.e_type = type == 3 ? 0 : 1;
	}
	add_node_to_nodelist(list, ast_nodeobj, token_nodeobj);
}

void					execute_ast(t_ast *ast)
{
	while (ast)
	{
		if (ast->parent->node == factor)
			visit_factor(ast->parent, &ast);
		else
			visit_expression(ast->parent, &ast);
		ast = ast->next;
	}
}

void					parse_tokens(t_terminal *term, t_list *tokens)
{
	t_list	*cur_list;
	t_list	*head;
	t_token	*content;
	t_parser_node_list	*nhead;
	t_ast		*ast;

	head = tokens;
	cur_list = tokens;
	nhead = NULL;
	while (cur_list)
	{
		content = get_t_list_token(cur_list);
		check_dollar_tilde(term->env, content);
		if (content->e_type == TOKEN_PIPE || content->e_type == TOKEN_SEMI || !cur_list->next)
		{
			add_to_token_node_list(&nhead, head, cur_list, content->e_type);
			head = cur_list->next;
		}
		cur_list = move_t_list_n_times(cur_list, 1);
	}
	ast = create_ast_list(nhead);
	execute_ast(ast);
}
