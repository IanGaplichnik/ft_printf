/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_f.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igaplich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 15:37:58 by igaplich          #+#    #+#             */
/*   Updated: 2022/06/10 15:37:59 by igaplich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
#include <limits.h>
#include <math.h>

void	precision_f(t_parse *parse, char *fraction)
{
	char	*tmp;
	int		left;
	if (ft_strlen(fraction) < 18)
	{
		left = 18 - ft_strlen(fraction);
		tmp = fraction;
		fraction = ft_strnew(18);
		ft_memset(fraction, '0', left);
		ft_strncpy(&fraction[left], tmp, 18 - left);
		free(tmp);
	}
	fraction[parse->precision] = '\0';
}

void	print_f(t_parse *parse)
{
	long double	full;
	char		*intpart;
	char		*fraction;

	full = va_arg(parse->ap, double);
	if (full < 0)
	{
		full = -full;
		parse->neg = 1;
	}
	intpart = ft_itoa_base((int)full, 10, 0);
	fraction = ft_itoa_base((long long)((full - (int)full) * pow(10, 18)),
			10, 0);
	if (parse->precision == -1)
		parse->precision = 6;
	precision_f(parse, fraction);
	if (parse->neg)
		intpart = ft_strjoin ("-", intpart);
	parse->num = ft_strjoin(intpart, ".");
	parse->num = ft_strjoin(parse->num, fraction);
	list_alloc(parse->num, parse, ft_strlen(parse->num));
}

/*TODO:
add zeroes before fraction, based on ((intmax_t_len - 1) - fraction_len)
*/