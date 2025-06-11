/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimachad <dimachad@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 17:59:39 by dimachad          #+#    #+#             */
/*   Updated: 2025/06/11 19:08:18 by dimachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/printf/ft_printf.h"
#include "minitalk.h"

volatile sig_atomic_t	g_ack_received = 0;

void	ack_handler(int signal)
{
	(void)signal;
	g_ack_received = 1;
}

void	send_null(int pid)
{
	int	bit_count;

	bit_count = 8;
	while (bit_count--)
	{
		kill(pid, SIGUSR1);
		while (!g_ack_received)
			pause();
		g_ack_received = 0;
	}
}

void	send_message(int pid, char *message)
{
	int					bit_count;

	bit_count = 8;
	while (*message)
	{
		bit_count = 8;
		while (bit_count--)
		{
			if ((*message >> bit_count) & 1)
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			while (!g_ack_received)
				pause();
			g_ack_received = 0;
		}
		message++;
	}
	send_null(pid);
}

static void	setup_signal_handler(void)
{
	struct sigaction	signal;

	sigemptyset(&signal.sa_mask);
	signal.sa_flags = 0;
	signal.sa_handler = ack_handler;
	sigaction(SIGUSR1, &signal, NULL);
}

// This client takes two arguments
// being the first the server pid
// and the second the message
int	main(int argc, char **argv)
{
	int	pid;
	int	err;

	if (argc != 3)
		return (ft_printf("Error: call ./server [PID] [message]\n"));
	pid = ft_atoi(argv[1], &err);
	if (err || pid < 0)
		return (ft_printf("Error: Invalid pid"));
	setup_signal_handler();
	send_message(pid, argv[2]);
	return (0);
}
