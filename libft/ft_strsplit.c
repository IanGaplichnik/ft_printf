/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igaplich <igaplich@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 20:58:20 by igaplich          #+#    #+#             */
/*   Updated: 2022/03/08 18:30:48 by igaplich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(const char *s, char c)
{
	int	is_inside;
	int	sum;

	is_inside = 0;
	sum = 0;
	while (*s)
	{
		if (is_inside == 0 && *s != c)
		{
			is_inside = 1;
			sum++;
		}
		if (is_inside == 1 && *s == c)
			is_inside = 0;
		s++;
	}
	return (sum);
}

static void	*free_array(char **arr, int j)
{
	while (j)
		free(arr[j--]);
	free(arr);
	return (NULL);
}

static	char	**str_create(const char *s, char c, int len, char **str)
{
	int		i;
	int		j;
	int		start;

	i = 0;
	j = 0;
	start = 0;
	while (j < len)
	{
		while (s[i] && s[i] == c)
			i++;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		str[j] = ft_strsub(s, start, i - start);
		if (!str[j])
			return (free_array(str, j));
		j++;
	}
	str[j] = NULL;
	return (str);
}

char	**ft_strsplit(const char *s, char c)
{
	int		words;
	char	**str;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	str = (char **)malloc((words + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	return (str_create(s, c, words, str));
}
