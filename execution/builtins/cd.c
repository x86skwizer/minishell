#include "../minishell.h"
#include "../../merge.h"

void builtin_cd(char **args)
{
	char	*old_path;
	char	*new_path;
	int		ret;

	old_path = getcwd(NULL, 0);
	old_path = ft_strjoin(getcwd(old_path, 100), "/");
	if (args[1] == NULL)
		new_path = ft_strdup("/");
	else
		new_path = ft_strjoin(old_path, args[1]);
	search_replace("OLDPWD", old_path);
	search_replace("PWD", new_path);
	ret = chdir(new_path);
	if (ret < 0)
	{
		ft_putstr_fd("cd: ", STDERR_FILENO);
		ft_putstr_fd(new_path, STDERR_FILENO);
		ft_putendl_fd(" no such file or directory", STDERR_FILENO);
		return ;
	}
	old_path = getcwd(NULL, 0);
	return ;
}
