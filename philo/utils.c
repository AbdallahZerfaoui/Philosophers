/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 11:39:33 by azerfaou          #+#    #+#             */
/*   Updated: 2024/11/30 21:56:04 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000LL + tv.tv_usec);
}

void	sleep_ms(int ms)
{
	long long	start;

	start = current_time();
	if (current_time() - start < ms)
		usleep(ms - (current_time() - start));
}

void	print_action(t_table *table, int philo_id, const char *action)
{
	printf("%lld - philo : %d - %s\n",
		current_time() - table->start_time, philo_id, action);
}

void	log_action(t_simulation *simulation, int philo_id, const char *action)
{
	t_log		*log;
	long long	timestamp;	

	timestamp = current_time() - simulation->table->start_time;
	log = create_log(timestamp, philo_id, action);
	if (log == NULL)
		return ;
	pthread_mutex_lock(&simulation->log_mutex);
	simulation->log_lst = add_log(simulation->log_lst, log);
	pthread_mutex_unlock(&simulation->log_mutex);
}

/***
 * @brief Get the forks ids for the philosopher with its given id
 * @note We count in the time sense, so the left fork is the philosopher id
 */
void	get_forks_ids(int philo_id, int *left_fork,
	int *right_fork, int num_philosophers)
{
	*left_fork = philo_id;
	*right_fork = (philo_id - 1) % num_philosophers;
}

/**
 * @brief Check if all the philosophers are still alive
 */
int	alles_gut(t_simulation *simulation)
{
	int	i;
	long long	time;

	i = 0;
	time = 0;
	while (i < simulation->table->num_philosophers)
	{
		if (simulation->table->philosophers == NULL)
			// printf("philosophers is NULL\n");
		// printf("id : %d\n", simulation->table->philosophers[i].id);
		// t_philosopher philo = simulation->table->philosophers[i];
		time = current_time() - simulation->table->philosophers[i].last_meal_time;
		if (time > simulation->table->time_to_die)
		{
			// time = current_time() - simulation->table->philosophers[i].last_meal_time;
			// printf("%lld - philo : %d - died - time to die :\n", time, i);
 			// print_action(simulation->table, i, "died");
			log_action(simulation, i, "died");
			return (0);
		}
		i++;
	}
	return (1);
}

/***
 * @brief Check if the dinner is over
 */
int	dinner_is_over(t_simulation *simulation)
{
	int	i;

	i = 0;
	while (i < simulation->table->num_philosophers)
	{
		if (simulation->philosophers[i].times_eaten
			< simulation->philosophers[i].mini_nbr_meals)
			return (0);
		i++;
	}
	return (1);
}

int is_simulation_over(t_simulation *simulation)
{
	if (!alles_gut(simulation) || dinner_is_over(simulation))
		return (1);
	return (0);
}
