static void	handler(int signal) // ce type de prototype
{
	// generalement c'est la qu'on 'kill' (envoit de signal)
}

int	main(void)
{
	// initialisation signaux, avec fonction ou sera recu signaux
	signal(SIGUSR1, handler); // signal(signal, fonction handler)
}
