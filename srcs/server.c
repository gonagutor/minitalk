/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaguado- <gaguado-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 17:48:46 by gaguado-          #+#    #+#             */
/*   Updated: 2021/11/23 18:10:42 by gaguado-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

void	print_recv_char(char recv)
{
	static int	count = 8;
	static char	character = 0;

	count--;
	character = (character & 0xFF) | (recv << count);
	if (count == 0)
	{
		ft_putchar_fd(character, 1);
		count = 8;
		character = 0;
	}
}

void	handle_signal_data(int signum, siginfo_t *siginfo, void *ctx)
{
	struct sigaction	sigact;

	ctx = NULL;
	sigact.__sigaction_u.__sa_sigaction = handle_signal_data;
	sigact.sa_flags = SA_SIGINFO;
	sigaction(signum, &sigact, NULL);
	print_recv_char(signum - 30);
	kill(siginfo->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sigact;

	sigact.__sigaction_u.__sa_sigaction = handle_signal_data;
	sigact.sa_flags = SA_SIGINFO;
	ft_putstr_fd("Server stated.\nServer PID: ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
	sigaction(SIGUSR1, &sigact, NULL);
	sigaction(SIGUSR2, &sigact, NULL);
	while (1)
		;
	return (0);
}
