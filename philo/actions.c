/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 19:48:21 by azerfaou          #+#    #+#             */
/*   Updated: 2024/12/05 20:37:54 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/***
 * @brief The philosopher takes a fork
 * if the fork is not available, the function returns 0
 */
int	take_fork_time_out(t_fork *fork, int philo_id)
{
	long long	start;

	start = current_time();
	while (current_time() - start < FORK_TIME_OUT + philo_id)
	{
		if (pthread_mutex_trylock(&fork->fork_mutex) == 0) //forbidden
		{
			return (1);
		}
	}
	return (0);
}
/***
 * @brief The philosopher takes the forks
 * so we lock the mutexes of the forks, no other philosopher can take them
 */
void	take_forks(t_philosopher *philosopher, int side)
{
	t_simulation	*simulation;
	t_table			*table;
	int				left_fork;
	int				right_fork;
	t_forks_data	forks_data;

	simulation = philosopher->simulation;
	table = simulation->table;
	get_forks_ids(philosopher->id, &forks_data.left_fork,
		&forks_data.right_fork, simulation->table->num_philosophers);
	left_fork = forks_data.left_fork;
	right_fork = forks_data.right_fork;
	sprintf(forks_data.message_left, "has taken the left fork %d", left_fork);
	sprintf(forks_data.message_right, "has taken the right fork %d",
		right_fork);
	if (is_alive(philosopher))
	{
		if (side == 0)
		{
			pthread_mutex_lock(&table->forks[left_fork].fork_mutex);
			log_action(simulation, philosopher->id, forks_data.message_left);
			pthread_mutex_lock(&table->nbr_forks_mutex);
			table->nbr_forks--;
			pthread_mutex_unlock(&table->nbr_forks_mutex);
			if (table->num_philosophers == 1)
			{
				log_action(simulation, philosopher->id, forks_data.message_left);
				sleep_ms(2 * table->time_to_die);
			}
			// log_action(simulation, philosopher->id, forks_data.message_left);
			// pthread_mutex_lock(&table->forks[right_fork].fork_mutex);
			else if (philosopher->simulation->table->num_philosophers % 2 >= 0) // != 0
			{
				if (pthread_mutex_lock(&table->forks[right_fork].fork_mutex) == 0)
				{
					log_action(simulation, philosopher->id, forks_data.message_right);
					pthread_mutex_lock(&table->nbr_forks_mutex);
					table->nbr_forks--;
					pthread_mutex_unlock(&table->nbr_forks_mutex);
				}
				else
				{
					pthread_mutex_unlock(&table->forks[left_fork].fork_mutex);
					log_action(simulation, philosopher->id, "has released the left fork"); // to remove
					pthread_mutex_lock(&table->nbr_forks_mutex);
					table->nbr_forks++;
					pthread_mutex_unlock(&table->nbr_forks_mutex);
					// log_action(simulation, philosopher->id, "has released the left fork");
					take_forks(philosopher, 0);
				}
			}
			else
			{
				pthread_mutex_lock(&table->forks[right_fork].fork_mutex);
				pthread_mutex_lock(&table->nbr_forks_mutex);
				table->nbr_forks--;
				pthread_mutex_unlock(&table->nbr_forks_mutex);
				log_action(simulation, philosopher->id, forks_data.message_right);
			}
		}
		else // side 1
		{
			pthread_mutex_lock(&table->forks[right_fork].fork_mutex);
			pthread_mutex_lock(&table->nbr_forks_mutex);
			table->nbr_forks--;
			pthread_mutex_unlock(&table->nbr_forks_mutex);
			log_action(simulation, philosopher->id, forks_data.message_right);
			pthread_mutex_lock(&table->forks[left_fork].fork_mutex);
			pthread_mutex_lock(&table->nbr_forks_mutex);
			table->nbr_forks--;
			pthread_mutex_unlock(&table->nbr_forks_mutex);
			log_action(simulation, philosopher->id, forks_data.message_left);
		}
	}
	// else
	// {
	// 	report_death(philosopher);
	// }
}
/**
 * @note last meal time is the moment when the philosopher started eating
 * and not when he finished eating
 */
void	eat(t_philosopher *philosopher)
{
	t_table			*table;
	int				left_fork;
	int				right_fork;
	t_forks_data	forks_data;

	table = philosopher->simulation->table;
	get_forks_ids(philosopher->id, &left_fork, &right_fork,
		table->num_philosophers);
	sprintf(forks_data.message_left, "has released the left fork %d",
		left_fork);
	sprintf(forks_data.message_right, "has released the right fork %d",
		right_fork);
	if (is_alive(philosopher))
	{
		philosopher->last_meal_time = current_time();
		philosopher->meal_end_time = philosopher->last_meal_time
			+ table->time_to_eat;
		philosopher->wake_up_time = philosopher->meal_end_time
			+ table->time_to_sleep;
		log_action(philosopher->simulation, philosopher->id, "is eating");
		// sleep_ms(table->time_to_eat);
		sleep_till(philosopher->meal_end_time);
		pthread_mutex_unlock(&table->forks[left_fork].fork_mutex);
		pthread_mutex_lock(&table->nbr_forks_mutex);
		table->nbr_forks++;
		pthread_mutex_unlock(&table->nbr_forks_mutex);
		// log_action(philosopher->simulation, philosopher->id,
		// 	forks_data.message_left);
		pthread_mutex_unlock(&table->forks[right_fork].fork_mutex);
		pthread_mutex_lock(&table->nbr_forks_mutex);
		table->nbr_forks++;
		pthread_mutex_unlock(&table->nbr_forks_mutex);
		// log_action(philosopher->simulation, philosopher->id,
		// 	forks_data.message_right);
		philosopher->times_eaten++;
	}
	else
	{
		// report_death(philosopher);
		pthread_mutex_unlock(&table->forks[left_fork].fork_mutex);
		pthread_mutex_unlock(&table->forks[right_fork].fork_mutex);
		pthread_mutex_lock(&table->nbr_forks_mutex);
		table->nbr_forks += 2;
		pthread_mutex_unlock(&table->nbr_forks_mutex);
	}
}

void	get_a_nap(t_philosopher *philosopher)
{
	long long	nap_duration;

	nap_duration = philosopher->simulation->table->time_to_sleep;
	if (is_alive(philosopher))
	{
		log_action(philosopher->simulation, philosopher->id, "is sleeping");
		// sleep_ms(nap_duration);
		sleep_till(philosopher->wake_up_time);
	}
	// else
	// {
	// 	report_death(philosopher);
	// }
}

void	think(t_philosopher *philosopher)
{
	// if (!is_alive(philosopher))
	// {
	// 	// report_death(philosopher);
	// 	return ;
	// }
	log_action(philosopher->simulation, philosopher->id, "is thinking");
}
