EXE = philo

CC = cc -g -pthread
RM = rm -f
CFLAGS = -Wall -Wextra -Werror

SRC = main.c init.c philosopher.c \
	utils.c errors.c \
	memory_management.c basic.c maths.c \
	monitor.c starvation.c logs.c \
	actions.c
	
OBJ = $(SRC:.c=.o)

all: art $(EXE)

$(EXE): $(OBJ)
	$(CC) $(CFLAGS) -I. -o $(EXE) $(OBJ)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(EXE) *.out
	$(RM) -r *.dSYM

re: fclean all

valgrind: re
# valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes  ./$(EXE) 5 800 200 200 3
	valgrind --tool=helgrind ./$(EXE) 50 800 200 200 3 
# valgrind --tool=drd ./$(EXE) 50 800 200 200 3

art2:
	@echo " ____  _     _ _                       _                   ";
	@echo "|  _ \| |__ (_) | ___  ___  ___  _ __ | |__   ___ _ __ ___ ";
	@echo "| |_) | '_ \| | |/ _ \/ __|/ _ \| '_ \| '_ \ / _ \ '__/ __|";
	@echo "|  __/| | | | | | (_) \__ \ (_) | |_) | | | |  __/ |  \__ \\";
	@echo "|_|   |_| |_|_|_|\___/|___/\___/| .__/|_| |_|\___|_|  |___/";
	@echo "                                |_|         by The Greatest";


art:
	@echo "▗▄▄▖ ▗▖ ▗▖▗▄▄▄▖▗▖    ▗▄▖  ▗▄▄▖ ▗▄▖ ▗▄▄▖ ▗▖ ▗▖▗▄▄▄▖▗▄▄▖  ▗▄▄▖";
	@echo "▐▌ ▐▌▐▌ ▐▌  █  ▐▌   ▐▌ ▐▌▐▌   ▐▌ ▐▌▐▌ ▐▌▐▌ ▐▌▐▌   ▐▌ ▐▌▐▌   ";
	@echo "▐▛▀▘ ▐▛▀▜▌  █  ▐▌   ▐▌ ▐▌ ▝▀▚▖▐▌ ▐▌▐▛▀▘ ▐▛▀▜▌▐▛▀▀▘▐▛▀▚▖ ▝▀▚▖";
	@echo "▐▌   ▐▌ ▐▌▗▄█▄▖▐▙▄▄▖▝▚▄▞▘▗▄▄▞▘▝▚▄▞▘▐▌   ▐▌ ▐▌▐▙▄▄▖▐▌ ▐▌▗▄▄▞▘";
	@echo "                                             by The Greatest";


.PHONY: all clean fclean re art
