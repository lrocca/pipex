/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrocca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 00:25:04 by lrocca            #+#    #+#             */
/*   Updated: 2021/06/16 14:33:08 by lrocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	ft_error(char *s1, char *s2)
{
	ft_putstr_fd("pipex: ", STDERR_FILENO);
	ft_putstr_fd(s1, STDERR_FILENO);
	if (s2)
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putendl_fd(s2, STDERR_FILENO);
	}
	exit(EXIT_FAILURE);
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

void	ft_init(int ac, char **av, int fd[2], pid_t *childpid)
{
	if (ac != 5)
		ft_error("bad arguments", NULL);
	if (access(av[1], R_OK) < 0)
		ft_error(av[1], strerror(errno));
	if (pipe(fd) == -1)
		ft_error("pipe failed", strerror(errno));
	*childpid = fork();
	if (*childpid < 0)
		ft_error("fork failed", strerror(errno));
}

int	main(int ac, char **av, char **env)
{
	int		fd[2];
	pid_t	childpid;
	int		std;

	ft_init(ac, av, fd, &childpid);
	if (childpid == 0)
	{
		std = open(av[1], O_RDONLY);
		if (std < 0)
			ft_error(av[1], strerror(errno));
		if (dup2(fd[1], STDOUT_FILENO) < 0 || dup2(std, STDIN_FILENO) < 0)
			ft_error("dup2 failed", strerror(errno));
		close(fd[0]);
		ft_exec(ft_splitspace(av[2]), env);
	}
	std = open(av[4], O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if (std < 0)
		ft_error(av[4], strerror(errno));
	if (dup2(fd[0], STDIN_FILENO) < 0 || dup2(std, STDOUT_FILENO) < 0)
		ft_error("dup2 failed", strerror(errno));
	close(fd[1]);
	ft_exec(ft_splitspace(av[3]), env);
	return (0);
}
