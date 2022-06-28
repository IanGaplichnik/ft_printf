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

//%p printing algo
int	print_perc(t_parse *parse)
{
	char	*conv;

	conv = ft_strnew(1);
	if (!conv)
		return (-1);
	conv[0] = '%';
	if (parse->width && parse->width > 1)
	{
		if (print_wid(parse, conv, 1) == -1)
		{
			free(conv);
			return (-1);
		}
	}
	else if (list_alloc(conv, parse, 1) == -1)
	{
		free(conv);
		return (-1);
	}
	parse->cur->ret = ft_strlen(parse->cur->data);
	free(conv);
	return (0);
}
