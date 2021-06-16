/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrocca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 00:25:04 by lrocca            #+#    #+#             */
/*   Updated: 2021/06/16 17:37:54 by lrocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	ft_error(char *s1, char *s2)
{
	ft_putstr_fd(s1, STDERR_FILENO);
	if (s2)
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(s2, STDERR_FILENO);
	}
	ft_putchar_fd('\n', STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	ft_child(char **av, char **env, int fd[2])
{
	int	infile;

	infile = open(av[1], O_RDONLY);
	if (infile < 0)
		ft_error(av[1], strerror(errno));
	if (dup2(fd[1], STDOUT_FILENO) < 0 || dup2(infile, STDIN_FILENO) < 0)
		ft_error("dup2 failed", strerror(errno));
	close(fd[0]);
	ft_exec(ft_splitspace(av[2]), env);
}

void	ft_parent(char **av, char **env, int fd[2])
{
	int		outfile;

	outfile = open(av[4], O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if (outfile < 0)
		ft_error(av[4], strerror(errno));
	if (dup2(fd[0], STDIN_FILENO) < 0 || dup2(outfile, STDOUT_FILENO) < 0)
		ft_error("dup2 failed", strerror(errno));
	close(fd[1]);
	ft_exec(ft_splitspace(av[3]), env);
}

int	main(int ac, char **av, char **env)
{
	int		fd[2];
	pid_t	childpid;

	if (ac == 1)
		ft_error("usage", "./pipex file1 cmd1 cmd2 file2");
	if (ac != 5)
		ft_error("bad args", NULL);
	if (access(av[1], R_OK) < 0)
		ft_error(av[1], strerror(errno));
	if (pipe(fd) == -1)
		ft_error("pipe failed", strerror(errno));
	childpid = fork();
	if (childpid < 0)
		ft_error("fork failed", strerror(errno));
	if (childpid == 0)
		ft_child(av, env, fd);
	ft_parent(av, env, fd);
	return (0);
}
