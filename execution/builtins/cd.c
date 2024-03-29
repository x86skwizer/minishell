/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <yamrire@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 16:07:08 by yamrire           #+#    #+#             */
/*   Updated: 2023/03/27 01:38:43 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../merge.h"

int	cd_print(char *new_path, char *old_path)
{
	ft_putstr_fd("cd: ", STDERR_FILENO);
	ft_putstr_fd(new_path, STDERR_FILENO);
	ft_putendl_fd(" no such file or directory", STDERR_FILENO);
	free(new_path);
	free(old_path);
	return (0);
}

int	builtin_cd(char **args)
{
	char	*old_path;
	char	*new_path;
	char	*tmp;
	int		ret;

	old_path = getcwd(NULL, 0);
	tmp = ft_strjoin(getcwd(old_path, 100), "/");
	free(old_path);
	old_path = tmp;
	if (args[1] == NULL)
		new_path = ft_strdup("/");
	else
		new_path = ft_strjoin(old_path, args[1]);
	search_replace("OLDPWD", old_path);
	search_replace("PWD", new_path);
	ret = chdir(new_path);
	if (ret < 0)
		return (cd_print(new_path, old_path));
	free(old_path);
	free(new_path);
	return (ret);
}
