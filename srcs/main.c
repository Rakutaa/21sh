#include "halfsh.h"
#include "get_next_line.h"

static void	display_prompt(void)
{
	write(1, "$>", 2);
}

int		main(void)
{
	char	*input;

	while (1)
	{
		display_prompt();
		if (get_next_line(1, &input) == 0)
			break ;
		ft_printf("%s\n", input);
		free(input);
	}
	return (0);
}
