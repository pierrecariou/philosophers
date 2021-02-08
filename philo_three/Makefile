# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pcariou <pcariou@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/03 15:02:53 by pcariou           #+#    #+#              #
#    Updated: 2021/02/08 13:24:58 by pcariou          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= philo_one

HEADER		= ./

SRCS		=	main.c \
				philosopher.c \
				die_in_action.c \
				utils.c

OBJS		= $(SRCS:.c=.o)

CFLAGS		= -Wall -Wextra -Werror

all:		$(NAME)

.c.o:
			gcc $(CFLAGS) -c $< -o $(<:.c=.o) -I$(HEADER)

$(NAME):	$(OBJS)
			gcc -pthread -o $(NAME) $(OBJS)

clean:
			rm -f $(OBJS)

fclean:		clean
			rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
