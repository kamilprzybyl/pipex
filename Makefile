FAGS = 	-Wall -Wextra -Werror
NAME = 	pipex
SRC = 	main.c \
		pipe.c \
		ft_split.c \
		ft_strjoin.c \
		ft_strlen.c \
		ft_substr.c \
		ft_strdup.c \
		ft_strlcpy.c \
		ft_strchr.c \
		ft_putstr_fd.c \
		ft_strncmp.c \
		ft_putendl_fd.c \
		pipe_utils.c
OBJ = 	$(SRC:.c=.o)

all: $(NAME)

$(NAME):
	gcc $(FLAGS) $(SRC) -o $@

clean:
	rm -fr $(OBJ)

fclean:
	make clean
	rm -fr $(NAME)

re: fclean all