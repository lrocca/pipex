/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrocca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 14:11:02 by lrocca            #+#    #+#             */
/*   Updated: 2021/06/19 03:02:57 by lrocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static char	*get_path(void)
{
	extern char	**environ;
	int	i;

	i = 0;
	while (ft_strncmp(environ[i], "PATH=", 5))
		i++;
	if (!environ[i])
		ft_error("no PATH in env", NULL);
	return (environ[i] + 5);
}

static char	*find_exec(char *cmd)
{
	char	**split;
	char	*path;
	char	*ret;
	int		i;

	path = get_path();
	cmd = ft_strjoin("/", cmd);
	split = ft_splitset(path, ":");
	ret = NULL;
	i = 0;
	while (split[i])
	{
		free(ret);
		ret = ft_strjoin(split[i], cmd);
		if (!access(ret, X_OK))
			break ;
		i++;
	}
	if (!split[i])
		ft_error(cmd + 1, "command not found");
	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
	return (ret);
}

void	ft_exec(char **av, int fd[2])
{
	char		*cmd;
	extern char	**environ;

	cmd = av[0];
	if (!ft_strchr(av[0], '/'))
		cmd = find_exec(cmd);
	execve(cmd, av, environ);
	close(fd[0]);
	close(fd[1]);
	ft_error("execve", strerror(errno));
}
