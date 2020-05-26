#ifndef LEXER_H

# define LEXER_H

# include "halfsh.h"

# define SEPARATORS " \"\'\t\n\v\r\f|<>;"
# define OPERATORS "|<>;"

typedef struct		s_token
{
	enum {
					TOKEN_WORD,
					TOKEN_DQUOTE,
					TOKEN_SQUOTE,
					TOKEN_PIPE,
					TOKEN_REDIRECT,
					TOKEN_SEMI
	}				e_type;
	char			*value;
}					t_token;

typedef struct		s_lexer
{
	unsigned int	i;
	char			*data;
	t_list			*tokens;
}					t_lexer;

void				init_lexer(t_terminal *term);
void				init_parser(t_list *tokens);

#endif