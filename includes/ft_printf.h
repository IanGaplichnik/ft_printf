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

# define CONV "%cspfdiouxX"
# define FLAGS "#-0+ "
# include "../libft/libft.h"
# include <stdarg.h>
# include <stdbool.h>
# include <limits.h>

//DELETEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE
# include <stdio.h>
# define RED "\033[0;31m" 
# define REG "\033[0m"
//DELETEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE

typedef struct s_ret
{
	char	*data;
	unsigned int		ret;
	struct s_ret	*next;
}	t_ret;

typedef struct s_parse
{
	bool	hash;			//#
	bool	dash;			//-
	bool	zero;			//0
	bool	plus;			//+ 
	bool	space;			//' '
	bool	neg;
	int		width;			//num
	int		precision;		//.num
	int		length;			//hh, h, ll, l, L
	char	conv;			//%cspdiouxX
	char	*num;
	struct s_ret	*head;	//head of linked list
	struct s_ret	*cur;	//current node of linked list
}	t_parse;

int		ft_printf(const char *format, ...);
int 	ft_vasprintf(char **ret, const char *format, va_list ap);
void	parse_init(t_parse *parse);
int		list_alloc(char *str, t_parse *parse, int len);
int		percent_parse(char **str, t_parse *parse, va_list ap);
void	print_di(t_parse *parse);
void	print_ux(t_parse *parse);
void	print_o(t_parse *parse);
int		print_conversion(t_parse *parse, va_list ap);
void	print_wid(t_parse *parse, char *string, int len);
void	num_width_f(t_parse *parse, int *num_len, int *i, int *str_len);
void	precision_add_f(t_parse *parse, char **fraction, long *intpart);
int		precision_check(t_parse *parse, char *string);
int		print_c(t_parse *parse, va_list ap);
void	precision_add(t_parse *parse, int *num_len);
void	number_and_space(t_parse *parse, int *str_len, int *i);
int		print_perc(t_parse *parse);
void	print_p(t_parse *parse, va_list ap);
void	print_f(t_parse *parse, va_list ap);
void	print_nums(t_parse *parse, va_list ap);
void	width_parse(char **str, t_parse *parse, int *param, va_list ap);
void	precision_parse(char **str, t_parse *parse, int *param, va_list ap);
int		clean_printf(t_parse *parse);

#endif
