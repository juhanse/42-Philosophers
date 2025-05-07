# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: juhanse <juhanse@student.s19.be>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/12 18:25:19 by juhanse           #+#    #+#              #
#    Updated: 2025/05/07 15:31:25 by juhanse          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS = -Wall -Werror -Wextra -g
RM = rm -rf

COLOUR_GREEN=\033[0;32m
COLOUR_RED=\033[0;31m
COLOUR_BLUE=\033[0;34m
COLOUR_END=\033[0m

SRCDIR = srcs/
OBJDIR = objs/

UTILS = utils/ft_atoi.c utils/ft_timestamp.c utils/ft_logs.c utils/ft_isdigit.c utils/ft_free.c utils/ft_malloc.c
SRC = main.c init.c actions.c philo.c $(UTILS)

SRCS = $(addprefix $(SRCDIR), $(SRC))
OBJS = $(addprefix $(OBJDIR), $(SRC:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(COLOUR_GREEN)Compiled ✅$(COLOUR_END)"

$(OBJDIR)%.o : $(SRCDIR)%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJDIR)
	@echo "$(COLOUR_RED)Cleaned 🧹$(COLOUR_END)"

fclean: clean
	$(RM) $(NAME)
	@echo "$(COLOUR_RED)Cleaned all 🧹$(COLOUR_END)"

re: fclean all

.PHONY: all clean fclean re
