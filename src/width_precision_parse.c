/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   width_precision_parse.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igaplich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 17:04:58 by igaplich          #+#    #+#             */
/*   Updated: 2022/06/27 17:05:03 by igaplich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

//Getting STAR argument for width
static int	starwidth_arg(char **str, t_parse *parse, int *param, va_list ap)
{
	*param = va_arg(ap, int);
	if (*param < 0)
	{
		parse->dash = true;
		*param *= -1;
	}
	*str += 1;
	if (ft_isdigit(**str))
	{
		if (width_parse(str, parse, &parse->width, ap) == -1)
			return (-1);
	}
	return (1);
}

//Getting the STAR argument for precision
static int	starprec_arg(char **str, t_parse *parse, int *param, va_list ap)
{
	*param = va_arg(ap, int);
	if (*param < 0)
			*param = -1;
	*str += 1;
	if (ft_isdigit(**str))
	{
		if (precision_parse(str, parse, &parse->precision, ap) == -1)
			return (-1);
	}
	return (1);
}

//Parsing precision, if there's any
int	precision_parse(char **str, t_parse *parse, int *param, va_list ap)
{
	char	*precision;
	char	*last_dig;

	*str += 1;
	if (**str >= '0' && **str <= '9')
	{
		last_dig = *str;
		while (*last_dig >= '0' && *last_dig <= '9')
			last_dig++;
		precision = ft_strsub(*str, 0, (last_dig - *str));
		if (!precision)
			return (-1);
		*param = ft_atoi(precision);
		*str = last_dig;
		free(precision);
	}
	else if (**str == '*')
	{
		if (starprec_arg(str, parse, param, ap) == -1)
			return (-1);
	}
	else
		parse->precision = 0;
	return (1);
}

//Parsing width, if there's any
int	width_parse(char **str, t_parse *parse, int *param, va_list ap)
{
	char	*last_dig;
	char	*width;

	if (**str >= '0' && **str <= '9')
	{
		last_dig = *str;
		while (*last_dig >= '0' && *last_dig <= '9')
			last_dig++;
		width = ft_strsub(*str, 0, (last_dig - *str));
		if (!width)
			return (-1);
		*param = ft_atoi(width);
		*str = last_dig;
		free(width);
	}
	else if (**str == '*')
	{
		if (starwidth_arg(str, parse, param, ap) == -1)
			return (-1);
	}
	return (1);
}
