#!/usr/bin/env bash

GREEN='\033[0;32m'
RED='\033[0;31m'
RESET='\033[0m'
FLAG=helgrind #drd helgrind

rm -f helgrind_output_*.txt
make re; clear
# Loop through a range of tests
for i in $(seq 2 20); do
    echo "Running Helgrind for test: ./philo $i 800 200 200 3"

    # Run Helgrind and capture the output
	output=$(valgrind --tool="$FLAG" ./philo $i 800 200 200 3 2>&1)
	echo "$output" > helgrind_output_"$i".txt

    # Extract the error summary using grep and awk
    error_summary=$(echo "$output" | grep "ERROR SUMMARY:" | awk '{print $4}')

    # Display the result based on the error count
    if [[ "$error_summary" -eq 0 ]]; then
        echo -e "${GREEN}No errors detected for: ./philo $i 800 200 200 3${RESET}"
		rm -f helgrind_output_"$i".txt
    else
        echo -e "${RED}$error_summary errors detected for: ./philo $i 800 200 200 3${RESET}"
    fi

    echo "-----------------------------------"
done
