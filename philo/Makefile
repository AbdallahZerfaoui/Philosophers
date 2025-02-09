# define standard colors
ifneq (,$(findstring xterm,${TERM}))
	BLACK        := $(shell tput -Txterm setaf 0)
	RED          := $(shell tput -Txterm setaf 1)
	GREEN        := $(shell tput -Txterm setaf 2)
	YELLOW       := $(shell tput -Txterm setaf 3)
	LIGHTPURPLE  := $(shell tput -Txterm setaf 4)
	PURPLE       := $(shell tput -Txterm setaf 5)
	BLUE         := $(shell tput -Txterm setaf 6)
	WHITE        := $(shell tput -Txterm setaf 7)
	RESET := $(shell tput -Txterm sgr0)
else
	BLACK        := ""
	RED          := ""
	GREEN        := ""
	YELLOW       := ""
	LIGHTPURPLE  := ""
	PURPLE       := ""
	BLUE         := ""
	WHITE        := ""
	RESET        := ""
endif

### ================================================================================ ###

EXE = philo
NBR_PHILO = 200
NBR_MEALS = 3

CC = gcc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -g -pthread #-fsanitize=thread -Ofast

SRC = main.c parse.c philosopher.c \
	utils.c utils2.c errors.c \
	memory_management.c allocate.c basic.c \
	monitor.c logs.c scribe.c \
	actions.c action_utils.c setters.c getters.c \
	simulation.c time.c death.c
	
OBJ = $(SRC:.c=.o)

all: art3 $(EXE)
	@echo "\033[31m	------------------***༺ (\033[31m\033[32mPhilosophers Compiled!\033[31m)༻***------------------\n\033[0m"

$(EXE): $(OBJ)
	$(CC) $(CFLAGS) -I. -o $(EXE) $(OBJ)

clean:
	@$(RM) $(OBJ)

fclean: clean
	@$(RM) $(EXE) *.out
	@$(RM) -r *.dSYM

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

art:
	@echo " ____  _     _ _                       _                   ";
	@echo "|  _ \| |__ (_) | ___  ___  ___  _ __ | |__   ___ _ __ ___ ";
	@echo "| |_) | '_ \| | |/ _ \/ __|/ _ \| '_ \| '_ \ / _ \ '__/ __|";
	@echo "|  __/| | | | | | (_) \__ \ (_) | |_) | | | |  __/ |  \__ \\";
	@echo "|_|   |_| |_|_|_|\___/|___/\___/| .__/|_| |_|\___|_|  |___/";
	@echo "                                |_|         by The Greatest";

art2:
	@echo "▗▄▄▖ ▗▖ ▗▖▗▄▄▄▖▗▖    ▗▄▖  ▗▄▄▖ ▗▄▖ ▗▄▄▖ ▗▖ ▗▖▗▄▄▄▖▗▄▄▖  ▗▄▄▖";
	@echo "▐▌ ▐▌▐▌ ▐▌  █  ▐▌   ▐▌ ▐▌▐▌   ▐▌ ▐▌▐▌ ▐▌▐▌ ▐▌▐▌   ▐▌ ▐▌▐▌   ";
	@echo "▐▛▀▘ ▐▛▀▜▌  █  ▐▌   ▐▌ ▐▌ ▝▀▚▖▐▌ ▐▌▐▛▀▘ ▐▛▀▜▌▐▛▀▀▘▐▛▀▚▖ ▝▀▚▖";
	@echo "▐▌   ▐▌ ▐▌▗▄█▄▖▐▙▄▄▖▝▚▄▞▘▗▄▄▞▘▝▚▄▞▘▐▌   ▐▌ ▐▌▐▙▄▄▖▐▌ ▐▌▗▄▄▞▘";
	@echo "                                             by The Greatest";

art3:
	@echo "${GREEN}                                                                                               #                           ";
	@echo "   ## #        #                  ##  ##       #       ##  ##             ## ##       ##       #                    #  #   ";
	@echo "        #                         #   ##               ##  #                            ####   #         ###               ";
	@echo "       ##    #####             #  #   ##     #####     ##  #                          ### ##   #        ######         #   ${RESET}";
	@echo "    #####   ##   ##     #  ## ##  #   ##     #   ##    ##  #                    ##    ######   #      ##  #   ##       #   ";
	@echo "   #   ##    #  ##      #  ##  #  ##  ##     #  ##     ##  #          .#         #        ##   #      #   #    #       #   ";
	@echo "${RED}   #############################   ######################  #        ########################   #########################   ";
	@echo "                                   ####                                                               ##  #                ";
	@echo "                                   #. ##                              by The Greatest                   +##                ";
	@echo "                                     #                                                                                     ${RESET}";
	@echo "                                                                                                            ";


   ## #        #                  ##  ##       #       ##  ##   
        #                         #   ##               ##  #    
       ##    #####             #  #   ##     #####     ##  #    
    #####   ##   ##     #  ## ##  #   ##     #   ##    ##  #    
   #   ##    #  ##      #  ##  #  ##  ##     #  ##     ##  #    
   #############################   ######################  #    
                                   ####                         
                                   #. ##                        
                                     #                          


.PHONY: all clean fclean re art art2 art3 valgrind helgrind drd help run_test cppcheck
