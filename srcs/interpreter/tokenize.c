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
			ft_memmove(term->in->prompt, QUOTE, 3);
			start_editor(term);
			if (term->in->sigint)
				break ;
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
	token->next = NULL;
	return (token);
}

t_token		*get_token(t_lexer *lexer, t_terminal *term)
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
