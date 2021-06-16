/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrocca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 12:23:50 by lrocca            #+#    #+#             */
/*   Updated: 2021/06/16 14:29:30 by lrocca           ###   ########.fr       */
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

char	*get_path(char **env);
char	*find_exec(char *cmd, char **env);

#endif
