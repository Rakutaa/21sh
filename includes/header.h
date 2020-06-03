#ifndef INTERPRETER
# define INTERPRETER

/*
**tämä ratkaisu, koska nyt yhdellä nodella voi olla monta redirectionia
**mm. cat << EOF >> file1
**en tiedä mitä muita hyötyä tästä vois olla
*/

typedef struct s_redirection
{
    char					*redir;
    char					*file;
    struct s_redirection	*next;
} t_redirection;

/*
**ideana olis et toi enum flagais noden.
**Nyt ASTnodessa tiedetään et millainen
**käsiteltävä data on.
*/

typedef struct ast_nodeobj {
	enum node { factor, expr } node;
	union {
		struct {
			char **cmds;
			t_redirection *redirection;
		} factor;
		struct {
			struct ast_nodeobj *left;
			struct ast_nodeobj *right;
		} expr;
	} nodes;
} t_ast_nodeobj;

typedef struct parser_nodeobj {
	enum { token, node } tn;
	union {
		struct {
			enum { TOKEN_P, TOKEN_S } e_type;
		} token;
		struct {
			t_ast_nodeobj *ast_nodeobj;
		} node;
	} nodes;
} t_parser_nodeobj;

typedef struct token_node_list
{
	t_parser_nodeobj			*parser_nodeobj;
	struct token_node_list	*next;
} t_token_node_list;

typedef struct s_ast
{
    t_ast_nodeobj       *parent;
	int in, out, err;
    struct s_ast    *next;
} t_ast;

t_ast_nodeobj		*create_factor(char **cmnd, t_redirection *redirection);
t_redirection	*create_redirection(char *file, char *sign);
t_ast_nodeobj		*create_expression(t_ast_nodeobj *left, t_ast_nodeobj *right);

// t_ast_nodeobj *mkcmnd(char **cmnd, t_redirection *redirection);
// t_ast_nodeobj *mkpipe(t_ast_nodeobj *left, t_ast_nodeobj *right);
#endif