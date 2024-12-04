/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 11:39:33 by azerfaou          #+#    #+#             */
/*   Updated: 2024/12/04 16:32:07 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// long long	current_time(void)
// {
// 	struct timeval	tv;

// 	gettimeofday(&tv, NULL);
// 	return (tv.tv_sec * 1000LL + (tv.tv_usec / 1000LL));
// }
long long	current_time(void)
{
	struct timespec	ts;
	long long		time;

	clock_gettime(CLOCK_MONOTONIC, &ts); // clock_gettime is more precise than gettimeofday but forbiden in the subject
	time = (ts.tv_sec * 1000000000LL + ts.tv_nsec) / 1000000LL;
	return (time);
}

void	sleep_ms(int ms)
{
	long long	start;

	start = current_time();
	if (current_time() - start < ms)
		usleep(1000LL * (ms - (current_time() - start)));
}

/**
 * @note i don't know why im checking if someone died in the print_action function
 */
void	print_action(t_simulation *simulation, int philo_id, const char *action)
{
	long long	timestamp;

	timestamp = current_time() - simulation->table->start_time;
	pthread_mutex_lock(&simulation->print_mutex);
	if (simulation->someone_died)
	{
		pthread_mutex_unlock(&simulation->print_mutex);
		return ;
	}
	printf("%lld - philo : %d - %s - Nforks : %d\n", timestamp, philo_id,
		action, simulation->table->nbr_forks);
	// if (timestamp < 0)
	// {
	// 	pthread_mutex_unlock(&simulation->print_mutex);
	// 	exit(1);
	// }
	pthread_mutex_unlock(&simulation->print_mutex);
}

// void	log_action(t_simulation *simulation, int philo_id, const char *action)
// {
// 	t_log		*log;
// 	long long	timestamp;

// 	timestamp = current_time() - simulation->table->start_time;
// 	log = create_log(timestamp, philo_id, action);
// 	if (log == NULL)
// 		return ;
// 	pthread_mutex_lock(&simulation->log_mutex);
// 	simulation->log_lst = add_log(simulation->log_lst, log);
// 	pthread_mutex_unlock(&simulation->log_mutex);
// }

/***
 * @brief Get the forks ids for the philosopher with its given id
 * @note We count in the time sense, so the left fork is the philosopher id
 */
void	get_forks_ids(int philo_id, int *left_fork, int *right_fork,
		int num_philosophers)
{
	*left_fork = philo_id;
	*right_fork = (philo_id + num_philosophers - 1) % num_philosophers;
}

/**
 * @brief Check if all the philosophers are still alive
//  */
// int	alles_gut(t_simulation *simulation)
// {
// 	int			i;
// 	long long	time;

// 	i = 0;
// 	time = 0;
// 	while (i < simulation->table->num_philosophers)
// 	{
// 		if (simulation->table->philosophers == NULL)
// 			// printf("philosophers is NULL\n");
// 			// printf("id : %d\n", simulation->table->philosophers[i].id);
// 			// t_philosopher philo = simulation->table->philosophers[i];
// 			time = current_time()
// - simulation->table->philosophers[i].last_meal_time;
// 		if (time > simulation->table->time_to_die)
// 		{
// 			time = current_time()
// - simulation->table->philosophers[i].last_meal_time;
// 			// printf("%lld - philo : %d - died - time to die :\n", time, i);
// 			// print_action(simulation->table, i, "died");
// 			print_action(simulation, i, "died");
// 			return (0);
// 		}
// 		i++;
// 	}
// 	return (1);
// }

/***
 * @brief Check if the dinner is over
 */
int	dinner_is_over(t_simulation *simulation)
{
	int	i;
	int	mini_nbr_meals;

	i = 0;
	mini_nbr_meals = simulation->philosophers[0].mini_nbr_meals;
	if (mini_nbr_meals == INT_MAX)
		return (0);
	while (i < simulation->table->num_philosophers)
	{
		if (simulation->philosophers[i].times_eaten < mini_nbr_meals)
			return (0);
		i++;
	}
	return (1);
}

int	is_simulation_over(t_simulation *simulation)
{
	if (simulation->someone_died || dinner_is_over(simulation))
		return (1);
	return (0);
}

void	print_simu_status(t_simulation *simulation)
{
	int	i;
	int	dead_id;

	dead_id = simulation->someone_died - 1;
	printf("someone died : %d\n", dead_id);
	printf("someone is starving : %d\n", simulation->someone_starving - 1);
	if (simulation->someone_died)
	{
		i = simulation->someone_died - 1;
		printf("last meal of %d at %lld\n", i,
			simulation->philosophers[i].last_meal_time
			- simulation->table->start_time);
	}
	printf("dinner is over : %d\n", dinner_is_over(simulation));
	printf("nbr of meals eaten by 0: %d\n",
		simulation->philosophers[0].times_eaten);
}


void	handle_greediness(t_philosopher philosopher)
{
	long long	ref_time;
	long long	now;
	long long	margin;
	long long	time_left;

	ref_time = philosopher.times_eaten * (philosopher.simulation->table->time_to_eat
			+ philosopher.simulation->table->time_to_sleep);
	now = current_time() - philosopher.simulation->table->start_time;
	margin = philosopher.simulation->table->time_to_eat / 4;
	time_left = philosopher.simulation->table->time_to_die - (current_time() - philosopher.last_meal_time);
	if (now > margin && ft_abs(now - ref_time) < margin && time_left > margin)
	{
		print_action(philosopher.simulation, philosopher.id, "is greedy");
		sleep_ms(GREEDINESS);
	}
}


