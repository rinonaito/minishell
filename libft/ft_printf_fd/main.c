#include	"ft_printf.h"

int main(void)
{
	ft_printf(STDERR_FILENO, "bash: %s: command not found\n", "hello");
	return (0);
}
