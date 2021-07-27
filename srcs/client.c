/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/17 11:16:23 by twagner           #+#    #+#             */
/*   Updated: 2021/07/19 16:08:02 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	ft_bit_transmitter(int pid, char *str)
{
	int		i;
	int		sig;

	while (*str)
	{
		i = -1;
		while (++i < 8)
		{
			if (((*str << i) & 0x80) != 0)
				sig = SIGUSR1;
			else
				sig = SIGUSR2;
			if (kill(pid, sig) == -1)
				return (-1);
			usleep(50);
		}
		++str;
	}
	return (0);
}

int	main(int ac, char **av)
{
	int		pid;
	char	*message;

	if (ac != 3)
		return (write(2, "wrong number of arguments\n", 26));
	pid = ft_atoi(av[1]);
	if (pid <= 0)
	{
		write(2, "error\n", 6);
		return (1);
	}
	message = av[2];
	if (ft_bit_transmitter(pid, message) == -1)
	{
		write(2, "error\n", 6);
		return (1);
	}
	return (0);
}
