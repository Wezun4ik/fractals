NAME = fractol

FLAGS = -Wall -Wextra -Werror

INCLUDES = ./libft/

FILES = manage.c cl.c buttons.c fractol.c

LIBX = -L /usr/local/lib -lm -framework OpenCL -framework OpenGL -framework AppKit -L /usr/local/lib -lmlx

all: $(NAME)

$(NAME):

	make -C libft/ fclean && make -C libft/
	gcc -g -o $(NAME) $(FILES)  $(FLAGS) $(LIBX) ./libft/libft.a

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all