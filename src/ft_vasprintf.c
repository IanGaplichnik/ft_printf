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

static void	ft_lencpy(char *dst, const char *src, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		dst[i] = src[i];
		i++;
	}
}

static int	copy_to_res(t_parse *parse, char **ret, size_t *str_len)
{
	t_ret	*tmp;
	int		i;

	i = 0;
	*ret = ft_strnew(*str_len);
	if (!(*ret))
		return (-1);
	tmp = parse->head;
	while (parse->cur)
	{
		ft_lencpy(&(*ret)[i], parse->cur->data, parse->cur->ret);
		i += parse->cur->ret;
		parse->cur = parse->cur->next;
		free(tmp->data);
		free(tmp);
		tmp = parse->cur;
	}
	return (1);
}

static int	str_build(t_parse *parse, char **ret)
{
	size_t	str_len;

	parse->cur = parse->head;
	str_len = 0;
	while (parse->cur)
	{
		str_len += parse->cur->ret;
		parse->cur = parse->cur->next;
	}
	parse->cur = parse->head;
	if (str_len != 0)
	{
		if (copy_to_res(parse, ret, &str_len) == -1)
			return (-1);
	}
	if (parse->num)
		free(parse->num);
	free(parse);
	return (str_len);
}

int	ft_vasprintf(char **ret, const char *format, va_list ap)
{
	int		i;
	int		return_value;
	char	*str;
	t_parse	*parse;

	str = (char *)format;
	parse = (t_parse *)malloc(sizeof(t_parse));
	if (!parse)
		return (-1);
	parse_init(parse);
	parse->head = NULL;
	parse->cur = NULL;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '%')
		{
			if (list_alloc(str, parse, i) == -1)
				return (clean_printf(parse));
			str += i;
			if (percent_parse(&str, parse, ap) == -1)
				return (clean_printf(parse));
			i = 0;
		}
		else
			i++;
	}
	if (list_alloc(str, parse, i) == -1)
		return (clean_printf(parse));
	return_value = str_build(parse, ret);
	if (return_value < 0)
		return (clean_printf(parse));
	return (return_value);
}
