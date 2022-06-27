/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igaplich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 18:07:28 by igaplich          #+#    #+#             */
/*   Updated: 2022/04/25 19:46:03 by igaplich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
#include <stdio.h>

void	parse_init(t_parse *parse)
{
	parse->hash = false;
	parse->dash = false;
	parse->space = false;
	parse->plus = false;
	parse->zero = false;
	parse->width = 0;
	parse->precision = -1;
	parse->length = 0;
	parse->conv = 0;
	parse->neg = 0;
	parse->num = NULL;
}

static void	list_fill(char *str, t_parse *parse, int len)
{
	parse->cur->data = ft_strnew(len + 1);
	if (str != NULL)
	{
		ft_strncpy(parse->cur->data, str, len);
		parse->cur->ret = ft_strlen(parse->cur->data);
	}
}

void	list_alloc(char *str, t_parse *parse, int len)
{
	t_ret	*new;

	if (len == 0)
		return ;
	new = (t_ret *)malloc(sizeof(t_ret));
	new->next = NULL;
	new->ret = 0;
	if (!parse->head)
	{
		parse->head = new;
		parse->cur = parse->head;
	}
	else
	{
		while (parse->cur->next)
			parse->cur = parse->cur->next;
		parse->cur->next = new;
		parse->cur = parse->cur->next;
	}
	list_fill(str, parse, len);
}

int	ft_printf(const char *format, ...)
{
	char	*ret_str;
	int		ret;
	va_list	ap;

	if (!format)
		return (-1);
	va_start(ap, format);
	ret = ft_vasprintf(&ret_str, format, ap);
	va_end(ap);
	if (ret < 0)
		return (-1);
	if (ret != 0)
	{
		write(1, ret_str, ret);
		free(ret_str);
	}
	return (ret);
}
