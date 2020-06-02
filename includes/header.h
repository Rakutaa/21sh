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

typedef struct nodeobj {
	enum node { factor, expr } node;
	union {
		struct {
			char **cmds;
			t_redirection *redirection;
		} factor;
		struct {
			struct nodeobj *left;
			struct nodeobj *right;
		} expr;
	} nodes;
} t_nodeobj;

typedef struct nodelist {
	enum { TOKEN_N, TOKEN_P, TOKEN_S } e_type;
	t_nodeobj	*nodeobj;
	struct nodelist	*next;
} t_nodelist;
/*
**execve tyyppinen cmnd ja redirection kertoo
**tuleeko tähän cmnd infoa jostain filestä
**tai meneekö tulostus johonkin fileen
**lisäks redirection kumoaa pipen, mikäli input tulee,
**sekä pipestä, että redirection filestä.
*/

// typedef struct s_node_cmnd
// {
//     char					**cmnd;
//     t_redirection			*redirection;
// } t_node_cmnd;

/*
**tässä left ja right voi olla joko node_cmnd tai node_pipe
*/

// typedef struct s_node_pipe
// {
//     void            *left;
//     void            *right;
// } t_node_pipe;

/*
**parent voi olla, joko node_cmnd tai node_pipe
**next tapahtuu, kun komentorivillä löytyy ;
*/

typedef struct s_ast
{
    t_nodeobj       *parent;
	int in, out, err;
    struct s_ast    *next;
} t_ast;

t_nodeobj		*mkfactor(char **cmnd, t_redirection *redirection);
t_redirection	*mkredir(char *file, char *sign);
t_nodeobj		*mkexpr(t_nodeobj *left, struct nodeobj *right);

// t_nodeobj *mkcmnd(char **cmnd, t_redirection *redirection);
// t_nodeobj *mkpipe(t_nodeobj *left, t_nodeobj *right);
#endif