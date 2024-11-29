# Philosophers

### **Step-by-Step Guide for the Dining Philosophers Project**

This tutorial will guide you through both the **mandatory** and **bonus** parts of the Dining Philosophers project in a structured way, ensuring the mandatory implementation is designed to easily extend into the bonus part.

---

## **1. Understand the Project Requirements**

### **Mandatory Part:**
- Use **threads** for philosophers.
- Use **mutexes** to protect shared resources (forks).
- Each philosopher must:
  1. Take forks (both left and right).
  2. Eat.
  3. Release forks.
  4. Sleep.
  5. Think.
- Simulation ends when:
  - A philosopher dies (fails to eat within `time_to_die` milliseconds).
  - Optional: All philosophers eat at least `number_of_times_each_philosopher_must_eat`.

### **Bonus Part:**
- Use **processes** for philosophers.
- Use **semaphores** for fork availability instead of mutexes.
- Forks are represented as a shared count tracked by a semaphore.

---

## **2. Design the Program**
Structure your code to accommodate both the mandatory and bonus requirements:
- Separate **logic** (philosopher actions) from **implementation** (threads vs. processes).
- Use abstraction for shared resources (forks).
- Centralize simulation control for easy debugging and extensions.

---

### **3. Step-by-Step Implementation**

### **Step 3.1: Setup the Project Directory**
1. Create the project directories:
   ```bash
   mkdir philo philo_bonus
   cd philo
   touch Makefile *.c *.h
   ```

2. Write your **Makefile**:
   ```Makefile
   NAME = philo

   CC = cc
   CFLAGS = -Wall -Wextra -Werror

   SRC = main.c init.c philosopher.c utils.c
   OBJ = $(SRC:.c=.o)

   all: $(NAME)

   $(NAME): $(OBJ)
       $(CC) $(CFLAGS) -o $(NAME) $(OBJ)

   clean:
       rm -f $(OBJ)

   fclean: clean
       rm -f $(NAME)

   re: fclean all
   ```

---

### **Step 3.2: Global Header File**
Create `philo.h` to store shared structures, constants, and function prototypes:
```c
#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_fork {
    pthread_mutex_t mutex;
}               t_fork;

typedef struct s_philosopher {
    int             id;
    int             times_eaten;
    long long       last_meal_time;
    struct s_table  *table;
}               t_philosopher;

typedef struct s_table {
    int             num_philosophers;
    int             time_to_die;
    int             time_to_eat;
    int             time_to_sleep;
    int             must_eat_count;
    t_fork          *forks;
    t_philosopher   *philosophers;
    pthread_t       *threads;
    long long       start_time;
}               t_table;

// Utils
long long   current_time(void);
void        sleep_ms(int ms);
void        print_action(t_table *table, int id, const char *action);

#endif
```

---

### **Step 3.3: Implement Utility Functions**
Add utilities for time management, printing, and sleeping:
```c
#include "philo.h"

long long current_time(void) {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000LL + tv.tv_usec / 1000LL);
}

void sleep_ms(int ms) {
    long long start = current_time();
    while (current_time() - start < ms)
        usleep(100);
}

void print_action(t_table *table, int id, const char *action) {
    printf("%lld %d %s\n", current_time() - table->start_time, id, action);
}
```

---

### **Step 3.4: Initialize Data**
Set up the table, forks, and philosophers:
```c
#include "philo.h"

int init_table(t_table *table, int argc, char **argv) {
    table->num_philosophers = atoi(argv[1]);
    table->time_to_die = atoi(argv[2]);
    table->time_to_eat = atoi(argv[3]);
    table->time_to_sleep = atoi(argv[4]);
    table->must_eat_count = (argc == 6) ? atoi(argv[5]) : -1;
    table->forks = malloc(sizeof(t_fork) * table->num_philosophers);
    table->philosophers = malloc(sizeof(t_philosopher) * table->num_philosophers);
    table->threads = malloc(sizeof(pthread_t) * table->num_philosophers);
    if (!table->forks || !table->philosophers || !table->threads)
        return (1);
    for (int i = 0; i < table->num_philosophers; i++)
        pthread_mutex_init(&table->forks[i].mutex, NULL);
    table->start_time = current_time();
    return (0);
}
```

---

### **Step 3.5: Philosopher Actions**
Write the main loop for each philosopher:
```c
#include "philo.h"

void *philosopher_routine(void *arg) {
    t_philosopher *philo = (t_philosopher *)arg;
    t_table *table = philo->table;

    while (1) {
        // Take forks
        pthread_mutex_lock(&table->forks[philo->id].mutex);
        print_action(table, philo->id, "has taken a fork");
        pthread_mutex_lock(&table->forks[(philo->id + 1) % table->num_philosophers].mutex);
        print_action(table, philo->id, "has taken a fork");
        
        // Eat
        print_action(table, philo->id, "is eating");
        philo->last_meal_time = current_time();
        sleep_ms(table->time_to_eat);
        pthread_mutex_unlock(&table->forks[philo->id].mutex);
        pthread_mutex_unlock(&table->forks[(philo->id + 1) % table->num_philosophers].mutex);

        // Sleep
        print_action(table, philo->id, "is sleeping");
        sleep_ms(table->time_to_sleep);

        // Think
        print_action(table, philo->id, "is thinking");
    }
    return (NULL);
}
```

---

### **Step 3.6: Launch Threads**
Write the main simulation:
```c
#include "philo.h"

int main(int argc, char **argv) {
    t_table table;

    if (argc < 5 || argc > 6) {
        printf("Usage: ./philo num_philosophers time_to_die time_to_eat time_to_sleep [must_eat_count]\n");
        return (1);
    }
    if (init_table(&table, argc, argv))
        return (1);

    for (int i = 0; i < table.num_philosophers; i++) {
        table.philosophers[i].id = i;
        table.philosophers[i].last_meal_time = table.start_time;
        table.philosophers[i].table = &table;
        pthread_create(&table.threads[i], NULL, philosopher_routine, &table.philosophers[i]);
    }
    for (int i = 0; i < table.num_philosophers; i++)
        pthread_join(table.threads[i], NULL);

    return (0);
}
```

---

### **Step 3.7: Extend for Bonus**
In the bonus version:
- Replace threads with **processes** (`fork()`).
- Replace mutexes with **semaphores** (`sem_open`, `sem_wait`, `sem_post`).
- Add process synchronization using a shared semaphore for forks.

---

This design ensures the mandatory part is robust and easily extensible to the bonus part. Let me know if you'd like the detailed bonus implementation or need help debugging!
