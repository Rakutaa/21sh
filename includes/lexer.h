/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hege <hege@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 13:08:11 by vkuokka           #+#    #+#             */
/*   Updated: 2020/07/22 23:45:54 by hege             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		TOKEN_SEMI,
		TOKEN_AGG
	}				e_type;
	char			*value;
	struct s_token	*next;
}					t_token;

typedef struct		s_lexer
{
	unsigned int	i;
	char			data[ARG_MAX];
	t_token			*tokens;
}					t_lexer;

void				init_lexer(t_terminal *term);
void				parse_tokens(t_terminal *term, t_token *tokens);
t_token				*get_t_list_token(t_list *node);
t_token				*move_token_n_times(t_token *list, int n);
void				check_dollar_tilde(t_list *env, t_token *token);
t_token				*get_agr(t_lexer *lexer);
int					is_re_ag(t_lexer *lexer);
t_token				*create_token(int type, char *value);
t_token				*get_redirection(t_lexer *lexer);
int					ok_to_parser(t_token *tokens, t_terminal *term);
int					syntax_error(int i, int j);
void				free_tokens(t_token *list);
int					not_pipe_semi_re(t_lexer *lexer);
void				add_token(t_token **tokens, t_token *new);
void				add_null_redirection(t_token *tokens, t_token *head, t_token **next);
t_token				*get_token(t_lexer *lexer, t_terminal *term);
void				free_env(t_env *env);
void				free_table(char	**table);
#endif
