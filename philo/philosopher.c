/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 17:56:50 by azerfaou          #+#    #+#             */
/*   Updated: 2024/12/05 20:14:58 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	report_death(t_philosopher *philosopher)
{
	t_simulation	*simulation;

	simulation = philosopher->simulation;
	log_action(simulation, philosopher->id, "died");
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
		// handle_greediness(*philosopher);
		take_forks(philosopher, 0);
		eat(philosopher);
		get_a_nap(philosopher);
		// }
	}
	return (NULL);
}
