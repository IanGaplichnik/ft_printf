/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igaplich <igaplich@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 19:23:12 by igaplich          #+#    #+#             */
/*   Updated: 2021/11/23 18:25:00 by igaplich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	char	*fresh;
	size_t	begin;
	size_t	end;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	begin = 0;
	end = ft_strlen(s) - 1;
	while (s[begin] == ' ' || s[begin] == '\n' || s[begin] == '\t')
		begin++;
	if (begin == end + 1)
		return (ft_strdup(""));
	while (s[end] == ' ' || s[end] == '\n' || s[end] == '\t')
		end--;
	fresh = ft_strnew(end - begin + 1);
	if (!fresh)
		return (NULL);
	while (begin <= end)
		fresh[i++] = s[begin++];
	i++;
	fresh[i] = '\0';
	return (fresh);
}
