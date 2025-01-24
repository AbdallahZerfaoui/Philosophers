/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 14:58:47 by azerfaou          #+#    #+#             */
/*   Updated: 2024/12/05 20:51:39 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdint.h>
# include <time.h>

# define RED		"\x1b[31m"
# define GREEN		"\x1b[32m"
# define YELLOW		"\x1b[33m"
# define BLUE		"\x1b[34m"
# define CYAN		"\x1b[36m"
# define RESET		"\x1b[0m"

# define MINIMUM_INPUTS 5
# define MAXIMUM_PHILOS 200
# define ACTION_STR_LEN 50
# define CHUNK_SIZE 20 //DONT CHANGE
# define DELAY_AFTER_CREATION 300 //in us
# define SCRIBE_SLEEP_TIME 59
# define SCRIBE_TIME_GAP 67 // gap between log and now - youssef constant
# define INT_MAX_DIGITS 10
# define MONITOR_SLEEP 100 // in us
# define TAKE 1
# define RELEASE -1
# define LOCK_ERROR 1
# define UNLOCK_ERROR 2

typedef struct s_log
{
	long long			timestamp;
	int					philo_id;
	char				action[50];
	char				color[16];
	int					status;
	struct s_log		*next;
}						t_log;

typedef struct s_fork
{
	int					id;
	pthread_mutex_t		fork_mutex;
}						t_fork;

typedef struct s_philosopher
{
	int					id;
	pthread_mutex_t		philo_mutex;
	int					mini_nbr_meals;
	pthread_t			thread;
	int					times_eaten;
	int					ready_to_eat;
	long long			last_meal_time;
	long long			meal_end_time;
	long long			wake_up_time;
	int					left_fork;
	int					right_fork;
	int					is_eating;
	struct s_simulation	*simulation;
}						t_philosopher;

typedef struct s_philo_shared_data
{
	int					times_eaten;
	long long			last_meal_time;
}						t_philo_shared_data;

typedef struct s_table
{
	int					num_philosophers;
	long long			time_to_die;
	long long			time_to_sleep;
	long long			time_to_eat;
	t_fork				*forks;
	t_philosopher		*philosophers;
	long long			start_time;
}						t_table;

typedef struct s_simulation
{
	t_table				*table;
	t_philosopher		*philosophers;
	t_log				*log_lst;
	pthread_t			*monitors;
	pthread_t			scribe;
	int					someone_died;
	pthread_mutex_t		death_mutex;
	pthread_mutex_t		log_mutex;
}						t_simulation;

typedef struct s_monitoring_data
{
	int					id;
	int					nbr_monitors;
	t_simulation		*simulation;
}						t_monitoring_data;

// Monitor
void					monitoring_routine(t_monitoring_data *monitor_data);
int						get_nbr_chuncks(int num_philosophers);

// Errors
void					handle_inadequate_args(void);
void					handle_invalid_args(void);
void					*handle_allocation_failure(t_simulation *simulation,
							int level);
// Memory management
void					free_simulation(t_simulation *simulation);
void					*ft_calloc(size_t nitems, size_t size);

// Utils
void					log_action(t_simulation *simulation, int philo_id,
							const char *action, const char *color);
void					get_forks_ids(int philo_id, int *left_fork,
							int *right_fork, int num_philosophers);
// Utils - Simulation
int						dinner_is_over(t_simulation *simulation);
int						is_simulation_over(t_simulation *simulation);
// Utils - Philosophers
void					report_death(t_philosopher *philosopher);
int						is_alive(const t_simulation *simulation, \
							const t_philo_shared_data *data);
int						im_alive(const t_philosopher *philosopher);

// Utils - mutex
int						lock_safely(pthread_mutex_t *mutex);
int						unlock_safely(pthread_mutex_t *mutex);

// Utils - time
long long				current_time_us(void);
long long				current_time(void);
void					sleep_ms(int ms);
void					sleep_till(long long target_time);

// Actions
void					think(t_philosopher *philosopher);
void					take_forks(t_philosopher *philosopher, int side);
void					eat(t_philosopher *philosopher);
void					get_a_nap(t_philosopher *philosopher);
void					unlock_my_forks(t_philosopher *philosopher);
// Actions - utils	
void					try_take_fork(t_philosopher *philosopher,
							int fork_id, int *fork);
void					release_fork(t_philosopher *philosopher,
							int fork_id, int *fork);
void					handle_single_philosopher(const t_table *table);

// Initialization
t_simulation			*setup_simulation(char **argv);
void					destroy_mutexes(t_simulation *simulation);

// Allocate
t_simulation			*allocate_simulation(void);
int						allocate_forks(t_simulation *simulation);
int						allocate_philosophers(t_simulation *simulation,
							int mini_nbr_meals);

// Philosophers
void					philosopher_routine(t_philosopher *philosopher);

// Scribe
void					scribe_routine(t_simulation *simulation);

// Basic
int						ft_atoi(const char *str);
size_t					ft_strlen(const char *s);
void					ft_strcpy(char *dst, const char *src);
void					swap(int *a, int *b);
int						ft_strncmp(const char *s1, const char *s2, size_t n);

// Logs
t_log					*create_log(long long timestamp, int philo_id,
							const char *action, const char *color);
t_log					*insert_after(t_log *lst, t_log *target, t_log *log);
t_log					*add_log(t_log *log_lst, t_log *log);
int						print_logs(t_simulation *simulation, long long delay);
void					free_log_lst(t_log *log_lst);
int						display_log(const t_log *log, const char *color);

// Setters
void					set_last_time_meal(t_philosopher *philosopher);
void					set_fork_owner(int *fork, int fork_id, int action);
void					set_eaten_meals(t_philosopher *philosopher,
							int increment);
void					set_someone_died(t_philosopher *philosopher);
void					set_philo_times(t_philosopher *philosopher);

// Getters
long long				get_start_time(t_simulation *simulation);
int						get_times_eaten(t_philosopher *philosopher);
int						get_someone_died(t_simulation *simulation);
void					get_philo_data(t_philosopher *philosopher,
							t_philo_shared_data *data);
// Simulation
void					run_simulation(t_simulation *simulation);

#endif
