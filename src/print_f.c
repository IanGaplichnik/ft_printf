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

void	precision_round(t_parse *parse, char **fraction, int i, int *intpart)
{
	char	old;

	if (i == -1)
		i = parse->precision;
	old = '9';
	while ((*fraction)[i] == '9' && i >= 0 && old == '9')
	{
		(*fraction)[i] = '0';
		if ((*fraction)[i] == '0' && old == '9' && i == 0)
			*intpart += 1;
		if ((*fraction)[i - 1] && (*fraction)[i - 1] != '9')
		{
			old = (*fraction)[i - 1];
			(*fraction)[i - 1] += 1;
		}
		i--;
	}
}

void	precision_zero(t_parse *parse, char **fraction, int *intpart)
{
	int		i;

	if ((*fraction)[0] == '5' && (*intpart + 1) % 2 == 0) 
		*intpart += 1;
	else if ((*fraction)[0] > '5')
		*intpart += 1;
	(*fraction)[0] = '\0';
}

void	precision_add_f(t_parse *parse, char **fraction, int *intpart)
{
	char	*tmp;
	int		left;
	char	old;

	left = 19 - ft_strlen(*fraction);
	if (left > 0)
	{
		tmp = *fraction;
		*fraction = ft_strnew(19);
		ft_memset(*fraction, '0', left);
		ft_strncpy(&(*fraction)[left], tmp, 19 - left);
		free(tmp);
	}
	if (parse->precision == 0)
		precision_zero(parse, fraction, intpart);
	else
	{
		if (((*fraction)[parse->precision]) >= '5' && (*fraction)[parse->precision] != '\0')
		{
			if ((*fraction)[parse->precision] == '9')
				precision_round(parse, fraction, -1, intpart);
			else if ((*fraction)[parse->precision - 1] != '9')
				(*fraction)[parse->precision - 1] += 1;
			else
				precision_round(parse, fraction, parse->precision - 1, intpart);
		}
		(*fraction)[parse->precision] = '\0';
	}
}

void	print_f(t_parse *parse)
{
	long double	full;
	char		*int_str;
	int			intpart;
	char		*fraction;
	char		*tmp;

	full = va_arg(parse->ap, double);
	if (full < 0 || (1 / full == -INFINITY))
	{
		full = -full;
		parse->neg = 1;
	}
	intpart = (int)full;
	fraction = ft_uitoa_base((unsigned long long)((full - intpart) * pow(10, 19)),
			10, 0); //CHANGE POW
	if (parse->precision == -1)
		parse->precision = 6;
	precision_add_f(parse, &fraction, &intpart);
	int_str = ft_uitoa_base(intpart, 10, 0);
	if (parse->precision != 0 || parse->hash)
		parse->num = ft_strjoin(int_str, ".");
	else
		parse->num = int_str;
	parse->num = ft_strjoin(parse->num, fraction);
	if (parse->neg)
		parse->num = ft_strjoin("-", parse->num);
	else if (parse->plus && !parse->neg)
		parse->num = ft_strjoin("+", parse->num);
	list_alloc(parse->num, parse, ft_strlen(parse->num));
	free(int_str);
}
