# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lrocca <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/15 00:18:39 by lrocca            #+#    #+#              #
#    Updated: 2021/06/16 17:26:46 by lrocca           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror
INC		=	-I$(INC_DIR) -I$(LIB_DIR)

NAME	=	pipex

FILES	=	main.c exec.c

SRC_DIR	=	./src
OBJ_DIR	=	./obj
INC_DIR	=	./inc
LIB_DIR	=	./libft

SRC	=	$(addprefix $(SRC_DIR)/, $(FILES))
OBJ	=	$(patsubst $(SRC_DIR)/%, $(OBJ_DIR)/%, $(SRC:.c=.o))

LIBFT	=	$(LIB_DIR)/libft.a

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(LIBFT): $(LIB_DIR)
	make -C $^

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME) ./in ./out

re: fclean all
