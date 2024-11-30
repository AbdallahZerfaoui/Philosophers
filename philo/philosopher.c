/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 17:56:50 by azerfaou          #+#    #+#             */
/*   Updated: 2024/11/30 20:50:45 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/***
 * @brief The philosopher takes the forks
 * so we lock the mutexes of the forks, no other philosopher can take them
 */
static void	take_forks(t_philosopher *philosopher, int side)
{
	t_table	*table;
	int		left_fork;
	int		right_fork;

	table = philosopher->simulation->table;
	get_forks_ids(philosopher->id, &left_fork, &right_fork,
		table->num_philosophers);
	if (side == 0)
	{
		pthread_mutex_lock(&table->forks[left_fork].mutex);
		// print_action(table, philosopher->id, "has taken the left fork");
		log_action(philosopher->simulation, philosopher->id,
			"has taken the left fork");
		pthread_mutex_lock(&table->forks[right_fork].mutex);
		// print_action(table, philosopher->id, "has taken the right fork");
		log_action(philosopher->simulation, philosopher->id,
			"has taken the right fork");
	}
	else
	{
		pthread_mutex_lock(&table->forks[right_fork].mutex);
		// print_action(table, philosopher->id, "has taken the right fork");
		log_action(philosopher->simulation, philosopher->id,
			"has taken the right fork");
		pthread_mutex_lock(&table->forks[left_fork].mutex);
		// print_action(table, philosopher->id, "has taken the left fork");
		log_action(philosopher->simulation, philosopher->id,
			"has taken the left fork");
	}
}

static void	eat(t_philosopher *philosopher)
{
	t_table	*table;
	int		left_fork;
	int		right_fork;

	table = philosopher->simulation->table;
	get_forks_ids(philosopher->id, &left_fork, &right_fork,
		table->num_philosophers);
	// print_action(table, philosopher->id, "is eating");
	log_action(philosopher->simulation, philosopher->id, "is eating");
	sleep_ms(table->time_to_eat);
	philosopher->last_meal_time = current_time();
	pthread_mutex_unlock(&table->forks[left_fork].mutex);
	log_action(philosopher->simulation, philosopher->id,
		"has released the left fork");
	pthread_mutex_unlock(&table->forks[right_fork].mutex);
	log_action(philosopher->simulation, philosopher->id,
		"has released the right fork");
	philosopher->times_eaten++;
}

static void	get_a_nap(t_philosopher *philosopher)
{
	t_table	*table;

	table = philosopher->simulation->table;
	// print_action(table, philosopher->id, "is sleeping");
	log_action(philosopher->simulation, philosopher->id, "is sleeping");
	sleep_ms(table->time_to_sleep);
}

static void	think(t_philosopher *philosopher, int time_to_think)
{
	t_table	*table;

	table = philosopher->simulation->table;
	// print_action(table, philosopher->id, "is thinking");
	log_action(philosopher->simulation, philosopher->id, "is thinking");
	sleep_ms(time_to_think);
}

void	*philosopher_routine(t_philosopher *philosopher)
{
	t_table	*table;
	int		left_fork;
	int		right_fork;
	int		time_to_think;

	time_to_think = TIME_TO_THINK;
	table = philosopher->simulation->table;
	get_forks_ids(philosopher->id, &left_fork, &right_fork,
		table->num_philosophers);
	while (1)
	{
		take_forks(philosopher, philosopher->id % 2);
		eat(philosopher);
		get_a_nap(philosopher);
		think(philosopher, time_to_think);       
	}
	return (NULL);
}
