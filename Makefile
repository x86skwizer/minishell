# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yamrire <yamrire@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/20 20:11:20 by yamrire           #+#    #+#              #
#    Updated: 2023/03/01 01:19:12 by yamrire          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = main.c ./parsing/parsing.c ./utils/ft_split.c ./utils/ft_strlen.c ./utils/ft_strnstr.c ./utils/ft_substr.c ./utils/ft_strjoin.c ./utils/ft_strdup.c ./utils/ft_strchr.c ./parsing/utils.c ./utils/ft_strcmp.c
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
