#include "./includes/ft_printf.h"

int main(void)
{
	int ret;
	// int ret_or;
	// ret = ft_printf("Helo %.2s after\n", "Input");
	// ret_or = printf("Helo %.2s after\n", "Input");
	// ret = ft_printf("%s %s %s %s string. gg!", "this", "is", "a", "multi", "string");
	// ret_or = printf("%s %s %s %s string. gg!", "this", "is", "a", "multi", "string");

	ret = ft_printf("% 03d", 634);
	printf("ret = %d\n\n", ret);
	ret = printf("% 03d", 634);
	printf("ret = %d\n\n", ret);
	// printf("%hhd\n", '*');
	// ft_printf("%%", "test");
	// ft_printf("%   %", "test");
	// ret_or = printf("%05% text\n");
	// printf("Ret_or = %d\n", ret_or);
	return (0);
}