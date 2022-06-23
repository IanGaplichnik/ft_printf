/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igaplich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 20:22:44 by igaplich          #+#    #+#             */
/*   Updated: 2022/05/11 20:22:46 by igaplich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
#include <limits.h>

void	lengths_prepare(int *num_len, int *str_len, t_parse *parse)
{
	if (parse->precision != -1 || *num_len > parse->width)
		parse->zero = 0;
	*str_len = *num_len;
	if (parse->neg || parse->plus || parse->space)
		*str_len += 1;
	if (*str_len < parse->width)
		*str_len = parse->width;
	if (*str_len < parse->precision)
		*str_len = parse->precision;
}

void	precision_add(t_parse *parse, int *num_len)
{
	char	*tmp;
	int		i;

	i = 0;
	if (parse->precision > *num_len)
	{
		tmp = parse->num;
		parse->num = ft_strnew(parse->precision);
		ft_memset(&parse->num[i], '0', parse->precision - *num_len);
		ft_strcpy(&parse->num[parse->precision - *num_len + i], tmp);
		free(tmp);
		*num_len = parse->precision;
	}
}

void	number_and_space(t_parse *parse, int *str_len, int *i)
{
	ft_strcpy(&parse->cur->data[*i], parse->num);
	*i += ft_strlen(parse->num);
	if (*i < *str_len)
	{
		ft_memset(&parse->cur->data[*i], ' ', *str_len - *i);
		*i = *str_len;
	}
	parse->cur->ret = *i;
}

void	print_di(t_parse *parse)
{
	int		str_len;
	int		num_len;
	int		i;

	if (*parse->num == '0' && parse->precision == 0)
	{
		free(parse->num);
		parse->num = ft_strdup("");
		num_len = 0;
	}
	else
		num_len = ft_strlen(parse->num);
	precision_add(parse, &num_len);
	lengths_prepare(&num_len, &str_len, parse);
	if (str_len == 0)
	{
		free(parse->num);
		return ;
	}
	list_alloc(NULL, parse, str_len);
	i = 0;
	num_width_f(parse, &num_len, &i, &str_len);
	number_and_space(parse, &str_len, &i);
	free(parse->num);
}
