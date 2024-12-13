/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:10:30 by azerfaou          #+#    #+#             */
/*   Updated: 2024/12/13 21:12:43 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/***
 * @brief The philosopher takes a fork and set the ownernship of it
 * when he finishes eating, he releases the fork and set the owner to -1
 * @param philosopher the philosopher
 * @param action 1 for take, -1 for release
 * @return the old owner id because it's needed in the function unlock_my_forks
 */
// int	set_fork_owner(t_philosopher *philosopher, int fork_id, int action)
// {
// 	t_table *table;
// 	int		old_owner_id;

// 	old_owner_id = -1;
// 	table = philosopher->simulation->table;
// 	pthread_mutex_lock(&table->forks[fork_id].owner_mutex);
// 	if (action == TAKE)
// 	{
// 		if (table->forks[fork_id].owner == -1)
// 			table->forks[fork_id].owner = philosopher->id;
// 	}
// 	else if (action == RELEASE)
// 	{
// 		if (table->forks[fork_id].owner == philosopher->id)
// 		{
// 			table->forks[fork_id].owner = -1;
// 			old_owner_id = philosopher->id;
// 		}
// 	}
// 	pthread_mutex_unlock(&table->forks[fork_id].owner_mutex);
// 	return (old_owner_id);
// }

/***
 * @brief The philosopher takes a fork and set the variables left_fork and right_fork
 * when he finishes eating, he releases the fork variables to -1
 * @param philosopher the philosopher
 * @param action 1 for take, -1 for release
 */
void	set_fork_owner(int *fork, int fork_id, int action)
{
	if (action == TAKE && *fork == -1)
	{
		*fork = fork_id;
	}
	else if (action == RELEASE && *fork != -1)
	{
		*fork = -1;
	}
}

void	set_start_time(t_simulation *simulation)
{
	lock_safely(&simulation->table->start_time_mutex);
	simulation->table->start_time = current_time();
	unlock_safely(&simulation->table->start_time_mutex);
}

void	set_last_time_meal(t_philosopher *philosopher)
{
	lock_safely(&philosopher->philo_mutex);
	philosopher->last_meal_time = current_time();
	unlock_safely(&philosopher->philo_mutex);
}

void	set_eaten_meals(t_philosopher *philosopher, int increment)
{
	lock_safely(&philosopher->philo_mutex);
	philosopher->times_eaten += increment;
	unlock_safely(&philosopher->philo_mutex);
}

void	set_wake_up_time(t_philosopher *philosopher)
{
	const t_table	*table;

	table = philosopher->simulation->table;
	// pthread_mutex_lock(&philosopher->wake_up_time_mutex);
	philosopher->wake_up_time = philosopher->meal_end_time
		+ table->time_to_sleep;
	// pthread_mutex_unlock(&philosopher->wake_up_time_mutex);
}

void	set_philo_times(t_philosopher *philosopher)
{
	t_table *table;

	table = philosopher->simulation->table;
	lock_safely(&philosopher->philo_mutex);
	philosopher->last_meal_time = current_time();
	philosopher->meal_end_time = philosopher->last_meal_time
		+ table->time_to_eat;
	philosopher->wake_up_time = philosopher->meal_end_time + table->time_to_sleep;
	unlock_safely(&philosopher->philo_mutex);
}

void	set_meal_end_time(t_philosopher *philosopher)
{
	const t_table	*table;

	table = philosopher->simulation->table;
	// pthread_mutex_lock(&philosopher->meal_end_time_mutex);
	philosopher->meal_end_time = philosopher->last_meal_time
		+ table->time_to_eat;
	// pthread_mutex_unlock(&philosopher->meal_end_time_mutex);
}

void set_someone_died(t_philosopher *philosopher)
{
	t_simulation	*simulation;

	simulation = philosopher->simulation;
	lock_safely(&simulation->death_mutex);
	simulation->someone_died = philosopher->id + 1;
	unlock_safely(&simulation->death_mutex);
}
