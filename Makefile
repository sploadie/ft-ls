# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/20 16:35:37 by tgauvrit          #+#    #+#              #
#    Updated: 2015/01/10 09:25:11 by tgauvrit         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =			ft_ls

CC =			gcc

FLAGS =			-Wall -Werror -Wextra

HEADER =		./includes/ls.h

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
				del_filedir_arlst.o \
				ls_filedir_cmp.o \
				ls_isdir.o \
				ls_dirs.o \
				ls_files.o \
				ls_buckle.o \
				ls_first.o \
				ls_loop.o \
				ls_gen_filedirs.o \
				ls_print.o \
				filedir.o \
				del_filedir.o \
				ls_perror.o \
				check_malloc.o \
				isoption.o \
				check_options.o \
				ft_strjoinfree.o \
				ft_sort_string_array.o \
				id_to_name.o \
				ls_print_l.o \
				ls_print_sp.o \
				get_set_l_info.o \
				ls_l_prepare.o \
				isdots.o \
				show_entry.o \
				digitc.o \
				getacl.o

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
