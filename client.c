/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 19:32:42 by marvin            #+#    #+#             */
/*   Updated: 2023/03/27 19:32:42 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	ft_atoi(const char *str)
{
	int	res;
	int	negative;

	negative = 1;
	res = 0;
	while (*str && (*str == ' ' || *str == '\n' || *str == '\t' ||
			*str == '\v' || *str == '\f' || *str == '\r'))
		++str;
	if (*str == '-')
		negative = -1;
	if (*str == '-' || *str == '+')
		++str;
	while (*str && *str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - 48);
		++str;
	}
	return (res * negative);
}

void	message(int pid, char c)
{
	static int	c_bit;

	c_bit = 7;
	while (c_bit >= 0)
	{
		if ((c >> c_bit) % 2 == 0) // c >> bit -------------------- c / 128 ---------------------- c / pow(2, bit) sono la stessa cosa. shifto a destra 7 posizioni quindi rimane solo l'ultimo.
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		c_bit--;
		usleep(50);
	}
}		

static void	sig_back(int sig)
{
	(void)sig;
}

int	main(int argc, char **argv)
{
	int	i;
	i = 0;
	int serv_pid;
	signal(SIGUSR1, sig_back);
	signal(SIGUSR2, sig_back);
	if (argc == 3 && ft_atoi(argv[1]) >= 1)
	{	
		serv_pid = ft_atoi(argv[1]); //pid del server.
		while (argv[2][i]) //finche messaggio
		{
			message(serv_pid, argv[2][i]);
			i++;
		}
		message(serv_pid, 0);
	}
	else
	{
		printf("Errore. Accetta solo 1 stringa.\n");
		return (0);
	}
	return (0);
}
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

// signal(SIGINT, gestione_segnale);
// SIGHUP - inviato a un processo quando il terminale di controllo viene chiuso o disconnesso.
// SIGINT - inviato a un processo quando l'utente preme Ctrl+C per interrompere il processo.
// SIGQUIT - inviato a un processo quando l'utente preme Ctrl+\ per abbandonare il processo.
// SIGILL - inviato a un processo quando viene tentata l'esecuzione di un'istruzione illegale.
// SIGABRT - inviato a un processo quando viene chiamata la funzione abort().
// SIGFPE - inviato a un processo quando viene rilevato un errore in una operazione in virgola mobile.
// SIGKILL - inviato a un processo per terminarlo immediatamente. Non può essere gestito o ignorato dal processo.
// SIGSEGV - inviato a un processo quando viene tentato l'accesso ad una regione di memoria non valida.
// SIGPIPE - inviato a un processo quando tenta di scrivere su un socket o una pipe che è 
// stata chiusa dal processo di destinazione.
// SIGALRM - inviato a un processo quando scade un timer impostato con la funzione alarm().
// SIGTERM - inviato a un processo per richiedere la sua terminazione.
// SIGUSR1 e SIGUSR2 - segnali definiti dall'utente che possono essere utilizzati 
// per inviare messaggi personalizzati tra processi o per attivare funzionalità specifiche.
