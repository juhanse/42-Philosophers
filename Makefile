# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: juhanse <juhanse@student.s19.be>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/12 18:25:19 by juhanse           #+#    #+#              #
#    Updated: 2025/02/12 18:36:03 by juhanse          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philosophers
CC = cc
CFLAGS = -Wall -Werror -Wextra

COLOUR_GREEN=\033[0;32m
COLOUR_RED=\033[0;31m
COLOUR_BLUE=\033[0;34m
COLOUR_END=\033[0m

PATH_SRCS = src/
PATH_UTILS = src/utils/

HEADERS = philo.h
SRCS = main.c init.c
UTILS = ft_atoi.c

SRCS_OBJS = $(addprefix $(PATH_SRCS), $(SRCS:.c=.o))
UTILS_OBJS = $(addprefix $(PATH_UTILS), $(UTILS:.c=.o))
OBJS = $(SRCS_OBJS) $(UTILS_OBJS)

all: $(NAME)

$(NAME): $(OBJS) $(HEADERS)
	ar -rsc $(NAME) $(OBJS)
	@echo "$(COLOUR_GREEN)Compiled ✅$(COLOUR_END)"

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	@echo "$(COLOUR_RED)Cleaned 🧹$(COLOUR_END)"

fclean: clean
	rm -f $(NAME)
	@echo "$(COLOUR_RED)Cleaned all 🧹$(COLOUR_END)"

re: fclean all

.PHONY: all clean fclean re
