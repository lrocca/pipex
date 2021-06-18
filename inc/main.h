/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrocca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 12:23:50 by lrocca            #+#    #+#             */
/*   Updated: 2021/06/18 20:22:13 by lrocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>

# include "libft.h"

void	ft_error(char *s1, char *s2);
void	ft_exec(char **av, int fd[2]);

#endif
