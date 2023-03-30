#include <stdlib.h>
#include <stdio.h>
#include <signal.h>


void handle_sigststp(int sig)
{
	printf("Stop not allowed\n");
}

//NOTE Tuttavia, a differenza del segnale SIGKILL, 
//il segnale SIGINT(CTRL+C nel terminal) permette al processo di interrompersi in modo controllato, ad esempio per salvare i dati o effettuare altre operazioni di cleanup.


int main(int argc, char**argv){

	struct sigaction sa; //struttura già dichiarata in signal.h
	sa.sa_handler = &handle_sigststp; //assegno funzione a handler//membro della struttura handler
	sigaction(SIGTSTP, &sa , NULL); //SEGNALE CTRL+Z nel terminal, sospende e salva le attività, indirizzo struttura

	int x;
	printf("Input number: ");
	scanf("%d", &x);
	printf("Result %d * 5 0 %d\n", x, x * 5);
	return;
}