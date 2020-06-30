/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 14:53:00 by vkuokka           #+#    #+#             */
/*   Updated: 2020/06/30 14:03:46 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_ast.h"
#include "lexer.h"

static char			*get_word(t_lexer *lexer)
{
	unsigned int	start;

	start = lexer->i;
	while (lexer->data[lexer->i] \
	&& !ft_strchr(SEPARATORS, lexer->data[lexer->i]))
		lexer->i++;
	return (ft_strsub(lexer->data, start, lexer->i - start));
}

static char			*get_string(t_lexer *lexer, char quote, t_terminal *term)
{
	unsigned int	start;
	char			*str;

	lexer->i++;
	start = lexer->i;
	while (lexer->data[lexer->i] != quote)
	{
		if (!lexer->data[lexer->i])
		{
			ft_memmove(term->in->prompt, QUOTE, 4);
			ft_putchar('\n');
			start_editor(term);
			if (term->in->sigint)
				return (NULL);
			continue ;
		}
		lexer->i++;
	}
	str = ft_strsub(lexer->data, start, lexer->i - start);
	lexer->i++;
	return (str);
}

t_token				*create_token(int type, char *value)
{
	t_token			*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->e_type = type;
	token->value = value;
	return (token);
}

static t_token		*get_token(t_lexer *lexer, t_terminal *term)
{
	t_token			*token;

	token = NULL;
	if (ft_strchr(OPERATORS, lexer->data[lexer->i]))
	{
		if (lexer->data[lexer->i] == '|')
			token = create_token(TOKEN_PIPE, ft_strdup("|"));
		else if (lexer->data[lexer->i] == '>' || lexer->data[lexer->i] == '<')
			token = get_redirection(lexer);
		else if (lexer->data[lexer->i] == ';')
			token = create_token(TOKEN_SEMI, ft_strdup(";"));
		lexer->i++;
		return (token);
	}
	if (lexer->data[lexer->i] == '"')
		return (create_token(TOKEN_DQUOTE, get_string(lexer, '"', term)));
	if (lexer->data[lexer->i] == '\'')
		return (create_token(TOKEN_SQUOTE, get_string(lexer, '\'', term)));
	return (create_token(TOKEN_WORD, get_word(lexer)));
}

//PIPE SEMI REDIR

			// if((token_next->e_type == 5 || token->e_type == 5))
			// {
			// 	if(token_next->e_type == 5 && token->e_type == 5)
			// 		return 0;
			// 	if(token_next->e_type == 3 || token_next->e_type == 4 ||
			// 	token->e_type == 3 || token->e_type == 4)
			// 		return 0;
			// }
			// if(token_next->e_type == 3 || token->e_type == 3) //tässä ohjataan teksti null
			// {
			// 	if(token_next->e_type == 3 && token->e_type == 3)
			// 		return 0;
			// 	if(token_next->e_type == 4 || token->e_type == 4)
			// 		return 0;
			// }

//tässä errorina exit.. en tiedä et miks tosin. check_syntax

// int				check_tokens(t_list *tokens)
// {
// 	t_token *token;
// 	t_token *token_next;

// 	while (tokens->next)
// 	{
// 		token = tokens->content;
// 		token_next = tokens->next->content;
// 		if (token_next)
// 		{
// 			if ((token_next->e_type == 3 || token_next->e_type == 4 || token_next->e_type == 5) &&
// 			(token->e_type == 3 || token->e_type == 4 || token->e_type == 5))
// 				return (0);
// 		}
// 		tokens = tokens->next;
// 	}
// 	if (token->e_type == 5)
// 		return (0);
// 	return (1);
// }

void	add_null_redirection(t_list *tokens)
{
	t_list	*head;
	t_list	*tail;
	t_list	*prev;
	t_token	*token;
	t_list	*del;

	head = ft_lstnew(create_token(TOKEN_WORD, ft_strdup("cat")), sizeof(t_token));
	head->next = ft_lstnew(create_token(TOKEN_SEMI, ft_strdup(";")), sizeof(t_token));
//	head->next->next = ft_lstnew(create_token(TOKEN_WORD, ft_strdup("echo")), sizeof(t_token));
	// head->next->next->next = ft_lstnew(create_token(TOKEN_REDIRECT, ft_strdup(">")), sizeof(t_token));
//	head->next->next->next = ft_lstnew(create_token(TOKEN_WORD, ft_strdup("")), sizeof(t_token));
	// head = ft_lstnew(create_token(TOKEN_REDIRECT, ft_strdup(">")), sizeof(t_token));
	// head->next = ft_lstnew(create_token(TOKEN_WORD, ft_strdup("/dev/null")), sizeof(t_token));
	tail = tokens->next;
	del = tail;
	tokens->next = head;
	while (tail)
	{
		token = tail->content;
		if (token->e_type == TOKEN_SEMI)
		{
			head->next->next = tail->next;
			prev->next->next = NULL;
			break ;
		}
		prev = tail;
		tail = tail->next;
	}
	free_tokens(del);
}

int		check_syntax_error(int i, int j)
{
	if((j == 5 || i == 5))
		if((j == 5 && i == 5) || j == 3 || j == 4 || i == 3 || i == 4)
			return (1);
	if((j == 3 || i == 3) && (j == 4 || i == 4))
		return (1);
	return (0);
}

int		syntax_error(int i, int j)
{
	if (i == 5 && j == 5)
		ft_printf("\n21: unexpected syntax error close to keyword \";;\"\n");
	else if (j == 5)
		ft_printf("\n21: unexpected syntax error close to keyword \";\"\n");
	else if (j == 3)
		ft_printf("\n21: unexpected syntax error close to keyword \"|\"\n");
	else
		ft_printf("\n21: unexpected syntax error close to keyword \"newline\"\n");
	return (0);
}

int		fixable(t_list *tokens, t_terminal *term)
{
	t_token *token;
	t_token *token_next;

	token = NULL;
	token_next = NULL;
	while (tokens->next)
	{
		token = tokens->content;
		token_next = tokens->next->content;
		if (token_next)
		{
			if (check_syntax_error(token->e_type, token_next->e_type))
				return (syntax_error(token->e_type, token_next->e_type));
			if(token_next->e_type == 3 && token->e_type == 3)
				add_null_redirection(tokens); //tässä ohjataan teksti /dev/null
		}
		tokens = tokens->next;
	}
	if (token_next && token_next->e_type == 5)
		free_tokens(tokens);
	if (token_next && token_next->e_type == 3)
	{
		ft_memmove(term->in->prompt, PIPE, 4);
		ft_putchar('\n');
		start_editor(term);
		if (term->in->sigint)
			return (0);
		init_lexer(term);
		return (9);
	}
	return 1;
}

void				init_lexer(t_terminal *term)
{
	t_lexer			*lexer;
	int				ret;

	lexer = (t_lexer *)malloc(sizeof(t_lexer));
	!lexer ? program_exit(term, 1) : 0;

	lexer->data = term->in->string;
	lexer->i = 0;
	while (lexer->data[lexer->i] && ft_isspace(lexer->data[lexer->i]))
		lexer->i++;
	lexer->tokens = ft_lstnew(get_token(lexer, term), sizeof(t_token));
	while (lexer->data[lexer->i])
	{
		if (ft_isspace(lexer->data[lexer->i]))
		{
			while (lexer->data[lexer->i] && ft_isspace(lexer->data[lexer->i]))
				lexer->i++;
			if (is_aggre(lexer))
				ft_lstaddback(&lexer->tokens, \
				ft_lstnew(get_agr(lexer), sizeof(t_token)));
		}
		else if (lexer->data[lexer->i])
		{
			ft_lstaddback(&lexer->tokens, \
			ft_lstnew(get_token(lexer, term), sizeof(t_token)));
			if (term->in->sigint)
				break ;
		}
	}
	ret = fixable(lexer->tokens, term);
	if (ret && !term->in->sigint) //tässä
	{
		if (ret == 9)
			return ;
		ft_putendl("");
		parse_tokens(term, lexer->tokens);
	}
	free_tokens(lexer->tokens);
}
