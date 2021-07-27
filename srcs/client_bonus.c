/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/17 11:16:23 by twagner           #+#    #+#             */
/*   Updated: 2021/07/19 18:03:00 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_ack;

void	ft_ack_handler(int sig, siginfo_t *siginfo, void *context)
{
	if (sig && siginfo && context)
		g_ack = 1;
	g_ack = 1;
	write(1, "message received !\n", 19);
	exit(0);
}

int	ft_send_null_byte(int pid)
{
	int	i;

	i = -1;
	g_ack = 0;
	while (++i < 8)
	{
		if (kill(pid, SIGUSR2) == -1)
			return (-1);
		usleep(50);
	}
	while (!g_ack)
		usleep(1);
	return (0);
}

int	ft_bit_transmitter(int pid, char *str)
{
	int		i;
	int		sig;

	while (*str)
	{
		i = -1;
		while (++i < 8)
		{
			g_ack = 0;
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
	if (ft_send_null_byte(pid) == -1)
		return (-1);
	return (0);
}

int	main(int ac, char **av)
{
	int					pid;
	char				*message;
	struct sigaction	act;

	act.sa_sigaction = &ft_ack_handler;
	sigaction(SIGUSR1, &act, NULL);
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
