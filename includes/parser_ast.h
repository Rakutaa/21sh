/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_ast.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtran <vtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 16:40:04 by vtran             #+#    #+#             */
/*   Updated: 2020/06/10 19:12:02 by vtran            ###   ########.fr       */
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

// typedef struct							s_env
// {
// 	char								**paths;
// 	int									size;
// }										t_env;

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
			enum
			{
				BUILDIN,
				EXEC
			}							e_factor;
			char						**cmds;
			t_redirection_aggregation	*list;
			char						*path_join;
		}								t_factor;
		struct							s_expr
		{
			struct s_ast_node			*left;
			struct s_ast_node			*right;
		}								t_expr;
	}									nodes;
}										t_ast_node;

/*
**listan_node
*/

//muuta nimi parseriks, ja lisää tähän node_list ominaisuus

typedef struct							s_parser_node
{
	enum
	{
		TOKEN,
		AST
	}									e_node;
	union
	{
		t_token							*token;
		t_ast_node						*ast_nodeobj;
	}									nodes;
//	struct s_parser_node_list			*next;
}										t_parser_node;

/*
**lista
*/

typedef struct							s_parser_node_list
{
	t_parser_node						*parser_nodeobj;
	struct s_parser_node_list			*next;
}										t_parser_node_list;

typedef struct							s_ast
{
	t_ast_node							*parent;
	int									cmds;
	int									*pids;
	int									i;
	int									*pipe;
	int									tbc;
	int									in;
	int									out;
	int									err;
	struct s_ast						*next;
}										t_ast;

t_ast_node								*create_factor(char **cmnd, \
										t_redirection_aggregation *list, \
										t_list *env);
t_ast_node								*create_expression(t_ast_node *left, \
										t_ast_node *right);
void									helper_dup(t_ast **ast, \
										t_ast_node *obj, int pipe_in);
void									helper_close(t_ast_node *obj,
										t_ast **ast);
void									exec_factor(t_ast_node *obj,
										t_ast **ast, char **env);
void									visit_factor(t_ast_node *obj,
										t_ast **ast);
void									visit_expression(t_ast_node *obj,
										t_ast **ast, t_terminal *term);
void									add_node_to_parser_node_list(
										t_parser_node_list\
										**list, t_parser_node *ast_node, \
										t_parser_node *token_node);
t_ast									*create_ast_list(
										t_parser_node_list *list);
void									execute_ast(t_ast *ast, t_terminal *term);
t_redirection_aggregation				*tokens_to_redirection(
										t_token *head, t_token *last);
void									free_ast(t_ast *list);
void									free_parser(t_parser_node_list *list);
void									free_tokens(t_token *list);
t_ast									*init_ast(void);
void									buildin_factor(t_ast_node *obj, t_ast **ast, t_terminal *term);
char									*value_lookup(t_list *enviroment, char *key);
int										buildin_cd(t_list *enviroment, char **args);
void									unset_key(t_list *enviroment, char *key);
void									set_key(t_list *enviroment, char *key, char *value);
int										buildin_env(char **env);
int										buildin_unsetenv(t_terminal *term, char **args);
int										buildin_setenv(t_terminal *term, char **args);
void									cmd_not_found(char *cmd);
void									buildin_echo(char **args);
#endif
