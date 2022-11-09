# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmartin <mmartin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/06/06 14:10:02 by mmartin           #+#    #+#              #
#    Updated: 2016/02/25 09:40:07 by mmartin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra --pedantic
LDFLAGS		=	"-Wl,--no-as-needed,-ldl"
INC			=	-I$(HOME)/.brew/include -I./includes -I./Libft/includes
LIB			=	-L./Libft -lft -lGL -lglfw3 -lm -lpthread

NAME		=	scop
LIBFT		=	Libft/libft.a

DOBJ		=	obj/

SRC			=	srcs/main.c					\
				srcs/ft_create_object.c		\
				srcs/ft_cutt_triangle.c		\
				srcs/ft_delete_object.c		\
				srcs/ft_event.c				\
				srcs/ft_get_fragments.c		\
				srcs/ft_get_light.c			\
				srcs/ft_get_materials.c		\
				srcs/ft_get_object.c		\
				srcs/ft_init.c				\
				srcs/ft_matrix.c			\
				srcs/ft_matrix_cal.c		\
				srcs/ft_move.c				\
				srcs/ft_move_bis.c			\
				srcs/ft_parse.c				\
				srcs/ft_parse_object.c		\
				srcs/ft_parse_material.c	\
				srcs/ft_parse_material2.c	\
				srcs/ft_parse_material3.c	\
				srcs/ft_read_tga.c			\
				srcs/ft_shader.c			\
				srcs/ft_vector.c			\
				srcs/ft_vector_tool.c		\

OBJ			=	$(patsubst %.c, $(DOBJ)%.o, $(SRC))
DEPS		=	$(patsubst %.c, $(DOBJ)%.d, $(SRC))
DEPENDS		=	-MT $@ -MMD -MP -MF $(subst .o,.d,$@)

all:		$(LIBFT) $(NAME)

$(NAME):	$(OBJ)
	@echo "\033[32m$(CC) \033[33m$(CFLAGS) \033[36m-o $@ $^ $(LIB)\033[0m"
	@$(CC) $(CFLAGS) -o $@ $^ $(LIB) $(LDFLAGS)
	@echo "\033[33m"Compilation of $@ : "\033[32m"Success"\033[0m"

$(LIBFT):
	@git submodule init
	@git submodule update
	@make -C Libft

-include	$(OBJ:.o=.d)

$(DOBJ)%.o:	%.c
	@mkdir -p $(DOBJ)
	@mkdir -p $(DOBJ)srcs
	@echo "\033[32m$(CC) \033[33m$(CFLAGS) \033[35m$(DEPENDS) \033[36m-c $< -o $@ $(INC)\033[0m"
	@$(CC) $(CFLAGS) $(DEPENDS) -c $< -o $@ $(INC)

clean:
	@/bin/rm -rf $(DOBJ)
	@echo "\033[31mObjects of $(NAME) : deleted\033[0m"

fclean:		clean
	@make fclean -C Libft
	@/bin/rm -f $(NAME)
	@/bin/rm -rf $(NAME).dSYM
	@echo "\033[31m$(NAME) : deleted\033[0m"

re:			fclean all

.PHONY:		all re fclean clean
