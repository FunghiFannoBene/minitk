# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/29 03:30:38 by marvin            #+#    #+#              #
#    Updated: 2023/03/29 03:30:38 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minitalk
BONUS = minitalk_bonus
PRINTF = ft_printf/libftprintf.a
CC = cc

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME):
	make -C ft_printf
	$(CC) $(FLAGS) server.c $(PRINTF) -o server
	$(CC) $(FLAGS) client.c $(PRINTF) -o client

re: fclean all

clean:
	make clean -C ft_printf
	rm -rf server
	rm -rf client

fclean:
	make fclean -C ft_printf
	rm -rf server
	rm -rf client

bonus:
	make -C ft_printf
	$(CC) $(FLAGS) server_bonus.c $(PRINTF) -o server
	$(CC) $(FLAGS) client_bonus.c $(PRINTF) -o client
	
.PHONY: all re clean fclean bonus
