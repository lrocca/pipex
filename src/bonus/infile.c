/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrocca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 18:45:54 by lrocca            #+#    #+#             */
/*   Updated: 2021/06/19 02:53:50 by lrocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus.h"

static char	*ft_bufjoin(char *line, char buffer[128])
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	new = malloc(ft_strlen(line) + ft_strlen(buffer) + 1);
	if (!new)
		return (NULL);
	while (line && line[j])
		new[i++] = line[j++];
	if (line)
	{
		free(line);
		line = NULL;
	}
	j = 0;
	while (buffer && buffer[j])
		new[i++] = buffer[j++];
	new[i] = '\0';
	return (new);
}

static char	get_next_line(int fd, char **line)
{
	int		n;
	int		i;
	char	c;
	char	buffer[128];

	*line = NULL;
	i = 0;
	n = 1;
	while (n > 0)
	{
		n = read(fd, &c, 1);
		if (c == '\n')
			break ;
		buffer[i] = c;
		i++;
		if (i == 127)
		{
			buffer[i] = '\0';
			*line = ft_bufjoin(*line, buffer);
			i = 0;
		}
	}
	buffer[i] = '\0';
	*line = ft_bufjoin(*line, buffer);
	return (n);
}

static void	ft_here_doc(int fd, char *del)
{
	char	*line;
	char	ret;

	ret = 1;
	line = NULL;
	while (ret > 0)
	{
		ret = get_next_line(STDIN_FILENO, &line);
		if (ft_strcmp(line, del) == 0)
			break ;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		line = NULL;
	}
	if (ret < 0)
		ft_error("read failed", strerror(errno));
	if (line)
		free(line);
}

int	ft_get_infile(char *filename, char *delimiter)
{
	int	fd[2];
	int	infile;

	if (!ft_strcmp(filename, "here_doc"))
	{
		if (pipe(fd) == -1)
			ft_error("pipe failed", strerror(errno));
		ft_here_doc(fd[1], delimiter);
		close(fd[1]);
		return (fd[0]);
	}
	infile = open(filename, O_RDONLY);
	if (infile < 0)
		ft_error(filename, strerror(errno));
	return (infile);
}
