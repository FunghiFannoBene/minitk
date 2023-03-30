
#include "minitalk.h"

//funzione sigaction() viene utilizzata per registrare la funzione action come gestore di 
//segnale per i segnali specificati,
//e il valore del segnale viene passato come primo argomento della funzione sigaction().

void go(int signum, siginfo_t *info, void *ucontext) //prende valori dalla funzione KILL del client/server
{
	static int	c_bit;
	static char	c; //le statiche hanno un valore di 0 se non assegnateli un valore, oppure il valore successivo residuo.
	(void) ucontext; //casto void perchè è un parametro non usato ma presente e obbligatorio.

	if (c_bit < 8)
	{
		c = c << 1;
		if (signum == SIGUSR2)
			c++;
		c_bit++;
	}
	if (c_bit >= 8)
	{
		if (c == 0)
		{
			write(1, "\n", 1);
			kill(info->si_pid, SIGUSR1);
		}
		else
			write(1, &c, 1);
		c = 0;
		c_bit = 0;
	}
	kill(info->si_pid, SIGUSR2);
}

int main()
{
	printf("Server Process ID: %d\n", getpid());
	struct sigaction s_action;
	sigemptyset(&s_action.sa_mask);
	sigaddset(&s_action.sa_mask, SIGUSR1);
	sigaddset(&s_action.sa_mask, SIGUSR2);
	s_action.sa_flags = SA_SIGINFO | SA_NODEFER;
	s_action.sa_sigaction = go; //assegna nome funzione.
	sigaction(SIGUSR1, &s_action, 0); //utilizza funzione action presente nel client dandogli questi parametri.
	sigaction(SIGUSR2, &s_action, 0); //utilizza funzione action presente nel client dandogli questi parametri.
	while (1)
		pause();
	return (0);
}