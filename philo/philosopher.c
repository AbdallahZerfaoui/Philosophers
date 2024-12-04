/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 17:56:50 by azerfaou          #+#    #+#             */
/*   Updated: 2024/12/04 20:46:52 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	report_death(t_philosopher *philosopher)
{
	t_simulation	*simulation;

	simulation = philosopher->simulation;
	print_action(simulation, philosopher->id, "died");
	pthread_mutex_lock(&simulation->death_mutex);
	simulation->someone_died = philosopher->id + 1;
	pthread_mutex_unlock(&simulation->death_mutex);
}

int	is_alive(t_philosopher *philosopher)
{
	long long	time_since_last_meal;

	time_since_last_meal = current_time() - philosopher->last_meal_time;
	if (time_since_last_meal > philosopher->simulation->table->time_to_die
		&& philosopher->times_eaten < philosopher->mini_nbr_meals)
	{
		return (0);
	}
	return (1);
}

int	take_fork_time_out(t_fork *fork, int philo_id)
{
	long long	start;

	start = current_time();
	while (current_time() - start < FORK_TIME_OUT + philo_id)
	{
		if (pthread_mutex_trylock(&fork->fork_mutex) == 0)
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
static void	take_forks(t_philosopher *philosopher, int side)
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
			pthread_mutex_lock(&table->nbr_forks_mutex);
			table->nbr_forks--;
			pthread_mutex_unlock(&table->nbr_forks_mutex);
			print_action(simulation, philosopher->id, forks_data.message_left);
			// pthread_mutex_lock(&table->forks[right_fork].fork_mutex);
			if (philosopher->simulation->table->num_philosophers % 2 != 0)
			{
				if (take_fork_time_out(&table->forks[right_fork], philosopher->id))
				{
					print_action(simulation, philosopher->id, forks_data.message_right);
					pthread_mutex_lock(&table->nbr_forks_mutex);
					table->nbr_forks--;
					pthread_mutex_unlock(&table->nbr_forks_mutex);
				}
				else
				{
					pthread_mutex_unlock(&table->forks[left_fork].fork_mutex);
					pthread_mutex_lock(&table->nbr_forks_mutex);
					table->nbr_forks++;
					pthread_mutex_unlock(&table->nbr_forks_mutex);
					// print_action(simulation, philosopher->id, "has released the left fork");
					take_forks(philosopher, 0);
				}
			}
			else
			{
				pthread_mutex_lock(&table->forks[right_fork].fork_mutex);
				pthread_mutex_lock(&table->nbr_forks_mutex);
				table->nbr_forks--;
				pthread_mutex_unlock(&table->nbr_forks_mutex);
				print_action(simulation, philosopher->id, forks_data.message_right);
			}
		}
		else
		{
			pthread_mutex_lock(&table->forks[right_fork].fork_mutex);
			pthread_mutex_lock(&table->nbr_forks_mutex);
			table->nbr_forks--;
			pthread_mutex_unlock(&table->nbr_forks_mutex);
			print_action(simulation, philosopher->id, forks_data.message_right);
			pthread_mutex_lock(&table->forks[left_fork].fork_mutex);
			pthread_mutex_lock(&table->nbr_forks_mutex);
			table->nbr_forks--;
			pthread_mutex_unlock(&table->nbr_forks_mutex);
			print_action(simulation, philosopher->id, forks_data.message_left);
		}
	}
	else
	{
		report_death(philosopher);
	}
}
/**
 * @note last meal time is the moment when the philosopher started eating
 * and not when he finished eating
 */
static void	eat(t_philosopher *philosopher)
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
		print_action(philosopher->simulation, philosopher->id, "is eating");
		philosopher->last_meal_time = current_time();
		sleep_ms(table->time_to_eat);
		pthread_mutex_unlock(&table->forks[left_fork].fork_mutex);
		pthread_mutex_lock(&table->nbr_forks_mutex);
		table->nbr_forks++;
		pthread_mutex_unlock(&table->nbr_forks_mutex);
		print_action(philosopher->simulation, philosopher->id,
			forks_data.message_left);
		pthread_mutex_unlock(&table->forks[right_fork].fork_mutex);
		pthread_mutex_lock(&table->nbr_forks_mutex);
		table->nbr_forks++;
		pthread_mutex_unlock(&table->nbr_forks_mutex);
		print_action(philosopher->simulation, philosopher->id,
			forks_data.message_right);
		philosopher->times_eaten++;
	}
	else
	{
		report_death(philosopher);
		pthread_mutex_unlock(&table->forks[left_fork].fork_mutex);
		pthread_mutex_unlock(&table->forks[right_fork].fork_mutex);
		pthread_mutex_lock(&table->nbr_forks_mutex);
		table->nbr_forks += 2;
		pthread_mutex_unlock(&table->nbr_forks_mutex);
	}
}

static void	get_a_nap(t_philosopher *philosopher)
{
	long long	nap_duration;

	nap_duration = philosopher->simulation->table->time_to_sleep;
	if (is_alive(philosopher))
	{
		print_action(philosopher->simulation, philosopher->id, "is sleeping");
		sleep_ms(nap_duration);
	}
	else
	{
		report_death(philosopher);
	}
}

static void	think(t_philosopher *philosopher)
{
	if (!is_alive(philosopher))
	{
		report_death(philosopher);
		return ;
	}
	print_action(philosopher->simulation, philosopher->id, "is thinking");
}

/***
 * @note the condition number of philosophers >= 1 is useless
 */
void	*philosopher_routine(t_philosopher *philosopher)
{
	t_table	*table;
	int		left_fork;
	int		right_fork;

	table = philosopher->simulation->table;
	get_forks_ids(philosopher->id, &left_fork, &right_fork,
		table->num_philosophers);
	while (!is_simulation_over(philosopher->simulation))
	{
		// if (table->num_philosophers >= 1)
		// {
		think(philosopher);
		handle_greediness(*philosopher);
		take_forks(philosopher, 0);
		eat(philosopher);
		get_a_nap(philosopher);
		// }
	}
	return (NULL);
}
