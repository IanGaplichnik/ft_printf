/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_f2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igaplich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 17:39:13 by igaplich          #+#    #+#             */
/*   Updated: 2022/06/28 17:39:16 by igaplich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

//Preparing length of resulting string and length of number itself for %f
static int	lengths_prepare_f(t_parse *parse, long *intpart,
		int *num_len, int *str_len)
{
	if (parse->neg || parse->plus)
		parse->space = false;
	*num_len = ft_unumlenbase(*intpart, 10) + parse->precision;
	if ((parse->hash && parse->precision == 0) || parse->precision != 0)
		*num_len += 1;
	*str_len = *num_len;
	if (parse->neg || parse->plus || parse->space)
		*str_len += 1;
	if (*str_len < parse->width)
		*str_len = parse->width;
	if (*str_len != 0)
	{
		if (list_alloc(NULL, parse, *str_len) == -1)
			return (-1);
	}
	return (1);
}

//Handling width for %f
void	num_width_f(t_parse *parse, int *num_len, int *i, int *str_len)
{
	if (*num_len < parse->width && !parse->dash)
	{
		if (parse->zero)
			ft_memset(&parse->cur->data[*i], '0', *str_len - *num_len);
		else if (!parse->zero)
		{
			ft_memset(&parse->cur->data[*i], ' ', *str_len - *num_len);
			*i += *str_len - *num_len;
			if (parse->neg || parse->plus || parse->space)
				*i -= 1;
		}
	}
	if (parse->neg || parse->plus || parse->space)
	{
		if (parse->neg)
			parse->cur->data[*i] = '-';
		else if (parse->plus)
			parse->cur->data[*i] = '+';
		else if (parse->space)
			parse->cur->data[*i] = ' ';
	}
	*i = ft_strlen(parse->cur->data);
}

/*Combining int part, dot, fraction and spaces after
in the resulting string for %f*/
static void	number_and_space_f(t_parse *parse, int *i,
		int *str_len, char *fraction)
{
	ft_strcpy(&parse->cur->data[*i], parse->num);
	*i += ft_strlen(parse->num);
	if (parse->precision != 0 || parse->hash)
		parse->cur->data[(*i)++] = '.';
	if (parse->precision != 0)
	{
		ft_strcpy(&parse->cur->data[*i], fraction);
		*i += ft_strlen(fraction);
	}
	if (*i < parse->width)
	{
		ft_memset(&parse->cur->data[*i], ' ', *str_len - *i);
		*i = *str_len;
	}
	parse->cur->ret = *i;
}

//If result of %f is NOT nan or inf/-inf
int	print_fn(t_parse *parse, long *intpart, char **fraction)
{
	int		str_len;
	int		num_len;
	int		i;

	i = 0;
	if (precision_add_f(parse, fraction, intpart) == -1)
		return (-1);
	parse->num = ft_uitoa_base(*intpart, 10, 0);
	if (!parse->num)
		return (-1);
	if (lengths_prepare_f(parse, intpart, &num_len, &str_len) == -1)
		return (-1);
	num_width_f(parse, &num_len, &i, &str_len);
	number_and_space_f(parse, &i, &str_len, *fraction);
	free(*fraction);
	free(parse->num);
	return (1);
}
