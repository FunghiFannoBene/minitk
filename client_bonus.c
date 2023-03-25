/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shhuang <shhuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 15:49:33 by sum               #+#    #+#             */
/*   Updated: 2023/03/26 00:44:40 by shhuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include "libft/libft.h"
#include "libft/ft_printf/ft_printf.h"

void	send_message(int pid, char c)
{
	static int	bit;

	bit = 7;
	while (bit >= 0)
	{
		if ((c >> bit) % 2 == 0)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		bit--;
		usleep(100);
	}
}	

void	sig_back(int sig)
{
	if (sig == SIGUSR1)
	{
		write(1, "MESSAGE RECEIVED\n", 17);
		exit(0);
	}
}

int	main(int as, char **av)
{
	int	i;

	signal(SIGUSR1, sig_back);
	signal(SIGUSR2, sig_back);
	if (as == 3 && ft_atoi(av[1]) >= 1)
	{	
		i = 0;
		while (av[2][i])
		{
			send_message(ft_atoi(av[1]), av[2][i]);
			i++;
		}
		send_message(ft_atoi(av[1]), 0);
	}
	else
	{
		write (1, "ERROR!!", 7);
		return (0);
	}
	while (1)
		pause();
	return (0);
}
