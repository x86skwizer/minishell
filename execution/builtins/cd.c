#include "../minishell.h"

int builtin_cd(char **args)
{
	char	*old_path;
	char	*new_path;
	// t_env	*env;
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
	printf("%s\n",new_path);
	if (ret < 0)
	{
		ft_putstr_fd("cd: ", STDERR_FILENO);
		ft_putstr_fd(new_path, STDERR_FILENO);
		ft_putendl_fd(" no such file or directory", STDERR_FILENO);
		return (1);
	}
	old_path = getcwd(NULL, 0);
	return (ret);
}

int main(int argc, char **argv, char **envp)
{
    // char s[100];

	(void)argc;
	(void)envp;

	// for (int i = 0; envp[i]; i++)
	// {
	// 	printf("%s\n",envp[i]);
	// }
    //Printing the current working directory
    // printf("%d\n",builtin_cd(argv));
	builtin_cd(argv);
    //Changing the current working directory to the previous directory
    // chdir("..");
    //Printing the now current working directory
	// builtin_cd(argv);
    // printf("%d\n",builtin_cd(argv));
    return 0;
}