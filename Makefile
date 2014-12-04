# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/20 16:35:37 by tgauvrit          #+#    #+#              #
#    Updated: 2014/12/04 16:11:21 by tgauvrit         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =			ft_ls

CC =			gcc

FLAGS =			-Wall -Werror -Wextra

HEADER =		ls.h

HEADER_DIR =	-I ./includes/ -I $(FT_LIB_DIR) -I $(AL_LIB_DIR)

LIBRARIES =		-L$(FT_LIB_DIR) -l$(FT_LIB_NAME) -L$(AL_LIB_DIR) -l$(AL_LIB_NAME)

FT_LIB_NAME =	ft

FT_LIB =		lib$(FT_LIB_NAME).a

FT_LIB_DIR =	./libft/

AL_LIB_NAME =	arylst

AL_LIB =		lib$(AL_LIB_NAME).a

AL_LIB_DIR =	./arraylist/

SRC_DIR =		./srcs/

SRC_COMPILED =	main.o \
				filedir.o \
				del_filedir.o \
				ls_perror.o \
				check_malloc.o \
				isoption.o \
				check_options.o \
				ft_strjoinfree.o \
				ft_sort_string_array.o

COMPILED =		$(SRC_COMPILED)

all: $(NAME)

$(NAME): $(FT_LIB) $(AL_LIB) $(SRC_COMPILED)
	$(CC) -o $(NAME) $(FLAGS) $(LIBRARIES) $(HEADER_DIR) $(SRC_COMPILED)

$(SRC_COMPILED): %.o: $(SRC_DIR)%.c $(HEADER)
	$(CC) -c $(FLAGS) $(HEADER_DIR) $< -o $@

$(FT_LIB):
	@make -C $(FT_LIB_DIR);

$(AL_LIB):
	@make -C $(AL_LIB_DIR);

clean:
	-/bin/rm -f $(COMPILED)

fclean: clean
	-/bin/rm -f $(NAME)

re: fclean all
