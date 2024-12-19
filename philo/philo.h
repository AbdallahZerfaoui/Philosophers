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
# define MAGENTA	"\x1b[35m"
# define CYAN		"\x1b[36m"
# define RESET		"\x1b[0m"

# define MINIMUM_INPUTS 5
# define ALL_INPUTS 6
// # define SIMU_DURATION 5000
# define ACTION_STR_LEN 50
# define CHUNK_SIZE 200
# define MINI_TIME 10
# define FORK_TIME_OUT 1
# define DELAY_AFTER_CREATION 500 //in us
# define SCRIBE_TIME 50
# define LOCAL_LOG_SIZE 10
// # define GREEDINESS 30
# define TAKE 1
# define RELEASE -1
# define LOCK_ERROR 1
# define UNLOCK_ERROR 2


// Action description (e.g., "is eating")
typedef struct s_log
{
	long long			timestamp;
	int					philo_id;
	char				action[50];
	char 				color[16];
	struct s_log		*next;
}						t_log;

// typedef struct s_forks_data
// {
// 	int					left_fork;
// 	char				message_left[256];
// 	int					right_fork;
// 	char				message_right[256];
// }						t_forks_data;

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
	long long			last_meal_time; // when the meal started
	long long			meal_end_time;
	long long			wake_up_time;
	long long			log_buffer[LOCAL_LOG_SIZE];
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
	// pthread_mutex_t		start_time_mutex;
}						t_table;

typedef struct s_simulation
{
	t_table				*table;
	t_philosopher		*philosophers;
	// long long			start_simulation;
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

// Maths
int						ft_abs(int x);

// Monitor
void					monitoring_routine(t_monitoring_data *monitor_data);
int						get_nbr_chuncks(int num_philosophers);

// Errors
void					handle_missing_values(void);
void					handle_invalid_args(void);
void					*handle_allocation_failure(t_simulation *simulation,
							int level);
// Memory management
void					free_simulation(t_simulation *simulation);

// Utils
// void					log_action(t_simulation *simulation, int id,
// 							const char *action);
void					log_action(t_simulation *simulation, int philo_id,
							const char *action, char *color);
void					get_forks_ids(int philo_id, int *left_fork,
							int *right_fork, int num_philosophers);
void					sleep_ms(int ms);
void					sleep_till(long long target_time);
long long				current_time(void);
long long				current_time_us(void);
// int						custom_mutex_trylock(pthread_mutex_t *mutex);
// Utils - Simulation
int						alles_gut(t_simulation *simulation);
int						dinner_is_over(t_simulation *simulation);
int						is_simulation_over(t_simulation *simulation);
void					print_simu_status(t_simulation *simulation);
void					scribe_routine(t_simulation *simulation);
// Utils - Starvation
void					report_starvation(t_philosopher *philosopher);
int						check_starvation(t_philosopher *philosopher);
int						is_neighbor_starving(t_philosopher *philosopher);
void					wait_neighbor_to_eat(t_philosopher *philosopher);
// Utils - Philosophers
void					report_death(t_philosopher *philosopher);
int						is_alive(const t_simulation *simulation, \
		const t_philo_shared_data *data);
int						im_alive(const t_philosopher *philosopher);
void					handle_greediness(t_philosopher philosopher);

// Utils - mutex
int						lock_safely(pthread_mutex_t *mutex);
int						unlock_safely(pthread_mutex_t *mutex);

// Actions
void					think(t_philosopher *philosopher);
void					take_forks(t_philosopher *philosopher, int side);
int						take_fork_time_out(t_fork *fork, int philo_id);
void					eat(t_philosopher *philosopher);
void					get_a_nap(t_philosopher *philosopher);
void					unlock_my_forks(t_philosopher *philosopher);

// Initialization
t_simulation			*parse_inputs(char **argv);
void					destroy_mutexes(t_simulation *simulation);

// Philosophers
void					*philosopher_routine(t_philosopher *philosopher);

// Basic
void					*ft_calloc(size_t nitems, size_t size);
int						ft_atoi(const char *str);
char					*ft_strdup(const char *s);
size_t					ft_strlen(const char *s);
ssize_t					ft_putstr(char *str);
void					ft_putnbr(long long n);
void					ft_strcpy(char *dst, const char *src);

// Logs
t_log					*create_log(long long timestamp, int philo_id,
							const char *action, char *color);
t_log					*insert_after(t_log *lst, t_log *target, t_log *log);
t_log					*add_log(t_log *log_lst, t_log *log);
// void					print_logs(t_log *log_lst);
void					print_logs(t_simulation *simulation);
void					print_logs_before(t_simulation *simulation, long long limit);
int						log_size(t_log *lst);
void					free_log(t_log *log);

// Setters
void					set_last_time_meal(t_philosopher *philosopher);
// int						set_fork_owner(t_philosopher *philosopher, int fork_id, int action);
void					set_fork_owner(int *fork, int fork_id, int action);
void					set_start_time(t_simulation *simulation);
void					set_eaten_meals(t_philosopher *philosopher, int increment);
void					set_wake_up_time(t_philosopher *philosopher);
void					set_meal_end_time(t_philosopher *philosopher);
void					set_someone_died(t_philosopher *philosopher);
void					set_philo_times(t_philosopher *philosopher);

// Getters
long long				get_last_time_meal(t_philosopher *philosopher);
long long				get_meal_end_time(const t_philosopher *philosopher);
long long				get_wake_up_time(const t_philosopher *philosopher);
long long				get_start_time(t_simulation *simulation);
t_log					*get_log_lst(t_simulation *simulation);
int						get_times_eaten(t_philosopher *philosopher);
int						get_someone_died(t_simulation *simulation);
void					get_philo_data(t_philosopher *philosopher,
							t_philo_shared_data *data);
// t_philo_shared_data		*get_philo_data(t_philosopher *philosopher);

#endif
