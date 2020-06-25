/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_ast.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 16:40:04 by vtran             #+#    #+#             */
/*   Updated: 2020/06/25 16:46:53 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_AST_H

# define PARSER_AST_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include "lexer.h"
# include "library.h"

typedef struct							s_redirection_aggregation
{
	enum {
		REDIR,
		AGGRE
	}									e_flag;
	union
	{
		struct							s_redirection
		{
			char						*redir;
			char						*file;
		}								t_redirection;
		struct							s_ag
		{
			char						*n;
			char						*sign;
			char						*word;
		}								t_ag;
	}									node;
	struct s_redirection_aggregation	*next;
}										t_redirection_aggregation;

/*
**ideana olis et toi enum flagais noden.
**Nyt ASTnodessa tiedetään et millainen
**käsiteltävä data on.
*/

typedef struct							s_ast_node
{
	enum
	{
		FACTOR,
		EXPR
	}									e_node;
	union
	{
		struct							s_factor
		{
			char						**cmds;
			t_redirection_aggregation	*list;
		}								t_factor;
		struct							s_expr
		{
			struct s_ast_node			*left;
			struct s_ast_node			*right;
		}								t_expr;
	}									nodes;
}										t_ast_node;

typedef struct							s_parser_node
{
	enum
	{
		TOKEN,
		AST
	}									e_node;
	union
	{
		struct							s_parser_token
		{
			enum
			{
				TOKEN_P,
				TOKEN_S
			}							e_type;
		}								token;
		struct							s_parser_nodes
		{
			t_ast_node					*ast_nodeobj;
		}								ast;
	}									nodes;
}										t_parser_node;

typedef struct							s_parser_node_list
{
	t_parser_node						*parser_nodeobj;
	struct s_parser_node_list			*next;
}										t_parser_node_list;

typedef struct							s_ast
{
	t_ast_node							*parent;
	int									in;
	int									out;
	int									err;
	struct s_ast						*next;
}										t_ast;

t_ast_node								*create_factor(char **cmnd, \
										t_redirection_aggregation *list);
t_ast_node								*create_expression(t_ast_node *left, \
										t_ast_node *right);
void									helper_dup(t_ast **ast, \
										t_ast_node *obj, int pipe_in);
void									helper_close(t_ast_node *obj,
										t_ast **ast);
void									exec_factor(t_ast_node *obj,
										t_ast **ast);
void									visit_factor(t_ast_node *obj,
										t_ast **ast);
void									visit_expression(t_ast_node *obj,
										t_ast **ast);
void									add_node_to_parser_node_list(
										t_parser_node_list\
										**list, t_parser_node *ast_node, \
										t_parser_node *token_node);
t_ast									*create_ast_list(
										t_parser_node_list *list);
void									execute_ast(t_ast *ast);
t_redirection_aggregation				*tokens_to_redirection(
										t_list *head, t_list *last);
void									free_ast(t_ast *list);
void									free_parser(t_parser_node_list *list);
void									free_tokens(t_list *list);
t_ast									*init_ast(void);

#endif
