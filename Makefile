NAME = philo

SRC = philo.c \
	  utils.c \
	  get_time.c \
	  thread.c \
	  living.c \
	  init.c

CFLAGS = -Wall -Wextra -Werror

CC = gcc

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) -o $(NAME)

debug : debug_clean
	gcc $(FLAGS) $(SRC) -g -o debug

clean : 
	rm -f $(OBJ)

debug_clean :
	rm -rf debug debug.dSYM

fclean : clean
	rm -f $(NAME)

re : fclean all
