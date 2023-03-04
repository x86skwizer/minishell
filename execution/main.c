#include "minishell.h"
#include "../merge.h"

int main(int argc, char **argv, char **env)
{
	int		i;
	char	*path;
	char	*paths;
	char	**paths_;
	char	*s;
	char	*str[2];

	(void)argc;
	(void)argv;
	i = 0;
	while (env[i])
	{
		s = ft_split(env[i], '=')[0];
		if (ft_strncmp(s, "PATH", ft_strlen(s)) == 0)
		{
			paths = ft_strdup(ft_split(env[i], '=')[1]);
			break;
		}
		i++;
	}
	i = 0;
	paths_ = ft_split(paths, ':');
	str[0] = argv[1];
	if (argv[2])
		str[1] = argv[2];
	while (paths_[i])
	{
		path = ft_strjoin(paths_[i], "/");
		path = ft_strjoin(path, argv[1]);
		// printf("%s\n", path);
		if (open(path, O_RDONLY) != -1)
		{
			execve(path, str, NULL);
			break ;
		}
		i++;
	}
}