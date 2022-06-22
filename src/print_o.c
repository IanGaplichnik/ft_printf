/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_o.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igaplich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 12:14:03 by igaplich          #+#    #+#             */
/*   Updated: 2022/06/10 12:14:27 by igaplich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	num_width_o(t_parse *parse, int *num_len, int *i, int *str_len)
{
	if (*num_len < parse->width && !parse->dash)
	{
		if (parse->zero)
			ft_memset(&parse->cur->data[*i], '0', *str_len - *num_len);
		else if (!parse->zero)
			ft_memset(&parse->cur->data[*i], ' ', *str_len - *num_len);
		*i = *str_len - *num_len;
	}
	if (parse->hash)
		parse->cur->data[(*i)++] = '0';
}

void	lengths_prepare_o(int *num_len, int *str_len, t_parse *parse)
{
	if (parse->precision != -1)
		parse->zero = 0;
	if (parse->hash)
		*num_len += 1;
	*str_len = *num_len;
	if (*str_len < parse->width)
		*str_len = parse->width;
	if (*str_len < parse->precision)
		*str_len = parse->precision;
}

void	print_o(t_parse *parse)
{
	int	str_len;
	int	num_len;
	int	i;

	num_len = ft_strlen(parse->num);
	if ((*parse->num == '0' && parse->precision == 0)
		|| (*parse->num == '0' && parse->hash))
	{
		free(parse->num);
		parse->num = ft_strdup("");
		num_len = 0;
	}
	lengths_prepare_o(&num_len, &str_len, parse);
	precision_add(parse, &num_len);
	if (str_len == 0)
		return ;
	list_alloc(NULL, parse, str_len);
	i = 0;
	num_width_o(parse, &num_len, &i, &str_len);
	ft_strcpy(&parse->cur->data[i], parse->num);
	i += ft_strlen(parse->num);
	if (i < str_len)
	{
		ft_memset(&parse->cur->data[i], ' ', str_len - i);
		i = str_len;
	}
	parse->cur->ret = i;
	free(parse->num);
}