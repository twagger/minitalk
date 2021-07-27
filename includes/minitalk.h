/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twagner <twagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/17 11:17:45 by twagner           #+#    #+#             */
/*   Updated: 2021/07/19 17:31:01 by twagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H
# define SIGUSR1 30
# define SIGUSR2 31
# define MASK 0x80

# include <unistd.h>
# include <signal.h>
# include <stdlib.h>

typedef struct s_byte
{
	unsigned char	c;
	int				size;
}					t_byte;

void	ft_putnbr_fd(int n, int fd);
void	ft_putchar_fd(char c, int fd);
int		ft_atoi(const char *str);
void	ft_init_byte(t_byte *byte);

#endif