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

void	try_take_fork(t_philosopher *philosopher,
	int fork_id, int *fork)
{
	t_table	*table;

	table = philosopher->simulation->table;
	lock_safely(&table->forks[fork_id].fork_mutex);
	set_fork_owner(fork, fork_id, TAKE);
	log_action(philosopher->simulation, philosopher->id, "has taken a fork");
}

void	release_fork(t_philosopher *philosopher, int fork_id, int *fork)
{
	t_table	*table;

	table = philosopher->simulation->table;
	unlock_safely(&table->forks[fork_id].fork_mutex);
	set_fork_owner(fork, fork_id, RELEASE);
}

void	handle_single_philosopher(const t_table *table)
{
	sleep_ms(2 * table->time_to_die);
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

	simulation = philosopher->simulation;
	table = simulation->table;
	get_forks_ids(philosopher->id, &left_fork, &right_fork,
		table->num_philosophers);
	if (!im_alive(philosopher))
		return ;
	if (table->num_philosophers == 1)
	{
		try_take_fork(philosopher, left_fork, &philosopher->left_fork);
		handle_single_philosopher(table);
		return ;
	}
	if (side == 0)
	{
		try_take_fork(philosopher, left_fork, &philosopher->left_fork);
		try_take_fork(philosopher, right_fork, &philosopher->right_fork);
		philosopher->is_eating = 1;
		// if (lock_safely(&table->forks[right_fork].fork_mutex) == 0)
		// {
		// 	set_fork_owner(&philosopher->right_fork, right_fork, TAKE);
		// 	log_action(simulation, philosopher->id, "has taken a fork");
		// 	philosopher->is_eating = 1;
		// }
		// else
		// {
		// 	release_fork(philosopher, left_fork, &philosopher->left_fork);
		// 	take_forks(philosopher, 0);
		// }
	}
	else
	{
		try_take_fork(philosopher, right_fork, &philosopher->right_fork);
		try_take_fork(philosopher, left_fork, &philosopher->left_fork);
		philosopher->is_eating = 1;
	}
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

	table = philosopher->simulation->table;
	get_forks_ids(philosopher->id, &left_fork, &right_fork,
		table->num_philosophers);
	if (im_alive(philosopher))
	{
		set_philo_times(philosopher);
		log_action(philosopher->simulation, philosopher->id, "is eating");
		sleep_till(philosopher->meal_end_time);
		release_fork(philosopher, left_fork, &philosopher->left_fork);
		release_fork(philosopher, right_fork, &philosopher->right_fork);
		philosopher->is_eating = 0;
		set_eaten_meals(philosopher, 1);
	}
	else if (philosopher->is_eating)
		unlock_my_forks(philosopher);
}

void	get_a_nap(t_philosopher *philosopher)
{
	if (im_alive(philosopher))
	{
		log_action(philosopher->simulation, philosopher->id, "is sleeping");
		sleep_till(philosopher->wake_up_time);
	}
}

void	think(t_philosopher *philosopher)
{
	if (im_alive(philosopher))
		log_action(philosopher->simulation, philosopher->id, "is thinking");
}

void	unlock_my_forks(t_philosopher *philosopher)
{
	t_simulation	*simulation;
	int				left_fork;
	int				right_fork;

	simulation = philosopher->simulation;
	left_fork = philosopher->left_fork;
	right_fork = philosopher->right_fork;
	if (left_fork != -1)
	{
		philosopher->left_fork
			= unlock_safely(&simulation->table->forks[left_fork].fork_mutex);
	}
	if (right_fork != -1)
	{
		philosopher->right_fork
			= unlock_safely(&simulation->table->forks[right_fork].fork_mutex);
	}
}

