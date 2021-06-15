/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrocca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 00:25:04 by lrocca            #+#    #+#             */
/*   Updated: 2021/06/15 19:22:37 by lrocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	ft_error(char *s)
{
	// ft_putendl_fd(s, STDERR_FILENO);
	if (!errno)
		errno = 1;
	perror(s);
	exit(EXIT_FAILURE);
}

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
		ft_error("no PATH in env");
	cmd = ft_strjoin("/", cmd);
	split = ft_splitset(path, ":");
	while (*split)
	{
		ret = ft_strjoin(*split, cmd);
		if (!access(ret, X_OK))
			break ;
		split++;
	}
	if (!*split)
	{
		errno = 127;
		ft_error(cmd + 1);
	}
	return (ret);
}

void	ft_exec(char **av, char **env)
{
	char	*cmd;

	cmd = av[0];
	if (!ft_strchr(av[0], '/'))
		cmd = find_exec(cmd, env);
	execve(cmd, ++av, env);
	ft_error(cmd);
}

void	ft_check(int ac, char **av)
{
	if (ac != 5)
		ft_error("bad arguments");
	if (access(av[1], R_OK) < 0)
		ft_error(av[1]);
}

int	main(int ac, char **av, char **env)
{
	int		fd[2];
	pid_t	childpid;
	int		std;

	ft_check(ac, av);
	if (pipe(fd) == -1)
		ft_error("pipe failed");
	childpid = fork();
	if (childpid < 0)
		ft_error("fork failed");
	if (childpid == 0)
	{
		std = open(av[1], O_RDONLY);
		if (std < 0)
			ft_error(av[1]);
		if (dup2(fd[1], STDOUT_FILENO) < 0 || dup2(std, STDIN_FILENO) < 0)
			ft_error("dup2 failed");
		close(fd[0]);
		ft_exec(ft_splitspace(av[2]), env);
	}
	else
	{
		std = open(av[4], O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
		if (std < 0)
			ft_error(av[4]);
		if (dup2(fd[0], STDIN_FILENO) < 0 || dup2(std, STDOUT_FILENO) < 0)
			ft_error("dup2 failed");
		close(fd[1]);
		ft_exec(ft_splitspace(av[3]), env);
	}
	return (0);
}
