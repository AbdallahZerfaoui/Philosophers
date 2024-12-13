EXE = philo
NBR_PHILO = 142

CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -g -pthread #-fsanitize=thread

SRC = main.c init.c philosopher.c \
	utils.c errors.c \
	memory_management.c basic.c maths.c \
	monitor.c logs.c \
	actions.c setters.c getters.c \
	
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

run_test: re
	./$(EXE) $(NBR_PHILO) 800 200 200

valgrind: re
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes  ./$(EXE) $(NBR_PHILO) 800 200 200 3

helgrind: re
	valgrind --tool=helgrind ./$(EXE) $(NBR_PHILO) 800 200 200 3 

drd: re
	valgrind --tool=drd ./$(EXE) $(NBR_PHILO) 800 200 200 3

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


.PHONY: all clean fclean re art art2 valgrind helgrind drd
