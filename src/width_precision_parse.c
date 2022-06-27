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

static void	starwidth_arg(char **str, t_parse *parse, int *param, va_list ap)
{
	*param = va_arg(ap, int);
	if (*param < 0)
	{
		parse->dash = true;
		*param *= -1;
	}
	*str += 1;
	if (ft_isdigit(**str))
		width_parse(str, parse, &parse->width, ap);
}

static void	starprec_arg(char **str, t_parse *parse, int *param, va_list ap)
{
	*param = va_arg(ap, int);
	if (*param < 0)
			*param = -1;
	*str += 1;
	if (ft_isdigit(**str))
		precision_parse(str, parse, &parse->precision, ap);
}

void	precision_parse(char **str, t_parse *parse, int *param, va_list ap)
{
	char	*precision;
	char	*last_dig;

	if (**str == '.')
	{
		*str += 1;
		if (**str >= '0' && **str <= '9')
		{
			last_dig = *str;
			while (*last_dig >= '0' && *last_dig <= '9')
				last_dig++;
			precision = ft_strsub(*str, 0, (last_dig - *str));
			*param = ft_atoi(precision);
			*str = last_dig;
			free(precision);
		}
		else if (**str == '*')
			starprec_arg(str, parse, param, ap);
		else
			parse->precision = 0;
	}
}

void	width_parse(char **str, t_parse *parse, int *param, va_list ap)
{
	char	*last_dig;
	char	*width;

	if (**str >= '0' && **str <= '9')
	{
		last_dig = *str;
		while (*last_dig >= '0' && *last_dig <= '9')
			last_dig++;
		width = ft_strsub(*str, 0, (last_dig - *str));
		*param = ft_atoi(width);
		*str = last_dig;
		free(width);
	}
	else if (**str == '*')
		starwidth_arg(str, parse, param, ap);
}