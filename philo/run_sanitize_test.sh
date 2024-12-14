#!/usr/bin/env bash

GREEN='\033[0;32m'
RED='\033[0;31m'
RESET='\033[0m'

# Recompile the program with -fsanitize=thread
# CFLAGS="-fsanitize=thread -g -O1"
# export CFLAGS
make re
clear

# Loop through a range of tests
for i in $(seq 150 156); do
    echo "Running ThreadSanitizer for test: ./philo $i 800 200 200 3"

    # Run the program and capture the output
    output=$(./philo $i 800 200 200 3 2>&1)
    echo "$output" > tsan_output_"$i".txt

    # Check if any ThreadSanitizer warnings are present
    error_summary=$(echo "$output" | grep -c "WARNING: ThreadSanitizer")

    # Display the result based on the error count
    if [[ "$error_summary" -eq 0 ]]; then
        echo -e "${GREEN}No ThreadSanitizer warnings for: ./philo $i 800 200 200 3${RESET}"
        rm -f tsan_output_"$i".txt
    else
        echo -e "${RED}$error_summary ThreadSanitizer warnings for: ./philo $i 800 200 200 3${RESET}"
    fi

    echo "-----------------------------------"
done
