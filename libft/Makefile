# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: igaplich <igaplich@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/02 15:19:12 by igaplich          #+#    #+#              #
#    Updated: 2022/04/21 18:39:48 by igaplich         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
FLAGS = -c -I ${INC_DIR} #-Wall -Werror -Wextra 

NAME = libft.a

SRC2 = $(SRC:.c=.o)
INC_DIR = $(CURDIR)
SRC = ft_strlen.c \
	ft_strcpy.c \
	ft_putchar.c \
	ft_strdup.c \
	ft_putnbr.c \
	ft_putstr.c \
	ft_atoi.c \
	ft_isalpha.c \
	ft_isalnum.c \
	ft_isdigit.c \
	ft_isascii.c \
	ft_isprint.c \
	ft_strncpy.c \
	ft_toupper.c \
	ft_tolower.c \
	ft_strchr.c \
	ft_strcmp.c \
	ft_strstr.c \
	ft_strncmp.c \
	ft_strnstr.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_memset.c \
	ft_bzero.c \
	ft_memccpy.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_strcat.c \
	ft_strncat.c \
	ft_strlcat.c \
	ft_strrchr.c \
	ft_strdel.c \
	ft_strclr.c \
	ft_strnew.c \
	ft_memalloc.c \
	ft_memdel.c \
	ft_putendl.c \
	ft_strequ.c \
	ft_strnequ.c \
	ft_strsub.c \
	ft_strjoin.c \
	ft_strtrim.c \
	ft_strsplit.c \
	ft_putchar_fd.c \
	ft_putstr_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c \
	ft_striter.c \
	ft_striteri.c \
	ft_strmap.c \
	ft_strmapi.c \
	ft_itoa.c \
	ft_lstnew.c \
	ft_lstadd.c \
	ft_lstiter.c \
	ft_lstdelone.c \
	ft_lstdel.c \
	ft_lstmap.c \
	ft_print_double.c \
	ft_isspace.c \
	ft_lstadd_end.c \
	ft_lstlen.c \
	ft_lstmerge.c \
	ft_atoi_base.c \
	get_next_line.c \
	ft_itoa_base.c

all: $(NAME)

$(NAME):
	@echo "compiling libft"
	@$(CC) $(FLAGS) $(SRC)
	@ar rcs $(NAME) $(SRC2)

clean:
	@echo "Deleting libft object files"
	@/bin/rm -f $(SRC2)

fclean: clean
	@echo "Deleting libft object files and library files"
	@/bin/rm -f $(NAME)

re: fclean all
	@echo "Recompiling libft"
