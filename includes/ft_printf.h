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
	va_list	ap;
	bool	hash;			//#
	bool	dash;			//-
	bool	zero;			//0
	bool	plus;			//+ 
	bool	space;			//' '
	int		width;			//num
	int		precision;		//.num
	int		length;			//hh, h, ll, l, L
	char	conv;			//%cspdiouxX
	int		neg;
	char	*num;
	struct s_ret	*head;	//head of linked list
	struct s_ret	*cur;	//current node of linked list
}	t_parse;

int		ft_printf(const char *format, ...);
int		print_conversion(t_parse *parse);
int		percent_parse(char **str, t_parse *parse);
void	print_struct(t_parse *parse, char *state);
void	list_alloc(char *str, t_parse *parse, int i);
t_parse	*parse_init(t_parse *parse);
void	print_nums(t_parse *parse);
int		precision_check(t_parse *parse, char *string);
void	print_di(t_parse *parse);
void	print_ux(t_parse *parse);
void	print_o(t_parse *parse);
void	print_f(t_parse *parse);
void	precision_add(t_parse *parse, int *num_len);
void	lengths_prepare(int *num_len, int *str_len, t_parse *parse);
void	num_width(t_parse *parse, int *num_len, int *i, int *str_len);
void	num_no_width(t_parse *parse, int *i);
void	precision_add_f(t_parse *parse, char **fraction, long *intpart);
void	num_width_f(t_parse *parse, int *num_len, int *i, int *str_len);
void	lengths_prepare_f(t_parse *parse, long *intpart, int *num_len, int *str_len);
void	number_and_space(t_parse *parse, int *str_len, int *i);
void	print_wid(t_parse *parse, char *string, int len);
int		print_c(t_parse *parse);
int		print_perc(t_parse *parse);
void	print_p(t_parse *parse);
void	widprec_parse(char **str, t_parse *parse, int *param);

#endif
