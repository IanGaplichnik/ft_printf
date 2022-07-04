/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_result.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igaplich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 13:59:24 by igaplich          #+#    #+#             */
/*   Updated: 2022/06/29 13:59:26 by igaplich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

//Copying LEN bytes from SRC to DST
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

//Copying content of linked list PARSE->DATA fields to RET string
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

/*Calculating length of resulting string, calling functions to
copy content to the resulting string RET*/
int	str_build(t_parse *parse, char **ret)
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
