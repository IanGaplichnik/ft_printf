#include "./includes/ft_printf.h"
#include <stdio.h>
#include <limits.h>

int	main(void)
{
	int res = ft_printf("%.8f", 23.375094499);
	printf("res = %d\n", res);
	res = printf("%.8f", 23.375094499);
	printf("res = %d\n", res);
	return(0);
}