/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precision_f.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igaplich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 19:03:17 by igaplich          #+#    #+#             */
/*   Updated: 2022/06/20 19:03:18 by igaplich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

//Rounding fraction part of double, adding +1 to int part if needed
static void	precision_round(char **fraction, int i, long *intpart)
{
	char	old;

	old = '9';
	while (i >= 0 && (*fraction)[i] == '9' && old == '9')
	{
		(*fraction)[i] = '0';
		if ((*fraction)[i] == '0' && old == '9' && i == 0)
			*intpart += 1;
		if (i >= 1 && (*fraction)[i - 1] != '9')
		{
			old = (*fraction)[i - 1];
			(*fraction)[i - 1] += 1;
		}
		i--;
	}
}

//Banker's rounding for zero precision
static void	precision_zero(char **fraction, long *intpart)
{
	if ((*fraction)[0] == '5' && (*intpart + 1) % 2 == 0)
		*intpart += 1;
	else if ((*fraction)[0] > '5')
		*intpart += 1;
	(*fraction)[0] = '\0';
}

//%f fractional part manipulation, if precision is more than zero
static void	precision_nonzero(char **fraction, t_parse *parse, long *intpart)
{
	if (((*fraction)[parse->precision]) >= '5'
		&& (*fraction)[parse->precision] != '\0')
	{
		if ((*fraction)[parse->precision] == '9')
			precision_round(fraction, parse->precision, intpart);
		else if ((*fraction)[parse->precision - 1] != '9')
			(*fraction)[parse->precision - 1] += 1;
		else
			precision_round(fraction, parse->precision - 1, intpart);
	}
	(*fraction)[parse->precision] = '\0';
}

//%f Adding zeroes in the beginning of the fraction if needed, doing precision
int	precision_add_f(t_parse *parse, char **fraction, long *intpart)
{
	char	*tmp;
	int		left;

	left = 19 - ft_strlen(*fraction);
	if (left > 0)
	{
		tmp = *fraction;
		*fraction = ft_strnew(19);
		if (!(*fraction))
		{
			free(tmp);
			return (-1);
		}
		ft_memset(*fraction, '0', left);
		ft_strncpy(&(*fraction)[left], tmp, 19 - left);
		free(tmp);
	}
	if (parse->precision == 0)
		precision_zero(fraction, intpart);
	else
		precision_nonzero(fraction, parse, intpart);
	return (1);
}
