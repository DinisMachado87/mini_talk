/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimachad <dimachad@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 22:55:39 by dimachad          #+#    #+#             */
/*   Updated: 2025/05/13 22:34:06 by dimachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	signal_handler(int signal, siginfo_t *info, void *context)
{
	static int	i_bit = 8;
	static char	letter = 0;

	(void)context;
	i_bit--;
	letter = letter << 1;
	if (signal == SIGUSR2)
		letter |= 1;
	if (i_bit == 0)
	{
		if (letter == '\0')
			write(1, "\n", 1);
		else
			write(1, &letter, 1);
		i_bit = 8;
		letter = 0;
	}
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	signal;

	ft_printf("SERVER_ID:%d\n", getpid());
	sigemptyset(&signal.sa_mask);
	signal.sa_flags = SA_SIGINFO;
	signal.sa_sigaction = signal_handler;
	sigaction(SIGUSR1, &signal, NULL); 
	sigaction(SIGUSR2, &signal, NULL); 
	while (1)
		pause();
	return (0);
}
