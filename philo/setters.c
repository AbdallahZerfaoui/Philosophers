/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:10:30 by azerfaou          #+#    #+#             */
/*   Updated: 2025/01/24 17:22:46 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/***
 * @brief The philosopher takes a fork and set
 * the variables left_fork and right_fork
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

void	set_last_time_meal(t_philosopher *philosopher)
{
	lock_safely(&philosopher->philo_mutex);
	philosopher->last_meal_time = current_time_us();
	unlock_safely(&philosopher->philo_mutex);
}

void	set_eaten_meals(t_philosopher *philosopher, int increment)
{
	lock_safely(&philosopher->philo_mutex);
	philosopher->times_eaten += increment;
	unlock_safely(&philosopher->philo_mutex);
}

void	set_philo_times(t_philosopher *philosopher)
{
	const t_table	*table;

	table = philosopher->simulation->table;
	lock_safely(&philosopher->philo_mutex);
	philosopher->last_meal_time = current_time_us();
	philosopher->meal_end_time = philosopher->last_meal_time / 1000LL
		+ table->time_to_eat;
	philosopher->wake_up_time = philosopher->meal_end_time
		+ table->time_to_sleep;
	unlock_safely(&philosopher->philo_mutex);
}

void	set_someone_died(t_philosopher *philosopher)
{
	t_simulation	*simulation;

	simulation = philosopher->simulation;
	lock_safely(&simulation->death_mutex);
	simulation->someone_died = philosopher->id + 1;
	unlock_safely(&simulation->death_mutex);
}
