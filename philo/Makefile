EXE = philo

CC = cc -g
RM = rm -f
CFLAGS = -Wall -Wextra -Werror

SRC = main.c init.c philosopher.c utils.c simulation.c errors.c memory_management.c
OBJ = $(SRC:.c=.o)

all: $(EXE)

$(EXE): $(OBJ)
	$(CC) $(CFLAGS) -I. -o $(EXE) $(OBJ)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(EXE)

re: fclean all
