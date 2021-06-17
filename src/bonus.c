/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrocca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 18:46:50 by lrocca            #+#    #+#             */
/*   Updated: 2021/06/17 20:47:04 by lrocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	ft_child(char **av, char **env, int fd[2])
{
	// if (dup2(fd[1], STDOUT_FILENO) < 0 || dup2(infile, STDIN_FILENO) < 0)
		ft_error("dup2 failed", strerror(errno));
	close(fd[0]);
	// fd[0] = infile;
	ft_exec(ft_splitspace(av[2]), env, fd);
}

void	ft_parent(char **av, char **env, int fd[2])
{
	int	outfile;

	if (ft_strcmp(av[1], "here_doc"))
		outfile = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	else
		outfile = open(av[4], O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
	if (outfile < 0)
		ft_error(av[4], strerror(errno));
	if (dup2(fd[0], STDIN_FILENO) < 0 || dup2(outfile, STDOUT_FILENO) < 0)
		ft_error("dup2 failed", strerror(errno));
	close(fd[1]);
	fd[1] = outfile;
	ft_exec(ft_splitspace(av[3]), env, fd);
}

void	ft_loop(void)
{
	pid_t	childpid;

	childpid = fork();
	if (childpid < 0)
		ft_error("fork failed", strerror(errno));
	if (childpid == 0)
		;
		// ft_child(av, env, fd);
}

int	ft_get_infile(char *filename)
{
	int	infile;

	if (!ft_strcmp(filename, "here_doc"))
		return (0);
	else if (access(filename, R_OK) < 0)
		ft_error(filename, strerror(errno));
	infile = open(filename, O_RDONLY);
	if (infile < 0)
		ft_error(filename, strerror(errno));
	return (infile);
}

int	main(int ac, char **av, char **env)
{
	int	fd[2];
	int	i;
	int	infile;

	if (ac == 1)
		ft_error("usage", "./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2");
	if (ac < 5)
		ft_error("bad args", NULL);
	infile = ft_get_infile(av[1]);
	i = 2;
	while (av[i + 2])
	{
		if (pipe(fd) == -1)
			ft_error("pipe failed", strerror(errno));
		ft_loop();
	}
	ft_parent(av, env, fd);
	return (0);
}
