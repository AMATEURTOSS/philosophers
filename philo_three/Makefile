NAME = philo_three
CC = clang
CFLAG = -Wall -Wextra -Werror -pthread -I.

SRC =	main.c \
		check.c \
		fork.c \
		init.c \
		utils.c \
		utils2.c

OBJ =	$(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAG) $(OBJ) -o $(NAME)

%.o: %.c
	@$(CC) $(CFLAG) -c $< -o $@

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all