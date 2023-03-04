SRC = entry.c parsing_entry.c  execution.c utils/memory_manager.c \
		utils/linked_list.c utils/libft_str.c \
		main.c
EXEC = minishell
INC = -I./inc
all: $(EXEC)

$(EXEC): $(SRC)
		gcc -Wall -Wextra -Werror -o $(EXEC) $(SRC) $(INC)

clean:
	rm -f $(EXEC)

fclean: clean

re: fclean all