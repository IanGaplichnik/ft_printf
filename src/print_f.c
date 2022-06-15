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

void	precision_round(t_parse *parse, char **fraction)
{
	int		i;
	char	old;

	i = parse->precision;
	old = '9';
	while ((*fraction)[i] == '9' && i >= 0 && old == '9')
	{
		(*fraction)[i] = '0';
		if ((*fraction)[i - 1] && (*fraction)[i - 1] != '9')
		{
			old = (*fraction)[i - 1];
			(*fraction)[i - 1] += 1;
		}
		i--;
	}
}

void	precision_add_f(t_parse *parse, char **fraction)
{
	char	*tmp;
	int		left;
	char	old;

	left = 18 - ft_strlen(*fraction);
	if (left > 0)
	{
		tmp = *fraction;
		*fraction = ft_strnew(18);
		ft_memset(*fraction, '0', left);
		ft_strncpy(&(*fraction)[left], tmp, 18 - left);
		free(tmp);
	}
	if (((*fraction)[parse->precision]) >= '5'
		&& (*fraction)[parse->precision] != '\0')
	{
		if ((*fraction)[parse->precision] == '9')
			precision_round(parse, fraction);
		else if ((*fraction)[parse->precision - 1] != '9')
			(*fraction)[parse->precision - 1] += 1;
		else
		{
			(*fraction)[parse->precision] = '9';
			precision_round(parse, fraction);
		}
	}
	(*fraction)[parse->precision] = '\0';
}

void	precision_zero(t_parse *parse, char **fraction, char **intpart)
{
	char	old;
	int		i;

	i = ft_strlen(*intpart) - 1;
	old = '9';
	if ((*fraction)[0] >= '5')
	{
		old = (*intpart)[i];
		(*intpart)[i] += 1;
		while (old == '9' && (*intpart)[i] == '9' && i >= 0)
			{
				(*intpart)[i] = '0';
				if ((*intpart)[i - 1] && (*intpart)[i - 1] != '9')
				{
					old = (*intpart)[i - 1];
					(*intpart)[i - 1] += 1;
				}
			}
			i--;
	}
}

void	print_f(t_parse *parse)
{
	double	full;
	char		*intpart;
	char		*fraction;
	char		*tmp;

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
	if (parse->neg)
	{
		tmp = intpart;
		intpart = ft_strjoin ("-", intpart);
		free(tmp);
	}
	if (parse->precision != 0)
	{
		precision_add_f(parse, &fraction);
		tmp = parse->num;
		parse->num = ft_strjoin(intpart, ".");
		free(tmp);
		tmp = parse->num;
		parse->num = ft_strjoin(parse->num, fraction);
		free(tmp);
	}
	else
	{
		precision_zero(parse, &fraction, &intpart);
		parse->num = intpart;
	}
	list_alloc(parse->num, parse, ft_strlen(parse->num));
	if (intpart)
		free(intpart);
}
