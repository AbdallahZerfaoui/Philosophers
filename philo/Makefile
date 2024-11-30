EXE = philo

CC = cc -g -pthread
RM = rm -f
CFLAGS = -Wall -Wextra -Werror

SRC = main.c init.c philosopher.c \
	utils.c simulation.c errors.c \
	memory_management.c basic.c logs.c
OBJ = $(SRC:.c=.o)

all: $(EXE)

$(EXE): $(OBJ)
	$(CC) $(CFLAGS) -I. -o $(EXE) $(OBJ)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(EXE) *.out
	$(RM) -r *.dSYM

re: fclean all
