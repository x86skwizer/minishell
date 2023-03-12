#include "../merge.h"

void	execute_builtins(char **cmd)
{
	if (!ft_strcmp("echo", cmd[0]))
		builtin_echo(cmd);
	else if (!ft_strcmp("cd", cmd[0]))
		builtin_cd(cmd);
	else if (!ft_strcmp("pwd", cmd[0]))
		builtin_pwd();
	else if (!ft_strcmp("env", cmd[0]))
		builtin_env();
	else
		printf("Found undone builtin function !\n");
}

void	execute_one_cmd(t_pars *cmd, char *str, char **env, int i)
{
	
	if (ft_strcmp("echo", cmd->cmd[0]) && ft_strcmp("cd", cmd->cmd[0])
			&& ft_strcmp("pwd", cmd->cmd[0]) && ft_strcmp("export", cmd->cmd[0]) 
			&& ft_strcmp("unset", cmd->cmd[0]) && ft_strcmp("env", cmd->cmd[0]) 
			&& ft_strcmp("exit", cmd->cmd[0]))
	{
		cmd->pid[i] = fork();
		if (cmd->pid[i] == -1)
			handle_error(errno);
		else if (cmd->pid[i] == 0)
		{
			if (execve(cmd->cmd[0], cmd->cmd, env) == -1)
				handle_error(errno);
		}
		wait(NULL);
		free_double(cmd->cmd);
		free(str);
	}
	else
		execute_builtins(cmd->cmd);
	i++;
}

void	execute(t_list *list, char *str, char **env, int nbr_cmd)
{
	t_list	*curr;
	t_pars	*cmd;
	int	i;

	i = 0;
	curr = list;
	cmd = (t_pars *)curr->content;
	cmd->pid = malloc(nbr_cmd * sizeof(pid_t));
	if (nbr_cmd > 1)
	{
		if (pipe(cmd->fd_pip))
			handle_error(errno);
	}
	if (nbr_cmd == 1)
		execute_one_cmd(cmd, str, env, i);
}