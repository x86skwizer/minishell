# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yamrire <yamrire@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/20 20:11:20 by yamrire           #+#    #+#              #
#    Updated: 2023/03/23 21:20:01 by yamrire          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = main.c ./parsing/parsing.c ./parsing//utils/ft_split.c ./parsing/utils/ft_strlen.c ./parsing/utils/ft_strnstr.c ./execution/utils.c ./execution/end_prog.c \
	./parsing/utils/ft_substr.c ./parsing/utils/ft_strjoin.c ./parsing/utils/ft_strdup.c ./parsing/utils/ft_strchr.c ./parsing/utils.c \
	./parsing/utils/ft_strcmp.c ./parsing/utils/ft_lstadd_back.c ./parsing/utils/ft_lstlast.c ./parsing/utils/ft_lstnew.c ./execution/utils/env_fill.c \
	./execution/builtins/cd.c ./execution/builtins/echo.c ./execution/builtins/pwd.c ./execution/utils/libft_str.c ./execution/utils/search.c \
	./parsing/check_path.c ./execution/builtins/env.c ./parsing/expansion.c ./execution/execution.c ./parsing/utils/ft_itoa.c ./execution/builtins/export.c \
	./execution/builtins/unset.c ./execution/builtins/exit.c ./execution/utils/get_next_line.c ./execution/utils/heredoc.c execution/utils/linked_list.c execution/signals.c
NAME = minishell
CC = cc
FLAGS = -Wall -Werror -Wextra
CFLAGS = $(shell pkg-config --cflags readline)
LDFLAGS = $(shell pkg-config --libs readline) 
#LDFLAGS = -lreadline -L /Users/yamrire/goinfre/homebrew/opt/readline/lib -I /Users/yamrire/goinfre/homebrew/opt/readline/include #-fsanitize=address -g3
OBJ = $(SRC:%.c=%.o)

all : $(NAME) 

#$(NAME) :
#	$(CC) $(LDFLAGS) $(FLAGS) $(SRC) -o $(NAME)
$(NAME) : $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^
%.o: %.c
	$(CC) $(FLAGS) $(CFLAGS) -c $< -o $@

clean :
	rm -f $(OBJ)


fclean : clean
	rm -f $(NAME)
	
re : fclean all
