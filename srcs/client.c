/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaguado- <gaguado-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 17:47:43 by gaguado-          #+#    #+#             */
/*   Updated: 2021/11/23 17:29:43 by gaguado-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

void	signal_callback(int i)
{
	ft_putchar_fd('*', 1);
	signal(i, signal_callback);
}

void	send_str(int pid, char *str)
{
	int	i;
	int	z;

	i = 0;
	z = 7;
	while (str[i])
	{
		while (z >= 0)
		{
			usleep(100);
			if ((str[i] >> z) & 0x01)
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			z--;
			usleep(100);
		}
		z = 7;
		i++;
	}
}

int	main(int argc, char *argv[])
{
	int	pid;

	pid = ft_atoi(argv[1]);
	if (pid == -1 || pid == 0 || argc < 3)
	{
		ft_putstr_fd("Wrong parameters. USAGE:\n\t", 1);
		ft_putstr_fd("./client <Server PID> <String to send>\n", 1);
		return (1);
	}
	signal(SIGUSR1, signal_callback);
	send_str(pid, argv[2]);
	ft_putstr_fd("\nSent \"", 1);
	ft_putstr_fd(argv[2], 1);
	ft_putstr_fd("\"", 1);
	ft_putnbr_fd(pid, 1);
	return (0);
}
