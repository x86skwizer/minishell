#include "minishell.h"

t_minishell*	get_minishell_data(t_minishell *minishell)
{
	static t_minishell	*minishell_data = NULL;

	if (minishell)
		minishell_data = minishell;
	return (minishell_data);
}

// int	main(int argc, char **argv, char **env)
// {
// 	t_minishell	minishell;

// 	(void)argc;
// 	(void)argv;
// 	(void)env;
// 	minishell.list_env = NULL;
// 	minishell.cmd = NULL;
// 	minishell.exit_code = 0;
// 	get_minishell_data(&minishell);
// 	// call the env load function
// 	while (1)
// 	{
// 		printf("===================the exit code of the previous execution [%d]=================================\n", minishell.exit_code);
// 		printf("HELLO this is assistant for devloping minishell: \n");
// 		printf("choose the command you want to test: \n");
// 		printf("a. ls -la\n");
// 		printf("b. echo hello world\n");
// 		printf("c. ls -l | cat -e > file.txt\n");
// 		printf("d. ls -l | cat -e > file.txt | cat -e > file2.txt\n");
// 		printf("e. ls -l | cat -e > file.txt | cat -e > file2.txt | cat -e > file3.txt\n");
// 		printf("f. ls / > file.txt | cat < file.txt | wc -c \n");
// 		printf("g. ls / > file.txt | cat < file.txt | wc -c | cat -e > file2.txt\n");
// 		printf("choose the letter of the command you want to test: \n");
// 		char c[100];
// 		scanf("%s", c);
// 		parsing_entry(c);
// 		execution_entry();
// 		memory_manager();
// 	}
// 	return (0);
// }