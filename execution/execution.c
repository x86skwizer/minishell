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
	exit(my_global->exit_code);
}

void	execute_one_cmd(t_pars *cmd, char **env, int i)
{
			if (i == 0)
			{
				if (cmd->input)
				{
					dup2(cmd->fd_input, 0);
					close(cmd->fd_input);
				}
				if (my_global->nbr_cmd > 1)
				{
					close(my_global->fd_pip[0]);
					dup2(my_global->fd_pip[1], 1);
					close(my_global->fd_pip[1]);
				}
				if (my_global->nbr_cmd == 1)
				{
					if (cmd->fd_output)
					{
						dup2(cmd->fd_output, 1);
						close(cmd->fd_output);
					}
				}
			}
			else if (i == my_global->nbr_cmd - 1)
			{
				if (cmd->fd_output)
				{
					dup2(cmd->fd_output, 1);
					close(cmd->fd_output);
				}
				dup2(my_global->fd_tmp, 0);
				close(my_global->fd_tmp);
			}
			else if (i > 0 && i < my_global->nbr_cmd - 1)
			{
				close(my_global->fd_pip[0]);
				dup2(my_global->fd_pip[1], 1);
				dup2(my_global->fd_tmp, 0);
				close(my_global->fd_tmp);
				close(my_global->fd_pip[1]);
			}
			if (ft_strcmp("echo", cmd->cmd[0]) && ft_strcmp("cd", cmd->cmd[0])
					&& ft_strcmp("pwd", cmd->cmd[0]) && ft_strcmp("export", cmd->cmd[0]) 
					&& ft_strcmp("unset", cmd->cmd[0]) && ft_strcmp("env", cmd->cmd[0]) 
					&& ft_strcmp("exit", cmd->cmd[0]))
				execve(cmd->cmd[0], cmd->cmd, env);
			 else
				execute_builtins(cmd->cmd);
}

void	execute(t_list *list, char **env)
{
	t_list	*curr;
	t_pars	*cmd;
	int	i;

	i = 0;
	curr = list;
	my_global->fd_tmp = -1;
	my_global->pid = malloc(my_global->nbr_cmd * sizeof(pid_t));
	while (i < my_global->nbr_cmd)
	{
		cmd = (t_pars *)curr->content;
		if (my_global->nbr_cmd > 1)
		{
			if (i <= my_global->nbr_cmd - 1 && i > 0)
			{
				if (my_global->fd_tmp != -1)
					close(my_global->fd_tmp);
				my_global->fd_tmp = dup(my_global->fd_pip[0]);
				close(my_global->fd_pip[0]);
				close(my_global->fd_pip[1]);
			}
			if (i < my_global->nbr_cmd - 1)
				pipe(my_global->fd_pip);
		}
		my_global->pid[i] = fork();
		if (my_global->pid[i] == -1)
			handle_error(errno);
		else if (my_global->pid[i] == 0)
			execute_one_cmd(cmd, env, i);
		curr = curr->next;
		i++;
	}
	i = 0;
	while (i < my_global->nbr_cmd)
	{
		waitpid(my_global->pid[i], NULL, 0);
		i++;
	}
}