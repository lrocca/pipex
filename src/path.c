/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrocca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 14:11:02 by lrocca            #+#    #+#             */
/*   Updated: 2021/06/16 14:21:15 by lrocca           ###   ########.fr       */
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
		return (NULL);
	return (env[i] + 5);
}

char	*find_exec(char *cmd, char **env)
{
	char	*path;
	char	**split;
	char	*ret;

	path = get_path(env);
	if (!path)
		ft_error("no PATH in env", NULL);
	cmd = ft_strjoin("/", cmd);
	split = ft_splitset(path, ":");
	ret = NULL;
	while (*split)
	{
		free(ret);
		ret = ft_strjoin(*split, cmd);
		if (!access(ret, X_OK))
			break ;
		split++;
	}
	if (!*split)
		ft_error(cmd + 1, "command not found");
	return (ret);
}
