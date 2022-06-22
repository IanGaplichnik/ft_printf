/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_oux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igaplich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 17:57:37 by igaplich          #+#    #+#             */
/*   Updated: 2022/06/22 13:11:01 by igaplich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	num_width_ux(t_parse *parse, int *num_len, int *i, int *str_len)
{
	if (*num_len < parse->width && !parse->dash)
	{
		if (parse->zero)
			ft_memset(&parse->cur->data[*i], '0', *str_len - *num_len);
		else if (!parse->zero)
		{
			ft_memset(&parse->cur->data[*i], ' ', *str_len - *num_len);
			*i += *str_len - *num_len;
			if (parse->hash || parse->conv == 'p')
				*i -= 2;
		}
	}
	if (parse->hash || parse->conv == 'p')
	{
		if (parse->conv == 'p')
			parse->conv = 'x';
		parse->cur->data[(*i)++] = '0';
		parse->cur->data[*i] = parse->conv;
	}
	*i = ft_strlen(parse->cur->data);
}

void	lengths_prepare_ux(int *num_len, int *str_len, t_parse *parse)
{
	if (parse->precision != -1)
		parse->zero = 0;
	*str_len = *num_len;
	if (parse->hash || parse->conv == 'p')
		*str_len += 2;
	if (*str_len < parse->width)
		*str_len = parse->width;
	if (*str_len < parse->precision)
	{
		*str_len = parse->precision;
		if (parse->hash || parse->conv == 'p')
			*str_len += 2;
	}
}

void	print_ux(t_parse *parse)
{
	int	str_len;
	int	num_len;
	int	i;

	num_len = ft_strlen(parse->num);
	if (*parse->num == '0')
		parse->hash = 0;
	if (*parse->num == '0' && parse->precision == 0 && parse->conv != 'p')
	{
		free(parse->num);
		parse->num = ft_strdup("");
		num_len = 0;
	}
	lengths_prepare_ux(&num_len, &str_len, parse);
	if (str_len == 0)
		return ;
	precision_add(parse, &num_len);
	list_alloc(NULL, parse, str_len);
	i = 0;
	num_width_ux(parse, &num_len, &i, &str_len);
	number_and_space(parse, &str_len, &i);
	free(parse->num);
}
