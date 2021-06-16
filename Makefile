# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lrocca <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/15 00:18:39 by lrocca            #+#    #+#              #
#    Updated: 2021/06/16 14:22:21 by lrocca           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror
INC		=	-Iinc -Ilibft

NAME	=	pipex

SRC	=	src/main.c src/path.c
OBJ	=	$(SRC:.c=.o)

LIBFT_DIR	=	libft
LIBFT		=	$(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(INC) -c $^ -o $@

$(LIBFT): $(LIBFT_DIR)
	make -C $^

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
