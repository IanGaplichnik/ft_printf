/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igaplich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 18:41:22 by igaplich          #+#    #+#             */
/*   Updated: 2022/04/25 19:30:38 by igaplich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# define CONV "%bncspfdiouxX"
# define FLAGS "#-0+ "
# include "../libft/libft.h"
# include <stdarg.h>
# include <stdbool.h>

/*linked list inside of t_parse struct
*data is a string of ret length*/
typedef struct s_ret
{
	char			*data;
	unsigned int	ret;
	struct s_ret	*next;
}	t_ret;

/*t_parse is a structure, containing parsed flags, width, precision,
length modifier, conversion specifier and a linked list, containing parts
of the return string. Additionally, for numeric values num string holds
an absolute value of a number converted to a string, and neg marks
if that number is negative*/
typedef struct s_parse
{
	bool			hash;
	bool			dash;
	bool			zero;
	bool			plus;
	bool			space;
	bool			neg;
	int				width;
	int				precision;
	int				length;
	char			conv;
	char			*num;
	struct s_ret	*head;
	struct s_ret	*cur;
}	t_parse;

int		ft_printf(const char *format, ...);
int		ft_vasprintf(char **ret, const char *format, va_list ap);
int		ft_asprintf(char **str, const char *format, ...);
void	parse_init(t_parse *parse);
int		list_alloc(char *str, t_parse *parse, int len);
int		percent_parse(char **str, t_parse *parse, va_list ap);
int		print_di(t_parse *parse, int base);
int		print_ux(t_parse *parse);
int		print_o(t_parse *parse);
int		print_conversion(t_parse *parse, va_list ap);
int		print_wid(t_parse *parse, char *string, int len);
void	num_width_f(t_parse *parse, int *num_len, int *i, int *str_len);
int		precision_add_f(t_parse *parse, char **fraction, long *intpart);
int		precision_check(t_parse *parse, char *string);
int		print_c(t_parse *parse, va_list ap);
int		precision_add(t_parse *parse, int *num_len);
void	number_and_space(t_parse *parse, int *str_len, int *i);
int		print_perc(t_parse *parse);
int		print_p(t_parse *parse, va_list ap);
int		print_f(t_parse *parse, va_list ap);
int		print_nums(t_parse *parse, va_list ap);
int		width_parse(char **str, t_parse *parse, int *param, va_list ap);
int		precision_parse(char **str, t_parse *parse, int *param, va_list ap);
int		clean_printf(t_parse *parse);
int		print_fn(t_parse *parse, long *intpart, char **fraction);
int		str_build(t_parse *parse, char **ret);

#endif
