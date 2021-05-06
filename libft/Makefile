# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tisabel <tisabel@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/11 16:53:48 by mazor             #+#    #+#              #
#    Updated: 2021/03/16 21:52:06 by mazor            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
FLAGS = -Wall -Wextra -Werror
HEADER = libft.h

SRCS = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
	ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memccpy.c \
	ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c \
	ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c \
	ft_split.c ft_strchr.c ft_strdup.c ft_strjoin.c ft_strlcat.c \
	ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c \
	ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c \
	ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
	ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c \
	ft_lstmap.c ft_strjoin_char.c ft_strstr_bonus.c \
	ft_strfind_bonus.c ft_strcmp_bonus.c ft_min_bonus.c ft_max_bonus.c \
	ft_strcut_bonus.c

OBJ = ${SRCS:.c=.o}

all: $(NAME)

%.o: %.c $(HEADER)
	gcc $(FLAGS) -c -o $@ $<

$(NAME): $(OBJ)
	@echo "compile libft..."
	@ar -rcs $@ $?

clean:
	@echo "clean libft object files..."
	@/bin/rm -f $(OBJ)

fclean: clean
	@echo "remove libft..."
	@/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
