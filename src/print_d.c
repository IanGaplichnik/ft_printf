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

static void	lengths_prepare(int *num_len, int *str_len, t_parse *parse)
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

int	precision_add(t_parse *parse, int *num_len)
{
	char	*tmp;
	int		i;

	i = 0;
	if (parse->precision > *num_len)
	{
		tmp = parse->num;
		parse->num = ft_strnew(parse->precision);
		if (!parse->num)
		{
			free (tmp);
			return (-1);
		}
		ft_memset(&parse->num[i], '0', parse->precision - *num_len);
		ft_strcpy(&parse->num[parse->precision - *num_len + i], tmp);
		free(tmp);
		*num_len = parse->precision;
	}
	return (1);
}

//Copying number and adding spaces after if required by precision
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

//Increasing precision, until it prints the whole byte
static void	b_print_length(t_parse *parse, int *num_len)
{
	parse->precision = *num_len;
	while (parse->precision % 8 != 0)
		parse->precision += 1;
}

//%di printing algorithm
int	print_di(t_parse *parse, int base)
{
	int		str_len;
	int		num_len;
	int		i;

	if (*parse->num == '0' && parse->precision == 0)
		parse->num[0] = '\0';
	num_len = ft_strlen(parse->num);
	if (base == 2)
		b_print_length(parse, &num_len);
	if (precision_add(parse, &num_len) == -1)
		return (-1);
	lengths_prepare(&num_len, &str_len, parse);
	if (str_len == 0)
	{
		free(parse->num);
		return (1);
	}
	if (list_alloc(NULL, parse, str_len) == -1)
		return (-1);
	i = 0;
	num_width_f(parse, &num_len, &i, &str_len);
	number_and_space(parse, &str_len, &i);
	free(parse->num);
	return (1);
}
