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

static char	*ft_lencpy(char *dst, const char *src, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		dst[i] = src[i];
		i++;
	}
	return (dst);
}

static int	copy_to_res(t_parse *parse, char **ret, size_t *str_len)
{
	t_ret	*tmp;
	int		i;

	i = 0;
	*ret = ft_strnew(*str_len);
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
		copy_to_res(parse, ret, &str_len);
	free(parse);
	return (str_len);
}

int	ft_vasprintf(char **ret, const char *format, va_list ap)
{
	int		i;
	char	*str;
	t_parse	*parse;

	parse = (t_parse *)malloc(sizeof(t_parse));
	parse_init(parse);
	parse->head = NULL;
	str = (char *)format;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '%')
		{
			list_alloc(str, parse, i);
			str += i;
			percent_parse(&str, parse, ap);
			i = 0;
		}
		else
			i++;
	}
	list_alloc(str, parse, i);
	return (str_build(parse, ret));
}
