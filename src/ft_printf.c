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

//Initializing elements of the struct t_parse *parse
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

/*If string is present, allocate string of LEN bytes and copy STR in
the DATA element in the CURRENT node of the list,
else, allocate string of LEN bytes in the DATA element in the CURRENT node
and leave it as is*/
static int	list_fill(char *str, t_parse *parse, int len)
{
	parse->cur->data = ft_strnew(len + 1);
	if (!parse->cur->data)
		return (-1);
	if (str != NULL)
	{
		ft_strncpy(parse->cur->data, str, len);
		parse->cur->ret = ft_strlen(parse->cur->data);
	}
	return (1);
}

/*Creating a new node in the end of the list and calling
a function to allocate string inside created node*/
int	list_alloc(char *str, t_parse *parse, int len)
{
	t_ret	*new;

	if (len == 0)
		return (1);
	new = (t_ret *)malloc(sizeof(t_ret));
	if (!new)
		return (-1);
	new->data = NULL;
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
	if (list_fill(str, parse, len) == -1)
		return (-1);
	return (1);
}

//Implementation of printf C function
int	ft_printf(const char *format, ...)
{
	char	*ret_str;
	int		ret;
	va_list	ap;

	if (!format)
		return (-1);
	ret_str = NULL;
	va_start(ap, format);
	ret = ft_vasprintf(&ret_str, format, ap);
	va_end(ap);
	if (ret < 0)
	{
		if (ret_str)
			free(ret_str);
		return (-1);
	}
	if (ret > 0)
	{
		write(1, ret_str, (size_t)ret);
		free(ret_str);
	}
	return (ret);
}

//Implementation of asprintf C function
int	ft_asprintf(char **str, const char *format, ...)
{
	int		ret;
	va_list	ap;

	if (!format)
		return (-1);
	va_start(ap, format);
	ret = ft_vasprintf(str, format, ap);
	va_end(ap);
	if (ret < 0)
	{
		if (*str)
			free(*str);
		return (-1);
	}
	return (ret);
}
