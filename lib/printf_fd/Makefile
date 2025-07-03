# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: edubois- <edubois-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/21 07:34:22 by edubois-          #+#    #+#              #
#    Updated: 2024/10/31 00:57:30 by edubois-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS := ft_printf.c\
		ft_putchar.c\
		ft_putstr.c\
		ft_putnbr_unsigned.c\
		ft_putnbr.c\
		ft_adress_hexa.c\
		ft_putnbr_hexa.c\
		ft_putnbr_unsigned.c\
		ft_strchr.c\
		
OBJS := $(SRCS:.c=.o)

CC := cc
FLAGS := -Wall -Werror -Wextra -fPIC 

NAME := libftprintf.a

all: $(NAME)

$(NAME): $(OBJS)
	ar -rc $(NAME) $(OBJS)

%.o : %.c
	$(CC) $(FLAGS) -o $@ -c $<

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean all fclean re
