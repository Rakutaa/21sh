#include "lexer.h"

static char	*check_tilde(t_list *enviroment, char *str)
{
	char	*temp;
	char	*value;

	value = search_env(enviroment, "HOME");
	!value ? value = "" : 0;
	if (ft_strequ(str, "~"))
	{
		free(str);
		str = ft_strdup(value);
	}
	else if (str[0] == '~')
	{
		temp = str;
		str = ft_strjoin(value, &str[1]);
		free(temp);
	}
	return (str);
}

static void	free_temp(char *temp, char *temp2)
{
	free(temp);
	free(temp2);
}

static char	*check_dollar(t_list *enviroment, char *str)
{
	size_t	i;
	char	c;
	char	*temp;
	char	*temp2;

	i = -1;
	while (str[++i])
		if (str[i] == '$')
		{
			str[i++] = '\0';
			temp2 = str + i;
			while (ft_isalpha(str[++i]))
				continue ;
			c = str[i];
			str[i] = '\0';
			temp = search_env(enviroment, temp2);
			!temp ? temp = "" : 0;
			temp = ft_strjoin(str, temp);
			str[i] = c;
			temp2 = str;
			str = ft_strjoin(temp, str + i);
			free_temp(temp, temp2);
			i = -1;
		}
	return (str);
}

void					check_dollar_tilde(t_list *env, t_token *token)
{
	if (token->e_type == TOKEN_DQUOTE || token->e_type == TOKEN_WORD)
	{
		token->value = check_dollar(env, token->value);
		token->value = check_tilde(env, token->value);
	}
}