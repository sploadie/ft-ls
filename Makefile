# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/20 16:35:37 by tgauvrit          #+#    #+#              #
#    Updated: 2014/11/27 09:26:20 by tgauvrit         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =			ft_ls

CC =			gcc

FLAGS =			-Wall -Werror -Wextra

HEADERS =		-I ./includes/ -I $(FT_LIB_DIR) -I $(AL_LIB_DIR)

LIBRARIES =		-L$(FT_LIB_DIR) -l$(FT_LIB_NAME) -L$(AL_LIB_DIR) -l$(AL_LIB_NAME)

FT_LIB_NAME =	ft

FT_LIB =		lib$(FT_LIB_NAME).a

FT_LIB_DIR =	./libft/

AL_LIB_NAME =	arylst

AL_LIB =		lib$(AL_LIB_NAME).a

AL_LIB_DIR =	./arraylist/

SRC_DIR =		./srcs/

SRC_COMPILED =	main.o

all: $(NAME)

$(NAME): $(FT_LIB) $(AL_LIB) $(SRC_COMPILED)
	$(CC) -o $(NAME) $(FLAGS) $(LIBRARIES) $(HEADERS) $(SRC_COMPILED)

$(SRC_COMPILED): %.o: $(SRC_DIR)%.c
	$(CC) -c $(FLAGS) $(HEADERS) -L$(FT_LIB_DIR) -l$(FT_LIB_NAME) $< -o $@

$(FT_LIB):
	make -C $(FT_LIB_DIR);

$(AL_LIB):
	make -C $(AL_LIB_DIR);

clean:
	-/bin/rm -f $(COMPILED)

fclean: clean
	-/bin/rm -f $(FT_LIB)

re: fclean all
