#include "./includes/ft_printf.h"
#include <stdio.h>
#include <limits.h>

int	main(void)
{
	int res = ft_printf("%f", 0.000039);
	printf("res = %d\n", res);
	res = printf("%f", 0.000039);
	printf("res = %d\n", res);
	return(0);
}