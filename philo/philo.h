/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 14:58:47 by azerfaou          #+#    #+#             */
/*   Updated: 2024/11/29 18:34:45 by azerfaou         ###   ########.fr       */
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

typedef struct s_fork
{
	int				id;
	pthread_mutex_t	mutex;
}					t_fork;

typedef struct s_philosopher
{
	int				id;
	int				times_eaten;
	int				mini_nbr_meals;
	long long		last_meal_time;
	pthread_t		thread;
	struct s_table	*table;
}					t_philosopher;

typedef struct s_table
{
	int				num_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	t_fork			*forks;
	t_philosopher	*philosophers;
	long long		start_time;
}					t_table;

typedef struct s_simulation
{
	t_table			*table;
	t_philosopher	*philosophers;
}					t_simulation;

// Errors
void				handle_missing_values(void);

// Utils
void				print_action(t_table *table, int id, const char *action);
void				get_forks_ids(int philo_id, int *left_fork, int *right_fork,
						int num_philosophers);
void				sleep_ms(int ms);
long long			current_time(void);

// Initialization
t_simulation		*parse_inputs(char **argv);

// Basic
void				*ft_calloc(size_t nitems, size_t size);
int					ft_atoi(const char *str);

#endif
