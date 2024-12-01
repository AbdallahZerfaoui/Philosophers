/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 14:58:47 by azerfaou          #+#    #+#             */
/*   Updated: 2024/12/01 13:24:54 by azerfaou         ###   ########.fr       */
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
# define TIME_TO_THINK 250
# define SIMU_DURATION 2000
# define ACTION_STR_LEN 50

// Action description (e.g., "is eating")
typedef struct s_log
{
	long long			timestamp;
	int					philo_id;
	char				*action;
	struct s_log		*next;
}						t_log;

typedef struct s_fork
{
	int					id;
	pthread_mutex_t		mutex;
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
	t_philosopher		*philosophers;
	long long			start_time;
}						t_table;

typedef struct s_simulation
{
	t_table				*table;
	t_philosopher		*philosophers;
	t_log				*log_lst;
	pthread_mutex_t		log_mutex;
}						t_simulation;

// Errors
void					handle_missing_values(void);

// Memory management
void					free_simulation(t_simulation *simulation);

// Utils
void					print_action(t_table *table, int id,
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
