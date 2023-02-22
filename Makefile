# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yamrire <yamrire@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/20 20:11:20 by yamrire           #+#    #+#              #
#    Updated: 2023/02/22 02:27:06 by yamrire          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = main.c parsing.c ft_split.c ft_strlen.c ft_strnstr.c ft_substr.c ft_strjoin.c ft_strdup.c ft_strchr.c utils.c
NAME = minishell
CC = cc
FLAGS = -Wall -Werror -Wextra -lreadline
OBJ = $(SRC:%.c=%.o)

all : $(NAME) $(OBJ)

$(NAME) :
	$(CC) $(FLAGS) $(SRC) -o $(NAME)

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)
	
re : fclean all