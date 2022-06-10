/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_oux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igaplich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 17:57:37 by igaplich          #+#    #+#             */
/*   Updated: 2022/06/08 17:57:46 by igaplich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	num_width_uxX(t_parse *parse, int *num_len, int *i, int *str_len)
{
	
	if (((*num_len < parse->width && !parse->hash)
		|| ((*num_len + 2) < parse->width && parse->hash)) && !parse->dash)
	{
		if (parse->hash && !parse->zero)
			*num_len += 2;
		if (parse->zero)
			ft_memset(&parse->cur->data[*i], '0', *str_len - *num_len);
		else if (!parse->zero)
			ft_memset(&parse->cur->data[*i], ' ', *str_len - *num_len);
		if (parse->hash && parse->zero)
			parse->cur->data[1] = parse->conv;
		*i = *str_len - *num_len;
	}
	if (parse->hash && (!parse->zero
		|| (parse->zero && parse->width && (parse->width < *num_len))))
	{
		parse->cur->data[(*i)++] = '0';
		parse->cur->data[(*i)++] = parse->conv;
	}
}

void	lengths_prepare_uxX(int *num_len, int *str_len, t_parse *parse)
{
	if (parse->precision != -1)
		parse->zero = 0;
	*str_len = *num_len;
	if (*str_len < parse->width)
		*str_len = parse->width;
	if (*str_len < parse->precision)
		*str_len = parse->precision;
}

void	print_uxX(t_parse *parse)
{
	int		str_len;
	int		num_len;
	int		i;

	num_len = ft_strlen(parse->num);
	if (*parse->num == '0')
		parse->hash = 0;
	if (*parse->num == '0' && parse->precision == 0 && parse->conv != 'o')
	{
		free(parse->num);
		parse->num = ft_strdup("");
		num_len = 0;
	}
	lengths_prepare_uxX(&num_len, &str_len, parse);
	precision_add(parse, &num_len);
	if (str_len == 0)
		return ;
	list_alloc(NULL, parse, str_len);
	i = 0;
	num_width_uxX(parse, &num_len, &i, &str_len);
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