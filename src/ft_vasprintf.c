/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vasprintf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igaplich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 14:07:05 by igaplich          #+#    #+#             */
/*   Updated: 2022/06/27 14:07:15 by igaplich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

//Freeing struct and linked list in the end of execution or in case of error
int	clean_printf(t_parse *parse)
{
	t_ret	*tmp;

	tmp = parse->head;
	parse->cur = parse->head;
	while (parse->cur)
	{
		parse->cur = parse->cur->next;
		if (tmp->data)
			free(tmp->data);
		free(tmp);
		tmp = parse->cur;
	}
	if (parse->num)
		free(parse->num);
	free(parse);
	return (-1);
}

//Allocating a struct and linked list inside of that struct
int	alloc_init(t_parse **parse, char **str, const char *format)
{
	*str = (char *)format;
	*parse = (t_parse *)malloc(sizeof(t_parse));
	if (!(*parse))
		return (-1);
	parse_init(*parse);
	(*parse)->head = NULL;
	(*parse)->cur = NULL;
	return (1);
}

//Main parsing algorithm reading FORMAT string
int	parser(t_parse *parse, char *str, va_list ap)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '%')
		{
			if (list_alloc(str, parse, i) == -1)
				return (-1);
			str += i;
			if (percent_parse(&str, parse, ap) == -1)
				return (-1);
			i = 0;
		}
		else
			i++;
	}
	if (list_alloc(str, parse, i) == -1)
		return (-1);
	return (1);
}

//Implementation of vasprintf function
int	ft_vasprintf(char **ret, const char *format, va_list ap)
{
	int		return_value;
	char	*str;
	t_parse	*parse;

	if (alloc_init(&parse, &str, format) == -1)
		return (clean_printf(parse));
	if (parser(parse, str, ap) == -1)
		return (clean_printf(parse));
	return_value = str_build(parse, ret);
	if (return_value < 0)
		return (clean_printf(parse));
	return (return_value);
}
