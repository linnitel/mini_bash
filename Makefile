# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tisabel <tisabel@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/03 21:04:29 by mazor             #+#    #+#              #
#    Updated: 2021/03/16 21:58:55 by mazor            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc -O2
FLAGS = -Wall -Wextra -Werror -Iincludes/
LIBFT = ./libft/libft.a

SRCS = srcs/main.c \
		srcs/signals/signals.c\
		srcs/signals/signals_utils.c\
		srcs/redirect/redirect.c\
		srcs/redirect/redir_utils.c\
		srcs/pipe/fd_utils.c\
		srcs/pipe/init_pipe.c\
		srcs/pipe/pipe_utils.c\
		srcs/parser/utils.c \
		srcs/parser/parser_variables.c \
		srcs/parser/parser_string.c \
		srcs/parser/parser_shielding.c \
		srcs/parser/parser_quotes.c \
		srcs/parser/parser_path.c \
		srcs/parser/parser_errors.c \
		srcs/parser/syntax_errors.c \
		srcs/parser/syntax_errors_utils.c \
		srcs/parser/convert.c \
		srcs/no_pipe_cmd/run_cmd.c \
		srcs/no_pipe_cmd/start_command.c \
		srcs/no_pipe_cmd/start_execve_pipe.c\
		srcs/init/init.c \
		srcs/general/variables.c \
		srcs/general/get_next_line.c\
		srcs/env/env_utils_2.c \
		srcs/env/env_utils.c \
		srcs/env/conv_env.c \
		srcs/env/env_free.c\
		srcs/cmd_utils/cmd_last.c \
		srcs/cmd_utils/add_back_cmd.c \
		srcs/cmd/ft_unset.c \
		srcs/cmd/ft_pwd.c \
		srcs/cmd/ft_export.c \
		srcs/cmd/ft_export_utils.c \
		srcs/cmd/ft_exit.c \
		srcs/cmd/ft_env.c \
		srcs/cmd/ft_echo.c \
		srcs/cmd/ft_cd.c \
		srcs/clear/clear.c \
		srcs/clear/error.c \

OBJ = $(SRCS:.c=.o)

HEADER = includes/minishell.h libft/libft.h includes/struct.h

%.o: %.c $(HEADER)
	$(CC) $(FLAGS) -c -o $@ $<

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	@echo "compile minishell..."
	@$(CC) $(FLAGS) -o $(NAME) $(OBJ) -L./libft -lft

$(LIBFT): NONE
	@make -C ./libft

bonus: all

clean:
	@echo "clean minishell object files..."
	@rm -f $(OBJ)
	@make -C libft clean

fclean: clean
	@echo "remove minishell"
	@echo "remove libft.a"
	@rm -f $(NAME) $(LIBFT)

re: fclean all

norminette:
	@norminette $(SRCS) $(HEADER) libft/*.c

.PHONY: all clean fclean bonus re norminette NONE