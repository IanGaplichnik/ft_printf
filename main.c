#include "./includes/ft_printf.h"

int main(void)
{
	int ret;
	// int ret_or;
	// ret = ft_printf("Helo %.2s after\n", "Input");
	// ret_or = printf("Helo %.2s after\n", "Input");
	// ret = ft_printf("%s %s %s %s string. gg!", "this", "is", "a", "multi", "string");
	// ret_or = printf("%s %s %s %s string. gg!", "this", "is", "a", "multi", "string");
	ret = 8;
	ret = ft_printf("%hd", '*');
	printf("%hhd\n", '*');
	// ft_printf("%%", "test");
	// ft_printf("%   %", "test");
	// ret_or = printf("%05% text\n");
	// printf("Ret_or = %d\n", ret_or);
	return (0);
}

/*

if precision > len(str)
	len(str) = len(str)
if precision < len(str)
	len = precision

if !width
	write (len(str))

if width
		if len(str) < width
			if !dash
				write (len(str)) && write (width - len(str) ' ')
			if dash
				write (width - len(str)' ' ) && write (precision)
		if len(str) > width
			write (len(str))

			*/