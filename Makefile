FAGS = 	-Wall -Wextra -Werror
NAME = 	pipex
SRC = 	src/main.c \
		src/pipe.c \
		src/utils/ft_split.c \
		src/utils/ft_strjoin.c \
		src/utils/ft_strlen.c \
		src/utils/ft_substr.c \
		src/utils/ft_strdup.c \
		src/utils/ft_strlcpy.c \
		src/utils/ft_strchr.c \
		src/utils/ft_putstr_fd.c \
		src/utils/ft_strncmp.c \
		src/utils/ft_putendl_fd.c
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