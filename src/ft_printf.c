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

t_parse	*parse_init(t_parse *parse)
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
	return (parse);
}

void	list_alloc(char *str, t_parse *parse, int i)
{
	t_ret	*new;

	if (i == 0)
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
	parse->cur->data = ft_strnew(i + 1);
	if (str != NULL)
	{
		ft_strncpy(parse->cur->data, str, i);
		parse->cur->ret = ft_strlen(parse->cur->data);
	}
	else
		ft_memset(parse->cur->data, '\0', i + 1);
}

int	print_reverse(t_parse *parse)
{
	int		j = 1;
	int		ret;
	t_ret	*tmp;

	ret = 0;
	tmp = parse->head;
	while (tmp)
	{
		printf("\n%sNODE %d%s\n", RED, j, REG);
		printf("|%s|", tmp->data);
		printf("\nNODE LENGTH = %d\n\n", tmp->ret);
		ret += tmp->ret;
		tmp = tmp->next;
		j++;
	}
	printf("Return = %d\n", ret);
	tmp = parse->head;
	while (tmp)
	{
		printf("%s", tmp->data);
		tmp = tmp->next;
	}
	return (ret);
}


int	print_test(t_parse *parse)
{
	int		ret;
	t_ret	*tmp;

	ret = 0;
	tmp = parse->head;
	while (tmp)
	{
		ret += tmp->ret;
		write(1, tmp->data, tmp->ret);
		tmp = tmp->next;
	}
	return (ret);
}

int	ft_printf(const char *format, ...)
{
	char	*str;
	t_parse	*parse;
	int		i;

	i = 0;
	str = (char *)format;
	parse = (t_parse *)malloc(sizeof(t_parse));
	parse->head = NULL;
	parse_init(parse);
	va_start(parse->ap, format);
	while (str[i] != '\0')
	{
		if (str[i] == '%' && str[1])
		{
			list_alloc(str, parse, i);
			str += i;
			percent_parse(&str, parse);
			i = 0;
		}
		else
			i++;
	}
	list_alloc(str, parse, i);
	va_end(parse->ap);
	return(print_test(parse));
	// return (print_reverse(parse));
}
