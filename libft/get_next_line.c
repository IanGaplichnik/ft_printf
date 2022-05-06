/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igaplich <igaplich@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 16:48:49 by igaplich          #+#    #+#             */
/*   Updated: 2022/03/08 13:52:19 by igaplich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	join_and_free(char **line, char **from)
{
	char	*tmp;

	tmp = *line;
	*line = ft_strjoin(*line, *from);
	ft_strdel(&tmp);
	if (!*line)
		return (0);
	return (1);
}

static int	leftover_check(char **line, char **leftover, int *bytes_read)
{
	char	*newline;

	newline = NULL;
	if (*leftover)
	{
		newline = ft_strchr(*leftover, '\n');
		if (newline)
		{
			*newline = '\0';
			if (!join_and_free(line, leftover))
				return (-1);
			ft_strcpy(*leftover, ++newline);
			*bytes_read = 0;
		}
		else
		{
			*bytes_read = 1;
			if (!join_and_free(line, leftover))
				return (-1);
			ft_strdel(leftover);
		}
	}
	return (1);
}

static int	get_line(const int fd, char **line, int bytes_read, char **tmp)
{
	char		buff[BUFF_SIZE + 1];
	static char	*leftover[MAX_FD];

	leftover_check(line, &leftover[fd], &bytes_read);
	while (bytes_read > 0 && !leftover[fd])
	{
		ft_bzero(buff, BUFF_SIZE + 1);
		bytes_read = read(fd, buff, BUFF_SIZE);
		if (bytes_read < 0)
			return (-1);
		if (ft_strchr(buff, '\n'))
		{
			leftover[fd] = ft_strdup(buff);
			return (leftover_check(line, &leftover[fd], &bytes_read));
		}
		*tmp = *line;
		*line = ft_strjoin(*line, buff);
		if (!*line)
			return (-1);
		ft_strdel(tmp);
	}
	if (ft_strlen(*line) || leftover[fd] || bytes_read)
		return (1);
	ft_strdel(line);
	return (0);
}

int	get_next_line(const int fd, char **line)
{
	int		bytes_read;
	char	*tmp;

	if (fd < 0 || !line || fd >= MAX_FD)
		return (-1);
	bytes_read = 1;
	*line = ft_strnew(0);
	return (get_line(fd, line, bytes_read, &tmp));
}
