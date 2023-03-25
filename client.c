/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shhuang <shhuang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 18:18:45 by sum               #+#    #+#             */
/*   Updated: 2023/03/26 00:44:38 by shhuang          ###   ########.fr       */
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

static void	sig_back(int sig)
{
	(void)sig;
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
	return (0);
}
