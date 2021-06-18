/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrocca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 18:46:50 by lrocca            #+#    #+#             */
/*   Updated: 2021/06/18 20:23:03 by lrocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus.h"

void	ft_child(char *cmd, int fd[2])
{
	if (dup2(fd[0], STDIN_FILENO) < 0 || dup2(fd[1], STDOUT_FILENO) < 0)
		ft_error("dup2 failed", ft_itoa(fd[0]));
	ft_exec(ft_splitspace(cmd), fd);
}

int	ft_first_child(char **av, int fd[2])
{
	int		infile;
	pid_t	childpid;
	char	here_doc;

	here_doc = (ft_strcmp(av[1], "here_doc") == 0);
	infile = ft_get_infile(av[1], av[2]);
	childpid = fork();
	if (childpid < 0)
		ft_error("fork failed", strerror(errno));
	if (childpid == 0)
		ft_child(av[1 + here_doc], fd);
	return (2 + here_doc);
}

void	ft_parent(char **av, int fd[2], int i)
{
	int	outfile;

	i++;
	if (ft_strcmp(av[1], "here_doc"))
		outfile = open(av[i], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	else
		outfile = open(av[i], O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
	if (outfile < 0)
		ft_error(av[i], strerror(errno));
	if (dup2(fd[0], STDIN_FILENO) < 0 || dup2(outfile, STDOUT_FILENO) < 0)
		ft_error("dup2 failed", strerror(errno));
	// close(fd[1]);
	fd[1] = outfile;
	ft_exec(ft_splitspace(av[--i]), fd);
}

void	ft_loop(char *cmd, int fd[2])
{
	pid_t	childpid;

	childpid = fork();
	if (childpid < 0)
		ft_error("fork failed", strerror(errno));
	if (childpid == 0)
		ft_child(cmd, fd);
	close(fd[1]);
}

int	main(int ac, char **av)
{
	int	prev;
	int	next;
	int	fd[2];
	int	i;

	if (ac == 1)
		ft_error("usage", "./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2");
	if (ac < 5)
		ft_error("bad args", NULL);
	i = ft_first_child(av, fd);
	while (av[i + 2])
	{
		prev = fd[0];
		if (pipe(fd) == -1)
			ft_error("pipe failed", strerror(errno));
		next = fd[0];
		fd[0] = prev;
		ft_loop(av[i++], fd);
		prev = next;
	}
	ft_parent(av, fd, i);
	return (0);
}
