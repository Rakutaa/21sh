#ifndef PARSER_AST
# define PARSER_AST

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

/*
**tämä ratkaisu, koska nyt yhdellä nodella voi olla monta redirectionia
**mm. cat << EOF >> file1
**en tiedä mitä muita hyötyä tästä vois olla
*/

typedef struct s_redirection
{
    char								*redir;
    char								*file;
    struct s_redirection				*next;
} 										t_redirection;

/*
**ideana olis et toi enum flagais noden.
**Nyt ASTnodessa tiedetään et millainen
**käsiteltävä data on.
*/

typedef struct s_ast_node {
	enum node { factor, expr }			node;
	union {
		struct {
			char						**cmds;
			t_redirection				*redirection;
		}								factor;
		struct {
			struct s_ast_node		*left;
			struct s_ast_node		*right;
		}								expr;
	}									nodes;
} 										t_ast_node;

typedef struct s_parser_node {
	enum { token, ast }				token_or_ast;
	union {
		struct {
			enum { TOKEN_P, TOKEN_S }	e_type;
		}								token;
		struct {
			t_ast_node					*ast_nodeobj;
		}								ast;
	}									nodes;
}										t_parser_node;

typedef struct s_parser_node_list
{
	t_parser_node						*parser_nodeobj;
	struct s_parser_node_list			*next;
}										t_parser_node_list;

typedef struct s_ast
{
    t_ast_node							*parent;
	int									in;
	int									out;
	int									err;
    struct s_ast						*next;
}										t_ast;

t_ast_node								*create_factor(char **cmnd, t_redirection *redirection);
t_redirection							*create_redirection(char *file, char *sign);
t_ast_node								*create_expression(t_ast_node *left, t_ast_node *right);
void			helper_dup(t_ast **ast, t_ast_node *obj, int pipe_in);
void			helper_close(t_ast_node *obj, t_ast **ast);
void			exec_factor(t_ast_node *obj, t_ast **ast);
void			visit_factor(t_ast_node *obj, t_ast **ast);
void			visit_expression(t_ast_node *obj, t_ast **ast);

void									add_node_to_redirection_list(t_redirection *list, t_redirection *node);
void					    			add_node_to_parser_node_list(t_parser_node_list **list, t_parser_node *ast_node, t_parser_node *token_node);
t_ast									*create_ast_list(t_parser_node_list *list);
void									execute_ast(t_ast *ast);

#endif