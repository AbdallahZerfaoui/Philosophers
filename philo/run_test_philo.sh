#!/usr/bin/env bash

# Colors
GREEN='\033[0;32m'
RED='\033[0;31m'
RESET='\033[0m'
TIME=3
MINIMUM_TIMESTAMP=2700

rm -f output_*.txt
make re; 
clear;
for i in $(seq 159 189); do
	echo "Testing with $i philosophers..."

	touch output_"$i".txt

	# Run philo in the background, output goes to output.txt
	./philo $i 800 200 200 > output_"$i".txt 2>&1 &
	pid=$!

	# Wait for 5 seconds
	sleep "$TIME"

	# Get the last line printed in output.txt
	last_line=$(tail -n 1 output_"$i".txt)

	# Extract the first field (timestamp) from the last line
	timestamp=$(echo "$last_line" | awk '{print $1}')

	# Check if timestamp is an integer and at least 4600
	if [ -n "$timestamp" ] && [ "$timestamp" -ge "$MINIMUM_TIMESTAMP" ] 2>/dev/null; then
		echo -e "${GREEN}Still working after "$TIME"s (timestamp: ${timestamp}ms).${RESET}"
		rm -f output_"$i".txt
	else
		echo -e "${RED}Not working after "$TIME"s (timestamp: ${timestamp}ms).${RESET}"
	fi

	# Kill the philo process if it's still running
	kill $pid 2>/dev/null
done
