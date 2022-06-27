/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_c.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igaplich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 18:24:39 by igaplich          #+#    #+#             */
/*   Updated: 2022/06/22 18:24:42 by igaplich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	print_c(t_parse *parse, va_list ap)
{
	char	*letter;

	letter = ft_strnew(1);
	letter[0] = (char)va_arg(ap, int);
	if (parse->width && parse->width > 1)
		print_wid(parse, letter, 1);
	else
		list_alloc(letter, parse, 1);
	parse->cur->ret = ft_strlen(parse->cur->data);
	if (letter[0] == '\0')
	{
		if (parse->width > 1)
			parse->cur->ret = parse->width;
		else
			parse->cur->ret = 1;
	}
	free(letter);
	return (0);
}
