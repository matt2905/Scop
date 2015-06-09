#
#

NAME	=	libmlx.a

SRC		=	mlx_init_loop.m				\
			mlx_int_str_to_wordtab.c	\
			mlx_new_image.m				\
			mlx_new_window.m			\
			mlx_opengl.m				\
			mlx_shaders.c				\
			mlx_xpm.c

OBJ1	=	$(SRC:.c=.o)
OBJ		=	$(OBJ1:.m=.o)
CFLAGS	+=	-O2

all:		$(NAME)

$(NAME):	$(OBJ)
	ar -r $(NAME) $(OBJ)
	ranlib $(NAME)

clean:
	rm -f $(OBJ)
	rm -f mlx_app

fclean:		clean
	rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
