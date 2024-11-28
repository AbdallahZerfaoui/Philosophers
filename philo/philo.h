/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 14:58:47 by azerfaou          #+#    #+#             */
/*   Updated: 2024/11/28 16:17:22 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>

# define MINIMUM_INPUTS 5
# define ALL_INPUTS 6

typedef struct s_fork
{
	pthread_mutex_t	mutex;
}					t_fork;

typedef struct s_philosopher
{
	int				id;
	int				times_eaten;
	int				mini_nbr_meals;
	long long		last_meal_time;
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
	pthread_t		*threads;
	long long		start_time;
}					t_table;

typedef struct s_simulation
{
	t_table			*table;
	t_philosopher	*philosophers;
}					t_simulation;

// Errors
void	handle_missing_values(void);

// Initialization
t_simulation	*parse_inputs(char **argv);

// Basic
void	*ft_calloc(size_t nitems, size_t size);
int		ft_atoi(const char *str);

#endif
