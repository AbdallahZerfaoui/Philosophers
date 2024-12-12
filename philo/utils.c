/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2024/11/29 11:39:33 by azerfaou          #+#    #+#             */
/*   Updated: 2024/12/05 12:29:51 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


// long long	current_time(void)
// {
// 	struct timeval	tv;

// 	gettimeofday(&tv, NULL);
// 	return (tv.tv_sec * 1000LL + (tv.tv_usec / 1000LL));
// }
/***
 * @brief Get the current time in milliseconds
 */
long long	current_time(void)
{
	struct timespec ts;
	long long time;

	clock_gettime(CLOCK_MONOTONIC, &ts);
		// clock_gettime is more precise than gettimeofday but forbiden in the subject
	time = (ts.tv_sec * 1000000000LL + ts.tv_nsec) / 1000000LL;
	return (time);
}

long long	current_time_us(void)
{
	struct timespec ts;
	long long time;

	clock_gettime(CLOCK_MONOTONIC, &ts);
		// clock_gettime is more precise than gettimeofday but forbiden in the subject
	time = (ts.tv_sec * 1000000000LL + ts.tv_nsec)/1000LL;
	return (time);
}

void	sleep_ms(int ms)
{
	long long start;

	start = current_time();
	if (current_time() - start < ms)
		usleep(1000LL * (ms - (current_time() - start)));
}

void	sleep_till(long long target_time)
{
	long long	diff;

	diff = target_time - current_time();
	while (diff > 1)
	{
		usleep(1000LL * (diff / 2));
		diff = target_time - current_time();
	}
	while(current_time() < target_time)
		;
}

/**

	* @note i don't know why im checking if someone died in the print_action function
 */
// void	print_action(t_simulation *simulation, int philo_id,
//		const char *action)
// {
// 	long long	timestamp;

// 	timestamp = current_time() - simulation->table->start_time;
// 	pthread_mutex_lock(&simulation->print_mutex);
// 	if (simulation->someone_died)
// 	{
// 		pthread_mutex_unlock(&simulation->print_mutex);
// 		return ;
// 	}
// 	// printf("%lld - philo : %d - %s - Nforks : %d\n", timestamp, philo_id,
// 	// 	action, simulation->table->nbr_forks);
// 	printf("%lld %d %s\n", timestamp, philo_id, action);
// 	pthread_mutex_unlock(&simulation->print_mutex);
// }
/***
 * @note should i create the log before or after locking the mutex???
 */
void	log_action(t_simulation *simulation, int philo_id, const char *action)
{
	t_log		*log;
	long long	timestamp;
	long long	start_time;

	// pthread_mutex_lock(&simulation->table->start_time_mutex);
	// timestamp = current_time() - simulation->table->start_time;
	// pthread_mutex_unlock(&simulation->table->start_time_mutex);
	start_time = get_start_time(simulation);
	timestamp = current_time() - start_time;
	log = create_log(timestamp, philo_id, action);
	if (!log)
	{
		return ;
	}
	pthread_mutex_lock(&simulation->log_mutex);
	simulation->log_lst = add_log(simulation->log_lst, log);
	pthread_mutex_unlock(&simulation->log_mutex);
}

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

/***
 * @brief Check if the dinner is over
 */
int	dinner_is_over(t_simulation *simulation)
{
	int	i;
	int	mini_nbr_meals;
	int	result;
	int	nbr_meals_eaten;

	i = 0;
	result = 1;
	mini_nbr_meals = simulation->philosophers[0].mini_nbr_meals;
	if (mini_nbr_meals == INT_MAX)
		return (0);
	while (i < simulation->table->num_philosophers)
	{
		// pthread_mutex_lock(&simulation->philosophers[i].times_eaten_mutex);
		// nbr_meals_eaten = simulation->philosophers[i].times_eaten;
		// pthread_mutex_unlock(&simulation->philosophers[i].times_eaten_mutex);
		nbr_meals_eaten = get_times_eaten(&simulation->philosophers[i]);
		if (nbr_meals_eaten < mini_nbr_meals)
		{
			result = 0;
			break ;
		}
		i++;
	}
	return (result);
}

/***
 * @brief Check if the simulation is over
 * The simulation is over if someone died or if the dinner is over
 * @note dinner_over variable is used to decrease the lock time
 */
int	is_simulation_over(t_simulation *simulation)
{
	int result;
	int dinner_over;
	int someone_died;

	dinner_over = dinner_is_over(simulation);
	someone_died = get_someone_died(simulation);
	// pthread_mutex_lock(&simulation->death_mutex);
	result = (someone_died || dinner_over);
	// pthread_mutex_unlock(&simulation->death_mutex);
	return (result);
}

void	print_simu_status(t_simulation *simulation)
{
	int i;
	int dead_id;

	dead_id = get_someone_died(simulation) - 1;
	printf("someone died : %d\n", dead_id);
	// printf("someone is starving : %d\n", simulation->someone_starving - 1);
	if (get_someone_died(simulation))
	{
		i = simulation->someone_died - 1;
		printf("last meal of %d at %lld\n", i,
			get_last_time_meal(&simulation->philosophers[i]) - get_start_time(simulation));
	}
	printf("dinner is over : %d\n", dinner_is_over(simulation));
	// printf("nbr of meals eaten by 0: %d\n",
	// 	simulation->philosophers[0].times_eaten);
	printf("nbr of meals eaten by each philosopher : ");
	for (int i = 0; i < simulation->table->num_philosophers; i++)
	{
		printf("%d ", simulation->philosophers[i].times_eaten);
		if (i == simulation->table->num_philosophers - 1)
			printf("\n");
	}
	// printf("forks status : ");
	// for (int i = 0; i < simulation->table->num_philosophers; i++)
	// {
	// 	printf("%d ", simulation->table->forks[i].owner);
	// 	if (i == simulation->table->num_philosophers - 1)
	// 		printf("\n");
	// }
}


