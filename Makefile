NAME = fdf

SRC = main.c color.c funct_ptr.c init_stack.c get_filename.c window.c

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Werror -Wextra

FLAGS = -lXext -lX11 -lm -fPIE

all : $(NAME)

$(NAME) : $(OBJ)
		cc $(CFLAGS) $(OBJ) -o $(NAME) libmlx.a libft.a $(FLAGS)

$(OBJ) : $(SRC)
		$(MAKE) -C ./libft
		cp ./libft/libft.a ../FdF
		$(MAKE) -C ./minilibx-linux
		cp ./minilibx-linux/libmlx.a .
		cc $(CFLAGS) -c $(SRC)

clean : 
		@$(MAKE) -s clean -C ./libft
		@$(MAKE) -s clean -C ./minilibx-linux
		@rm -f $(OBJ)
		@rm -f libft.a libmlx.a

fclean : clean
		@$(MAKE) -s fclean -C ./libft
		@rm -f $(NAME)
		
re : fclean all
