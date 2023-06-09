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
	while (*str && (*str == ' ' || *str == '\n' || *str == '\t' || *str == '\v'
			|| *str == '\f' || *str == '\r'))
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
		if ((c >> c_bit) % 2 == 0)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		c_bit--;
		usleep(100);
	}
}

void	sig_back(int signum)
{
	if (signum == SIGUSR1)
	{
		ft_printf("Messaggio inviato con successo.\n");
		exit(0);
	}
}

int	main(int argc, char **argv)
{
	int	i;
	int	serv_pid;

	i = 0;
	if (argc == 3 || ft_atoi(argv[1]) > 1)
	{
	// 	ft_printf("Errore. Accetta solo 1 stringa.\n");
	// 	return (1);
	// }
	serv_pid = ft_atoi(argv[1]);
	// if (kill(serv_pid, 0) == -1 && errno == ESRCH)
	// {
	// 	ft_printf("Processo con ID %d non esiste.\n", serv_pid);
	// 	return (1);
	// }
	signal(SIGUSR1, sig_back);
	signal(SIGUSR2, sig_back);
	while (argv[2][i])
		message(serv_pid, argv[2][i++]);
	message(serv_pid, 0);
	}
	return (0);
}
