#include "minishell.h"

void	execution_entry()
{
	printf("execution entry\n");
	t_cmd		*cmd;
	t_minishell	*minishell;
	t_list		*cmd_list;
	t_list		*tmp;

	minishell = get_minishell_data(NULL);
	cmd_list = minishell->cmd;
	tmp = cmd_list;
	/*while(tmp)
	{
		cmd = tmp->content;
		// print args
		while (*cmd->args)
		{
			printf("arg: %s\n", *cmd->args);
			cmd->args++;
		}
		tmp = tmp->next;
	}
	printf("starting the execution\n");*/
	int		pid = fork();
	char	*path;
	tmp = minishell->cmd;
	cmd = tmp->content;
	if (pid == 0)
	{
		printf("child process\n");
		path = ft_strjoin("/bin/", *cmd->args);
		printf("path: %s\n", path);
		printf("cmd->args: %s\n", cmd->args[0]);
		execve(path, cmd->args, NULL);
		ft_lstdelone(cmd_list, free);
	}
	else
	{
		printf("parent process\n");
		wait(NULL);
	}
}
