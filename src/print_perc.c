/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_perc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igaplich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 18:23:21 by igaplich          #+#    #+#             */
/*   Updated: 2022/06/22 18:23:23 by igaplich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	print_perc(t_parse *parse)
{
	char	*conv;

	conv = ft_strnew(1);
	conv[0] = '%';
	if (parse->width && parse->width > 1)
		print_wid(parse, conv, 1);
	else
		list_alloc(conv, parse, 1);
	parse->cur->ret = ft_strlen(parse->cur->data);
	free(conv);
	return (0);
}
