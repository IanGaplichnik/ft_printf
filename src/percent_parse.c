/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   percent_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igaplich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 12:25:56 by igaplich          #+#    #+#             */
/*   Updated: 2022/05/04 12:25:58 by igaplich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
#include <stdio.h>

static void	flag_mark(char flag, t_parse *parse)
{
	if (flag == '#')
		parse->hash = true;
	if (flag == '-')
	{
		parse->dash = true;
		parse->zero = false;
	}
	if (flag == '0' && parse->dash == false)
		parse->zero = true;
	if (flag == '+')
	{
		parse->plus = true;
		parse->space = false;
	}
	if (flag == ' ' && parse->plus == false)
		parse->space = true;
}

static void	flag_parse(char **str, t_parse *parse)
{
	char	*flag;

	flag = NULL;
	*str += 1;
	while (**str != '\0' && ft_strchr(FLAGS, **str))
	{
		flag = ft_strchr(FLAGS, **str);
		if (flag != NULL)
			flag_mark(*flag, parse);
		flag = NULL;
		*str += 1;
	}
	free(flag);
}

static void	length_parse(char **str, t_parse *parse)
{
	if (!ft_strncmp(*str, "hh", 2))
		parse->length = 1;
	else if (**str == 'h')
		parse->length = 2;
	else if (!ft_strncmp(*str, "ll", 2))
		parse->length = 3;
	else if (**str == 'l')
		parse->length = 4;
	else if (**str == 'L')
		parse->length = 5;
	if (str[0][1] && str[0][2] && (parse->length == 1 || parse->length == 3))
		*str += 2;
	else if (str[0][1] && (parse->length == 2 || parse->length == 4
		|| parse->length == 5))
		*str += 1;
}

static int	conv_parse(char **str, t_parse *parse)
{
	if (ft_strchr(CONV, **str))
	{
		parse->conv = **str;
		*str += 1;
		return (1);
	}
	*str += 1;
	return (0);
}

int	percent_parse(char **str, t_parse *parse, va_list ap)
{
	flag_parse(str, parse);
	if (**str != '\0')
	{
		width_parse(str, parse, &parse->width, ap);
		precision_parse(str, parse, &parse->precision, ap);
		length_parse(str, parse);
		if (conv_parse(str, parse) == 0)
		{
			parse_init(parse);
			return (0);
		}
		print_conversion(parse, ap);
	}
	parse_init(parse);
	return (1);
}
