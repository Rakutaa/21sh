/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtran <vtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 13:08:11 by vkuokka           #+#    #+#             */
/*   Updated: 2020/06/01 15:43:18 by vtran            ###   ########.fr       */
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
void				parse_tokens(t_terminal *term, t_list *tokens);

#endif
