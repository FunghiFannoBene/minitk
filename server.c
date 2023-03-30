/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 19:32:23 by marvin            #+#    #+#             */
/*   Updated: 2023/03/27 19:32:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
			write(1, "\n", 1);
		else
			write(1, &c, 1);
		c = 0;
		c_bit = 0;
	}
	kill(info->si_pid, SIGUSR2);
}

int main()
{
	printf("Server PID: %d\n", getpid());
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

//as an empty signal set. A signal set 
//is a collection of signals that can be used to manage and manipulate signal handling.
// ◦ write
// ◦ ft_printf and any equivalent YOU coded
// ◦ signal
// ◦ sigemptyset
// ◦ sigaddset
// ◦ sigaction
// ◦ kill
// ◦ getpid
// ◦ malloc
// ◦ free
// ◦ pause
// ◦ sleep
// ◦ usleep
// ◦ exit


// I parametri della funzione action hanno un valore definito, che viene assegnato dalla libreria che invia il segnale. Tuttavia, il valore di questi parametri dipende dal tipo di segnale ricevuto e dalle specifiche esigenze del programma.

// Ad esempio, il valore del parametro sig dipende dal tipo di segnale ricevuto (SIGUSR1 o SIGUSR2). Il valore del
//  parametro info contiene informazioni sul segnale ricevuto, come l'ID del processo mittente o il PID del processo 
//  che ha ricevuto il segnale. Infine,
//  il parametro context contiene informazioni sullo stato del processo al momento della ricezione del segnale.

// In sintesi, i parametri della funzione action non sono senza valore, ma il loro valore dipende dal contesto in 
// cui vengono utilizzati e dalle specifiche esigenze del programma. La libreria che invia il segnale assegna un valore
//  specifico a ciascun parametro, e il programma ricevente può utilizzare questi valori per eseguire un'azione specifica.