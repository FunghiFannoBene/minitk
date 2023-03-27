/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shhuang <shhuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 17:44:12 by sum               #+#    #+#             */
/*   Updated: 2023/03/26 00:44:30 by shhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include "libft/libft.h"
#include "libft/ft_printf/ft_printf.h"

void	action(int sig, siginfo_t *info, void *context)
{
	static int	bit;
	static char	c;

	(void)context;
	if (bit < 8)
	{
		c = c << 1;
		if (sig == SIGUSR2)
			c++;
		bit++;
	}
	if (bit >= 8)
	{
		if (c == 0)
			write(1, "\n", 1);
		else
			write(1, &c, 1);
		c = 0;
		bit = 0;
	}
	kill(info->si_pid, SIGUSR2);
}

int	main(void)
{
	struct sigaction	sa;

	ft_printf("PID : ");
	ft_printf("%d", getpid());
	ft_printf("\n");
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	sa.sa_flags = SA_SIGINFO | SA_NODEFER;
	sa.sa_sigaction = action; //assegna nome funzione.
	sigaction(SIGUSR1, &sa, 0); //utilizza funzione action presente nel client dandogli questi parametri.
	sigaction(SIGUSR2, &sa, 0); //utilizza funzione action presente nel client dandogli questi parametri.
	while (1)
		pause();
	return (0);
}
