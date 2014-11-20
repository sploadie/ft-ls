# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/20 16:35:37 by tgauvrit          #+#    #+#              #
#    Updated: 2014/11/20 17:11:29 by tgauvrit         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =			ft_ls

CC =			gcc

FLAGS =			-Wall -Werror -Wextra

HEADERS =		-I ./includes/ -I $(FT_LIB_DIR)

FT_LIB_NAME =	ft

FT_LIB =		lib$(FT_LIB_NAME).a

FT_LIB_DIR =	./libft/

SRC_DIR =		./srcs/

SRC_COMPILED =	main.o

all: $(NAME)

$(NAME): $(FT_LIB) $(SRC_COMPILED)
	$(CC) -o $(NAME) -L$(FT_LIB_DIR) -l$(FT_LIB_NAME) $(FLAGS) $(HEADERS) $(SRC_COMPILED)

$(SRC_COMPILED): %.o: $(SRC_DIR)%.c
	$(CC) -c $(FLAGS) $(HEADERS) -L$(FT_LIB_DIR) -l$(FT_LIB_NAME) $< -o $@

$(FT_LIB):
	make -C $(FT_LIB_DIR);

clean:
	-/bin/rm -f $(COMPILED)

fclean: clean
	-/bin/rm -f $(FT_LIB)

re: fclean all
