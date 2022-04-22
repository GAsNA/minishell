#include <stdlib.h>

int	main(int ac, char **av)
{
	int		pid;

	pid = atoi(av[1]);
	// envoie d'un signal a un processus
	kill(pid, SIGUSR1); // kill(pid du receveur, type de signal)
}
