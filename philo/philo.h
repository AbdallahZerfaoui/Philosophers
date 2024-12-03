/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 14:58:47 by azerfaou          #+#    #+#             */
/*   Updated: 2024/12/03 20:04:27 by azerfaou         ###   ########.fr       */
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

# define MINIMUM_INPUTS 5
# define ALL_INPUTS 6
# define SIMU_DURATION 5000
# define ACTION_STR_LEN 50
# define MINI_TIME 10
# define GREEDINESS 10

// Action description (e.g., "is eating")
typedef struct s_log
{
	long long			timestamp;
	int					philo_id;
	char				*action;
	struct s_log		*next;
}						t_log;

typedef struct s_forks_data
{
	int					left_fork;
	char				message_left[256];
	int					right_fork;
	char				message_right[256];
}						t_forks_data;

typedef struct s_fork
{
	int					id;
	pthread_mutex_t		fork_mutex;
}						t_fork;

typedef struct s_philosopher
{
	int					id;
	int					times_eaten;
	int					mini_nbr_meals;
	long long			last_meal_time;
	pthread_t			thread;
	struct s_simulation	*simulation;
}						t_philosopher;

typedef struct s_table
{
	int					num_philosophers;
	long long			time_to_die;
	long long			time_to_eat;
	long long			time_to_sleep;
	t_fork				*forks;
	int					nbr_forks;
	pthread_mutex_t		nbr_forks_mutex;
	t_philosopher		*philosophers;
	long long			start_time;
}						t_table;

typedef struct s_simulation
{
	t_table				*table;
	t_philosopher		*philosophers;
	pthread_t			monitor;
	int					someone_died;
	int					someone_starving;
	pthread_mutex_t		starvation_mutex;
	pthread_cond_t		starvation_done;
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		death_mutex;
}						t_simulation;

// Maths
int						ft_abs(int x);

// Monitor
void					monitoring_routine(t_simulation *simulation);

// Errors
void					handle_missing_values(void);

// Memory management
void					free_simulation(t_simulation *simulation);

// Utils
void					print_action(t_simulation *simulation, int id,
							const char *action);
void					log_action(t_simulation *simulation, int philo_id,
							const char *action);
void					get_forks_ids(int philo_id, int *left_fork,
							int *right_fork, int num_philosophers);
void					sleep_ms(int ms);
long long				current_time(void);
// Utils - Simulation
int						alles_gut(t_simulation *simulation);
int						dinner_is_over(t_simulation *simulation);
int						is_simulation_over(t_simulation *simulation);
void					print_simu_status(t_simulation *simulation);
// Utils - Starvation
void					report_starvation(t_philosopher *philosopher);
int						check_starvation(t_philosopher *philosopher);
// Utils - Philosophers
void					report_death(t_philosopher *philosopher);
int						is_alive(t_philosopher *philosopher);
void					handle_greediness(t_philosopher philosopher);

// Initialization
t_simulation			*parse_inputs(char **argv);
void					destroy_mutexes(t_simulation *simulation);

// Philosophers
void					*philosopher_routine(t_philosopher *philosopher);

// Basic
void					*ft_calloc(size_t nitems, size_t size);
int						ft_atoi(const char *str);
char					*ft_strdup(const char *s);

// Logs
t_log					*create_log(long long timestamp, int philo_id,
							const char *action);
t_log					*insert_after(t_log *lst, t_log *target, t_log *log);
t_log					*add_log(t_log *log_lst, t_log *log);
void					print_logs(t_log *log_lst);
int						log_size(t_log *lst);

#endif
