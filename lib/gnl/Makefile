# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: edubois- <edubois-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/31 00:21:13 by edubois-          #+#    #+#              #
#    Updated: 2024/10/31 00:37:23 by edubois-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS := get_next_line.c\
	get_next_line_utils.c\
		
OBJS := $(SRCS:.c=.o)

CC := cc
FLAGS := -Wall -Werror -Wextra

NAME := gnl.a

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
