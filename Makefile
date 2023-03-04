# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yamrire <yamrire@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/20 20:11:20 by yamrire           #+#    #+#              #
#    Updated: 2023/03/04 07:15:11 by yamrire          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = main.c ./parsing/parsing.c ./parsing//utils/ft_split.c ./parsing/utils/ft_strlen.c ./parsing/utils/ft_strnstr.c \
	./parsing/utils/ft_substr.c ./parsing/utils/ft_strjoin.c ./parsing/utils/ft_strdup.c ./parsing/utils/ft_strchr.c ./parsing/utils.c \
	./parsing/utils/ft_strcmp.c ./parsing/utils/ft_putchar_fd.c ./parsing/utils/ft_putstr_fd.c ./parsing/utils/ft_lstaddback_cmd.c \
	./parsing/utils/ft_lstlast_cmd.c ./parsing/utils/ft_lstnew_cmd.c
NAME = minishell
CC = cc
FLAGS =  -lreadline #-Wall -Werror -Wextra -fsanitize=address -g3
OBJ = $(SRC:%.c=%.o)

all : $(NAME) $(OBJ)

$(NAME) :
	$(CC) $(FLAGS) $(SRC) -o $(NAME)

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)
	
re : fclean all
