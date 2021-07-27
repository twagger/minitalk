/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/17 11:16:41 by twagner           #+#    #+#             */
/*   Updated: 2021/07/19 17:57:37 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_byte	g_byte;

void	ft_bit_receiver(int sig, siginfo_t *siginfo, void *context)
{
	if (context && siginfo)
		usleep(1);
	if (sig == SIGUSR1)
		g_byte.c += 1 << (7 - g_byte.size);
	++g_byte.size;
	if (g_byte.size == 8)
	{
		write(1, &g_byte.c, 1);
		ft_init_byte(&g_byte);
	}
}

int	main(void)
{
	struct sigaction	act;
	sigset_t			block_mask;

	sigemptyset(&block_mask);
	sigaddset(&block_mask, SIGUSR1);
	sigaddset(&block_mask, SIGUSR2);
	act.sa_mask = block_mask;
	act.sa_sigaction = &ft_bit_receiver;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
	ft_init_byte(&g_byte);
	while (1)
	{
		pause();
	}
	return (0);
}
