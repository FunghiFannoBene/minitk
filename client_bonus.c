/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 03:10:26 by marvin            #+#    #+#             */
/*   Updated: 2023/03/29 03:10:26 by marvin           ###   ########.fr       */
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

void	sig_back(int signum)
{
	if (signum == SIGUSR1)
	{
		printf("Messaggio inviato con successo.\n");
		exit(0);
	}
}

int	main(int argc, char **argv)
{
	int	i;
	i = 0;
	int serv_pid;
	if (argc != 3)
	{
		printf("Inserisci: %s NumeroPID Messaggio\n", argv[0]);
		return (1);
	}

	serv_pid = ft_atoi(argv[1]);
	if (kill(serv_pid, 0) == -1 && errno == ESRCH)
	{
		printf("Processo con ID %d non esiste.\n", serv_pid);
		return (1);
	}
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