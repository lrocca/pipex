/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrocca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 14:11:02 by lrocca            #+#    #+#             */
/*   Updated: 2021/06/16 17:35:47 by lrocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

char	*get_path(char **env)
{
	int	i;

	i = 0;
	while (ft_strncmp(env[i], "PATH=", 5))
		i++;
	if (!env[i])
		ft_error("no PATH in env", NULL);
	return (env[i] + 5);
}

char	*find_exec(char *cmd, char **env)
{
	char	**split;
	char	*path;
	char	*ret;
	int		i;

	path = get_path(env);
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

void	ft_exec(char **av, char **env)
{
	char	*cmd;

	cmd = av[0];
	if (!ft_strchr(av[0], '/'))
		cmd = find_exec(cmd, env);
	execve(cmd, av, env);
	ft_error("execve", strerror(errno));
}
