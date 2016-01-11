CC = gcc
FLAGS = -Wall -Werror -Wextra
NAME = ft_ls
SRC = main.c ft_ls.c get_params.c
OBJ = $(SRC:.c=.o)

SRCDIR = src/
OBJDIR = obj/
INCDIR = includes/
LIBDIR = libft/

all: $(NAME)

$(NAME):
	(cd $(LIBDIR); $(MAKE) all)
	(cd $(SRCDIR);$(CC) $(FLAGS) -c $(SRC) -I ../$(INCDIR) -I ../$(LIBDIR)includes/;mv $(OBJ) ../)
	$(CC) $(FLAGS) -o $(NAME) $(OBJ) -L $(LIBDIR) -lft
	mv $(OBJ) $(OBJDIR)

clean:
	(cd $(OBJDIR); rm -rf $(OBJ))

fclean: clean
	rm -rf $(NAME)

re: fclean all

lftclean:
	(cd $(LIBDIR); $(MAKE) clean)

lftfclean:
	(cd $(LIBDIR); $(MAKE) fclean)

.PHONY: $(NAME) all clean fclean re
