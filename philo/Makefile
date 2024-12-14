EXE = philo
NBR_PHILO = 145
NBR_MEALS = 3

CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -g -pthread #-fsanitize=thread -Ofast

SRC = main.c init.c philosopher.c \
	utils.c utils2.c errors.c \
	memory_management.c basic.c \
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
	./$(EXE) $(NBR_PHILO) 800 200 200 $(NBR_MEALS)

valgrind: re
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes  ./$(EXE) $(NBR_PHILO) 800 200 200 $(NBR_MEALS)

helgrind: re
	valgrind --tool=helgrind ./$(EXE) $(NBR_PHILO) 800 200 200 $(NBR_MEALS) 

drd: re
	valgrind --tool=drd ./$(EXE) $(NBR_PHILO) 800 200 200 $(NBR_MEALS)

cppcheck: re
	cppcheck --enable=warning,style,performance,portability --enable=unusedFunction $(SRC)


help: art
	@echo "---------------------------------------------------------------"
	@echo "                   Philosophers project help					"
	@echo "---------------------------------------------------------------"
	@echo "Available make targets:"
	@echo "  all        - Compile the program."
	@echo "  clean      - Remove object files."
	@echo "  fclean     - Remove object files and the executable."
	@echo "  re         - Clean and recompile the program."
	@echo "  run_test   - Run the program with specified philosopher number."
	@echo "  valgrind   - Run Valgrind with memory leak detection."
	@echo "  helgrind   - Run Valgrind's Helgrind for thread race condition detection."
	@echo "  drd        - Run Valgrind's DRD for thread-related errors."
	@echo "  cppcheck   - Run cppcheck static analysis."
	@echo "  help       - Display this help message."

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

.PHONY: all clean fclean re art art2 valgrind helgrind drd help run_test cppcheck
