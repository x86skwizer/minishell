#include "minishell.h"

void	parsing_entry(char *line)
{
	t_minishell	*minishell;
	t_list		**cmd;
	t_cmd		*_cmd;
	t_file		*file;
	char		**args;

	_cmd = malloc(sizeof(t_cmd));
	minishell = get_minishell_data(NULL);
	cmd = &(minishell->cmd);
	printf("parsing entry case: %s\n", line);
	if (line[0] == 'a')
	{
		args = ft_split("ls -la", ' ');
		_cmd->args = args;
		ft_lstadd_back(cmd, ft_lstnew(_cmd));
	}
	else if (line[0] == 'b')
	{
		args = ft_split("echo hello world", ' ');
		_cmd->args = args;
		ft_lstadd_back(cmd, ft_lstnew(_cmd));
	}
	else if (line[0] == 'c')
	{
		args = ft_split("ls -l", ' ');
		_cmd->args = args;
		ft_lstadd_back(cmd, ft_lstnew(_cmd));
		_cmd = malloc(sizeof(t_cmd));
		args = ft_split("cat -e", ' ');
		_cmd->args = args;
		file = malloc(sizeof(t_file));
		file->path = "file.txt";
		file->type = OUTPUT;
		_cmd->file = file;
		ft_lstadd_back(cmd, ft_lstnew(_cmd));
	}
	else if (line[0] == 'd')
	{
		args = ft_split("ls -l", ' ');
		_cmd->args = args;
		ft_lstadd_back(cmd, ft_lstnew(_cmd));
		_cmd = malloc(sizeof(t_cmd));
		args = ft_split("cat -e", ' ');
		_cmd->args = args;
		file = malloc(sizeof(t_file));
		file->path = "file.txt";
		file->type = OUTPUT;
		_cmd->file = file;
		ft_lstadd_back(cmd, ft_lstnew(_cmd));
		_cmd = malloc(sizeof(t_cmd));
		args = ft_split("cat -e", ' ');
		_cmd->args = args;
		file = malloc(sizeof(t_file));
		file->path = "file2.txt";
		file->type = OUTPUT;
		_cmd->file = file;
		ft_lstadd_back(cmd, ft_lstnew(_cmd));
	}
	else if (line[0] == 'e')
	{
		args = ft_split("ls -l", ' ');
		_cmd->args = args;
		ft_lstadd_back(cmd, ft_lstnew(_cmd));
		_cmd = malloc(sizeof(t_cmd));
		args = ft_split("cat -e", ' ');
		_cmd->args = args;
		file = malloc(sizeof(t_file));
		file->path = "file.txt";
		file->type = OUTPUT;
		_cmd->file = file;
		ft_lstadd_back(cmd, ft_lstnew(_cmd));
		_cmd = malloc(sizeof(t_cmd));
		args = ft_split("cat -", ' ');
		_cmd->args = args;
		file = malloc(sizeof(t_file));
		file->path = "file2.txt";
		file->type = OUTPUT;
		_cmd->file = file;
		ft_lstadd_back(cmd, ft_lstnew(_cmd));
		_cmd = malloc(sizeof(t_cmd));
		args = ft_split("cat -e", ' ');
		_cmd->args = args;
		file = malloc(sizeof(t_file));
		file->path = "file3.txt";
		file->type = OUTPUT;
		_cmd->file = file;
		ft_lstadd_back(cmd, ft_lstnew(_cmd));
	}
	else if (line[0] == 'f')
	{
		args = ft_split("ls /", ' ');
		_cmd->args = args;
		file = malloc(sizeof(t_file));
		file->path = "file.txt";
		file->type = OUTPUT;
		_cmd->file = file;
		ft_lstadd_back(cmd, ft_lstnew(_cmd));
		_cmd = malloc(sizeof(t_cmd));
		args = ft_split("cat", ' ');
		_cmd->args = args;
		file = malloc(sizeof(t_file));
		file->path = "file.txt";
		file->type = INPUT;
		_cmd->file = file;
		ft_lstadd_back(cmd, ft_lstnew(_cmd));
		_cmd = malloc(sizeof(t_cmd));
		args = ft_split("wc -c", ' ');
		_cmd->args = args;
		ft_lstadd_back(cmd, ft_lstnew(_cmd));
	}
	else if (line[0] == 'g')
	{
		args = ft_split("ls /", ' ');
		_cmd->args = args;
		file = malloc(sizeof(t_file));
		file->path = "file.txt";
		file->type = OUTPUT;
		_cmd->file = file;
		ft_lstadd_back(cmd, ft_lstnew(_cmd));
		_cmd = malloc(sizeof(t_cmd));
		args = ft_split("cat", ' ');
		_cmd->args = args;
		file = malloc(sizeof(t_file));
		file->path = "file.txt";
		file->type = INPUT;
		_cmd->file = file;
		ft_lstadd_back(cmd, ft_lstnew(_cmd));
		_cmd = malloc(sizeof(t_cmd));
		args = ft_split("wc -c", ' ');
		_cmd->args = args;
		ft_lstadd_back(cmd, ft_lstnew(_cmd));
		_cmd = malloc(sizeof(t_cmd));
		args = ft_split("cat -e", ' ');
		_cmd->args = args;
		file = malloc(sizeof(t_file));
		file->path = "file2.txt";
		file->type = OUTPUT;
		_cmd->file = file;
		ft_lstadd_back(cmd, ft_lstnew(_cmd));
	}
}
