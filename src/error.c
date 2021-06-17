/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrocca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 18:46:02 by lrocca            #+#    #+#             */
/*   Updated: 2021/06/17 18:46:21 by lrocca           ###   ########.fr       */
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
