# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lrocca <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/15 00:18:39 by lrocca            #+#    #+#              #
#    Updated: 2021/06/19 02:54:56 by lrocca           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror
INC		=	-I$(INC_DIR) -I$(LIB_DIR)

NAME	=	pipex

FILES	=	exec.c error.c

FILES_BONUS	=	bonus/main.c bonus/infile.c

ifdef WITH_BONUS
FILES	+=	$(FILES_BONUS)
else
FILES	+=	main.c
endif

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
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(LIBFT): $(LIB_DIR)
	$(MAKE) -C $^

clean: FILES += main.c $(FILES_BONUS)
clean:
	$(MAKE) clean -C $(LIB_DIR)
	$(RM) $(OBJ)

fclean: clean
	$(MAKE) fclean -C $(LIB_DIR)
	$(RM) $(NAME) ./in ./out

re: fclean all

bonus:
	@$(MAKE) WITH_BONUS=1 all
