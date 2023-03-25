# *************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sum <marvin@42.fr>                         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/06 18:09:45 by sum               #+#    #+#              #
#    Updated: 2022/12/12 15:49:16 by sum              ###   ########.fr        #
                                                                              #
# **************************************************************************** #

NAME = minitalk
BONUS = minitalk_bonus

CC = cc
LIBFT = libft/libft.a
PF = libft/ft_printf/libftprintf.a
FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME):
	make -C libft
	make -C libft/ft_printf
	$(CC) $(FLAGS) server.c $(LIBFT) $(PF) -o server
	$(CC) $(FLAGS) client.c $(LIBFT) $(PF) -o client

re: fclean all

clean:
	make clean -C libft
	make clean -C libft/ft_printf

fclean:
	make fclean -C libft
	make fclean -C libft/ft_printf
	rm -rf server
	rm -rf client

bonus:
	make -C libft
	make -C libft/ft_printf
	$(CC) $(FLAGS) server_bonus.c $(LIBFT) $(PF) -o server
	$(CC) $(FLAGS) client_bonus.c $(LIBFT) $(PF) -o client
	
.PHONY: all re clean fclean bonus

.SILENT:
