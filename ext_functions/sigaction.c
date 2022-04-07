#include <signal.h>
#include <string.h>

static void	handler(int signal, siginfo_t *siginfo, void *context) // recoit signaux
{
	(void) context;
	// actions + kill
	// siginfo contient pid de l'envoyeur
}

int main(int ac, char **av)
{
	struct sigaction	sig;

	memset(&sig, '\0', sizeof(sig)); // initialisation struct
	sig.sa_sigaction = &handler; // pointeur sur fonction du handler
	sig.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sig, NULL); // sigaction(signal, pointeur struct, NULL);
}
