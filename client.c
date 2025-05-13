

#include "minitalk.h"

volatile sig_atomic_t ack_received = 0;

void	ack_handler(int signal)
{
	(void)signal;
	ack_received = 1;
}

void	send_message(int pid, char *message)
{
	int					bit_count;
	struct sigaction	signal;

	bit_count = 8;
	sigemptyset(&signal.sa_mask);
	signal.sa_flags = 0;
	signal.sa_handler = ack_handler;
	sigaction(SIGUSR1, &signal, NULL);
	while (*message)
	{
		bit_count = 8;
		while (bit_count--)
		{
			if ((*message >> bit_count) & 1)
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			while (!ack_received)
				pause();
			ack_received = 0;
		}
		message++;
	}
	bit_count = 8;
	while (bit_count--)
	{
		kill(pid, SIGUSR1);
		while (!ack_received)
			pause();
		ack_received = 0;
	}
}

static int	invalid_pid(char *pid)
{
	while (*pid)
	{
		if ((*pid < '0') || (*pid > '9'))
			return (write(2, "Error: pid includes non digits\n", 32));
		pid++;
	}
	return (0);
}

// This client takes two arguments
// being the first the server pid
// and the second the message
int main(int argc, char **argv)
{
	int	pid;
	
	if (argc != 3)
		return (-1);
	if (invalid_pid(argv[1]))
		return (-1);
	pid = atoi(argv[1]);
	send_message(pid, argv[2]);
	return (0);
}
