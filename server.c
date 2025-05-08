/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimachad <dimachad@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 22:55:39 by dimachad          #+#    #+#             */
/*   Updated: 2025/05/09 01:34:03 by dimachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	signal_handler(int signal)
{
	static int	i_bit = 8;
	static char	letter = 0;

	i_bit--;
	letter = letter << 1;
	if (signal == SIGUSR2)
		letter |= 1;
	if (i_bit == 0)
	{
		write(1, &letter, 1);
		i_bit = 8;
		letter = 0;
	}
}

int	main(void)
{
	struct sigaction	signal;

	ft_printf("SERVER_ID:%d", getpid());
	signal.sa_handler = signal_handler;
	signal.sa_flags = 0;
	sigaction(SIGUSR1, &signal, NULL); 
	sigaction(SIGUSR2, &signal, NULL); 
	while (1)
		usleep(1000);
	return (0);
}
