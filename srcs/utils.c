#include "halfsh.h"

int			print_char(int c)
{
	return (write(0, &c, 1));
}
