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

//Copying letter into list depending on width
static int	copy_c(t_parse *parse, char *letter)
{
	if (parse->width && parse->width > 1)
	{
		if (print_wid(parse, letter, 1) == -1)
			return (-1);
	}
	else if (list_alloc(letter, parse, 1) == -1)
		return (-1);
	return (0);
}

//If %c is NULL, setting the correct length depending on width
static void	c_null(char *letter, t_parse *parse)
{
	if (letter[0] == '\0')
	{
		if (parse->width > 1)
			parse->cur->ret = parse->width;
		else
			parse->cur->ret = 1;
	}
}

//%c printing algorithm beginning
int	print_c(t_parse *parse, va_list ap)
{
	char	*letter;

	letter = ft_strnew(1);
	if (!letter)
		return (-1);
	letter[0] = (char)va_arg(ap, int);
	if (copy_c(parse, letter) == -1)
	{
		free(letter);
		return (-1);
	}
	parse->cur->ret = ft_strlen(parse->cur->data);
	c_null(letter, parse);
	free(letter);
	return (1);
}
