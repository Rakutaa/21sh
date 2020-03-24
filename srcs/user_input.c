#include "halfsh.h"
#include "keyboard.h"

static void	display_prompt(void)
{
	write(1, "$>", 2);
}

static int	listen_keys(void)
{
	char	key[KEY_SIZE + 1];
	ssize_t	bytes;
	size_t	i;
	int	sum;

	bytes = read(1, key, KEY_SIZE);
	key[bytes] = '\0';
	i = -1;
	sum = 0;
	while (key[++i])
		sum += key[i];
	return (sum);
}

static void	display_input(t_terminal *term, char *input)
{
	size_t	count;
	int	sum;

	count = 0;
	while (term)
	{
		sum = listen_keys();
		if (sum == ENTER)
			return ;
		if (ft_isprint(sum))
		{
			input[count] = sum;	
			ft_putchar(sum);
			count++;
		}
	}
}

void		user_input(t_terminal *term)
{
	char 	input[ARG_MAX];

	while (term)
	{	
		ft_bzero(input, ARG_MAX);
		display_prompt();
		display_input(term, input);
		// TODO Execution.
		ft_printf("\nUNDER CONSTRUCTION\n");
	}
}
