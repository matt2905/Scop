# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmartin <mmartin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/06/06 14:10:02 by mmartin           #+#    #+#              #
#    Updated: 2015/06/09 19:43:01 by mmartin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra -g
INC			=	-I./minilibx -I./includes -I./libft/includes
LIB			=	-L./libft -lft -L./minilibx -lmlx -framework OpenGl -framework AppKit

NAME		=	scop
LIBFT		=	libft/libft.a
MLX			=	minilibx/libmlx.a

DOBJ		=	obj/

SRC			=	srcs/main.c					\
				srcs/ft_delete_object.c		\
				srcs/ft_get_light.c			\
				srcs/ft_get_materials.c		\
				srcs/ft_get_object.c		\
				srcs/ft_mlx_event.c			\
				srcs/ft_parse.c				\
				srcs/ft_parse_object.c		\
				srcs/ft_parse_material.c	\
				srcs/ft_parse_material2.c	\
				srcs/ft_shader.c

OBJ			=	$(patsubst %.c, $(DOBJ)%.o, $(SRC))
DEPS		=	$(patsubst %.c, $(DOBJ)%.d, $(SRC))
DEPENDS		=	-MT $@ -MD -MP -MF $(subst .o,.d,$@)

all:		$(MLX) $(LIBFT) $(NAME)

$(NAME):	$(OBJ)
	@echo "\033[32m$(CC) \033[33m$(CFLAGS) \033[36m-o $@ $^ $(LIB)\033[0m"
	@$(CC) $(CFLAGS) -o $@ $^ $(LIB)
	@echo "\033[33m"Compilation of $@ : "\033[32m"Success"\033[0m"

$(MLX):
	@Make -C minilibx

$(LIBFT):
	@git submodule init
	@git submodule update
	@Make -C libft

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
	@Make fclean -C libft
	@Make fclean -C minilibx
	@/bin/rm -f $(NAME)
	@/bin/rm -rf $(NAME).dSYM
	@echo "\033[31m$(NAME) : deleted\033[0m"

re:			fclean all

norme:
	find . -name "*.[ch]" -not -path "./minilibx/*" -exec /usr/bin/norminette {} \+

.PHONY:		all re fclean clean
