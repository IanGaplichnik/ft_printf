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

void	print_struct(t_parse *parse, char *state)
{
	printf("\n\n%s\n", state);
	printf("# = %s\n", parse->hash ? "true" : "false");
	printf("- = %s\n", parse->dash ? "true" : "false");
	printf("0 = %s\n", parse->zero ? "true" : "false");
	printf("+ = %s\n", parse->plus ? "true" : "false");
	printf("' ' = %s \n", parse->space ? "true" : "false");
	printf("Width = %d\n", parse->width);
	printf("Prec = %d\n", parse->precision);
	printf("Len = %d\n", parse->length);
	printf("Conv = %c\n", parse->conv);
}

void	flag_mark(char flag, t_parse *parse)
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

void	flag_parse(char **str, t_parse *parse)
{
	char	*flag;

	flag = NULL;
	*str += 1;
	while (ft_strchr(FLAGS, **str))
	{
		flag = ft_strchr(FLAGS, **str);
		if (flag != NULL)
			flag_mark(*flag, parse);
		flag = NULL;
		*str += 1;
	}
	free(flag);
}

void	widprec_parse(char **str, t_parse *parse, int *param)
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
	if (**str == '.')
	{
		*str += 1;
		if (**str >= '0' && **str <= '9')
			widprec_parse(str, parse, &parse->precision);
		else
			parse->precision = 0;
	}
}

void	length_parse(char **str, t_parse *parse)
{
	if (!ft_strncmp(*str, "hh", 2))
		parse->length = 1;
	else if (**str == 'h')
		parse->length = 2;
	if (!ft_strncmp(*str, "ll", 2))
		parse->length = 3;
	else if (**str == 'l')
		parse->length = 4;
	if (**str == 'L')
		parse->length = 5;
	if (parse->length == 1 || parse->length == 3)
		*str += 2;
	if (parse->length == 2 || parse->length == 4 || parse->length == 5)
		*str += 1;
}

void	conv_parse(char **str, t_parse *parse)
{
	if (ft_strchr(CONV, **str))
	{
		parse->conv = **str;
		*str += 1;
	}
}

int	percent_parse(char **str, t_parse *parse)
{
	int	ret;

	ret = 0;
	flag_parse(str, parse);
	widprec_parse(str, parse, &parse->width);
	length_parse(str, parse);
	conv_parse(str, parse);
	// print_struct(parse, "");
	ret += print_conversion(parse);
	return (ret);
}
