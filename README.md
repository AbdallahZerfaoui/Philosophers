# Philosophers Project: A Beginner's Guide

This guide breaks down the key steps involved in the Philosophers project. The goal is to simulate the classic "Dining Philosophers" computer science problem, focusing on concurrency, resource sharing, and avoiding issues like deadlock and starvation.

## 1. Understanding the Problem

*   **Scenario:** Imagine several philosophers sitting around a circular table. Between each pair of adjacent philosophers lies a single fork.
*   **Goal:** Philosophers alternate between thinking, getting hungry, eating, and sleeping.
*   **Challenge:** To eat, a philosopher needs *two* forks – the one on their left and the one on their right. They must pick up both forks without causing a situation where no one can eat (deadlock) or where a specific philosopher never gets a chance to eat (starvation).

## 2. Setting Up the Simulation

*   **Parsing Input (`philo/parse.c`, `main.c`):**
    *   The program starts by reading command-line arguments:
        *   Number of philosophers
        *   Time to die (ms): Max time a philosopher can go without eating.
        *   Time to eat (ms): Duration of eating.
        *   Time to sleep (ms): Duration of sleeping.
        *   (Optional) Number of times each philosopher must eat.
    *   Functions like `parse_arguments`, `check_limits`, `ft_atoi`, and `ft_isnumber` handle reading and validating this input. Invalid input leads to errors handled in `philo/errors.c`.
*   **Allocating Memory (`philo/allocate.c`, `philo/memory_management.c`):**
    *   Memory is needed to store information about the simulation (`t_simulation`), the table (`t_table`), each philosopher (`t_philosopher`), and each fork (`t_fork`). These structures are defined in `philo/philo.h`.
    *   Functions like `allocate_simulation`, `allocate_forks`, `allocate_philosophers`, and `ft_calloc` reserve the necessary memory.
*   **Initialization (`philo/allocate.c`, `philo/parse.c`):**
    *   Each philosopher and fork is initialized with its ID and default state.
    *   **Crucially:** A **mutex** (`pthread_mutex_t`) is created for each fork (`init_forks`) and each philosopher (`init_philosophers`). Mutexes act like locks to protect shared resources (like forks or philosopher data) from being accessed by multiple threads simultaneously.
    *   Global mutexes (e.g., for logging `log_mutex`, checking death `death_mutex`) are also initialized in `setup_simulation`.

## 3. The Philosopher's Life (`philo/philosopher.c`, `philo/actions.c`)

*   **Threads:** Each philosopher runs concurrently in its own thread, executing the `philosopher_routine` function.
*   **The Cycle:** Inside the loop (`while (!is_simulation_over(...))`), a philosopher performs actions:
    *   **Think (`think`):** Logs the thinking status.
    *   **Take Forks (`take_forks`, `philo/action_utils.c`):**
        *   Attempts to acquire the mutexes for both the left and right forks using `try_take_fork` which calls `lock_safely` (`philo/utils2.c`).
        *   To prevent **deadlock**, philosophers might pick up forks in a specific order (e.g., even/odd IDs pick up left/right first, or lower ID fork first). The `side` variable and potential `usleep(DELAY_AFTER_CREATION)` help stagger attempts.
        *   The philosopher's `left_fork` and `right_fork` variables track which forks they hold.
    *   **Eat (`eat`):**
        *   If successful in getting both forks:
            *   Logs "is eating".
            *   Updates their `last_meal_time` and calculates `meal_end_time` and `wake_up_time` (`set_philo_times` in `philo/setters.c`).
            *   Simulates eating using `sleep_till` (`philo/time.c`).
            *   Releases the forks using `release_fork` (which calls `unlock_safely`).
            *   Increments their meal count (`set_eaten_meals`).
    *   **Sleep (`get_a_nap`):**
        *   Logs "is sleeping".
        *   Simulates sleeping using `sleep_till`.
*   **Checking Status:** Philosophers constantly check if the simulation has ended (`is_simulation_over` in `philo/utils.c`) or if they are still alive (`im_alive` in `philo/death.c`).

## 4. Monitoring for Problems (`philo/monitor.c`, `philo/death.c`)

*   **Monitor Thread(s):** One or more separate threads run the `monitoring_routine`. Using multiple monitors (`get_nbr_chuncks` in `philo/utils2.c`) can improve efficiency for large numbers of philosophers.
*   **Health Checks:**
    *   The monitor periodically checks each philosopher it's responsible for.
    *   It safely reads the philosopher's `last_meal_time` and `times_eaten` using `get_philo_data` (`philo/getters.c`), which locks the philosopher's specific mutex.
*   **Detecting Death:**
    *   Calculates time since the last meal (`current_time_us` in `philo/time.c`).
    *   If this exceeds `time_to_die` (`is_alive` in `philo/death.c`), it calls `report_death`, which sets a global `someone_died` flag (protected by `death_mutex` via `set_someone_died`) and logs the death.
*   **Checking Meal Count:** The monitor also checks if all philosophers have completed their required meals using `dinner_is_over` (`philo/utils.c`).

## 5. Logging Actions (`philo/scribe.c`, `philo/logs.c`)

*   **The Scribe Thread:** A dedicated thread runs `scribe_routine`. Its purpose is to print status messages from all philosophers in the correct chronological order.
*   **Recording:** When a philosopher acts, `log_action` (`philo/utils.c`) creates a log entry (`t_log`) with the timestamp, philosopher ID, and message.
*   **Storing:** These logs are added to a shared linked list (`log_lst` in `t_simulation`), sorted by timestamp. Access is protected by `log_mutex` (`add_log`).
*   **Printing:** The scribe periodically wakes up (`sleep_ms`), locks the `log_mutex`, prints logs that occurred sufficiently in the past (`print_logs`, `display_log`), removes them from the list, and unlocks the mutex. This ensures output isn't jumbled due to thread concurrency.

## 6. Running and Ending the Simulation (`philo/simulation.c`)

*   **Orchestration:** The `run_simulation` function manages the overall process.
*   **Thread Creation:** It uses `pthread_create` to start all philosopher threads, monitor thread(s), and the scribe thread.
*   **Waiting:** It uses `pthread_join` to wait for all threads to complete. Philosophers finish when the simulation ends (death or meals completed). Monitors and the scribe finish when they detect the simulation end condition.

## 7. Cleaning Up (`philo/memory_management.c`, `philo/parse.c`)

*   **Resource Release:** After the simulation ends (`main.c`), it's crucial to clean up:
    *   `destroy_mutexes`: Destroys all initialized mutexes.
    *   `free_simulation`: Frees all dynamically allocated memory (for philosophers, forks, table, logs, etc.) to prevent memory leaks.

## 8. Building the Project (`philo/Makefile`)

*   The `Makefile` provides commands to compile the source code (`.c` files) into an executable program (`philo`).
*   Common commands:
    *   `make`: Compiles the project.
    *   `make clean`: Removes intermediate object files (`.o`).
    *   `make fclean`: Removes object files and the executable.
    *   `make re`: Recompiles everything cleanly.
    *   `make run_test`, `make valgrind`, `make helgrind`: Useful targets for running tests and checking for memory or threading errors.

## Key Concepts Recap

*   **Threads:** Allow philosophers (and monitors/scribe) to run concurrently.
*   **Mutexes:** Essential locks to protect shared data (forks, philosopher state, logs) from race conditions, ensuring data integrity.
*   **Deadlock:** A state where threads are blocked forever, waiting for resources held by each other. Prevented by careful resource acquisition strategies (e.g., fork ordering).
*   **Starvation:** A state where a thread is perpetually denied access to necessary resources and cannot make progress. Monitored by checking `time_to_die`.
