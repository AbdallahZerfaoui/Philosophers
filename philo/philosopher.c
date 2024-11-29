/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 17:56:50 by azerfaou          #+#    #+#             */
/*   Updated: 2024/11/29 18:35:02 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/***
 * @brief The philosopher takes the forks
 * so we lock the mutexes of the forks, no other philosopher can take them
 */
static void	take_forks(t_philosopher *philosopher)
{
	t_table	*table;
	int		left_fork;
	int		right_fork;

	table = philosopher->table;
	get_forks_ids(philosopher->id,
		&left_fork, &right_fork, table->num_philosophers);
	pthread_mutex_lock(&table->forks[left_fork].mutex);
	print_action(table, philosopher->id, "has taken a fork");
	pthread_mutex_lock(&table->forks[right_fork].mutex);
	print_action(table, philosopher->id, "has taken a fork");
}

static void	eat(t_philosopher *philosopher)
{
	t_table	*table;
	int		left_fork;
	int		right_fork;

	table = philosopher->table;
	get_forks_ids(philosopher->id,
		&left_fork, &right_fork, table->num_philosophers);
	print_action(table, philosopher->id, "is eating");
	sleep_ms(table->time_to_eat);
	philosopher->last_meal_time = current_time();
	pthread_mutex_unlock(&table->forks[left_fork].mutex);
	pthread_mutex_unlock(&table->forks[right_fork].mutex);
}

static void	get_a_nap(t_philosopher *philosopher)
{
	t_table	*table;

	table = philosopher->table;
	print_action(table, philosopher->id, "is sleeping");
	sleep_ms(table->time_to_sleep);
}

static void	think(t_philosopher *philosopher, int time_to_think)
{
	t_table	*table;

	table = philosopher->table;
	print_action(table, philosopher->id, "is thinking");
	sleep_ms(time_to_think);
}

void	*philosopher_routine(t_philosopher *philosopher)
{
	t_table	*table;
	int		left_fork;
	int		right_fork;
	int		time_to_think;

	time_to_think = TIME_TO_THINK;
	table = philosopher->table;
	get_forks_ids(philosopher->id,
		&left_fork, &right_fork, table->num_philosophers);
	while (1)
	{
		take_forks(philosopher);
		eat(philosopher);
		get_a_nap(philosopher);
		think(philosopher, time_to_think);
	}
	return (NULL);
}
