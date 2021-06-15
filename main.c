/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrocca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 00:25:04 by lrocca            #+#    #+#             */
/*   Updated: 2021/06/15 11:41:00 by lrocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	main(int ac, char **av)
{
	if (ac != 5)
		return (1);
	// if executable is relative, find absolute path with access and env PATH
	if (av[2][0] == '/')
		return (42);
	return (0);
}
