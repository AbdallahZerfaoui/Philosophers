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
	// pthread_mutex_lock(&simulation->death_mutex);
	// simulation->someone_died = philosopher->id + 1;
	// pthread_mutex_unlock(&simulation->death_mutex);
	set_someone_died(philosopher);
}

int	is_alive(t_philosopher *philosopher)
{
	long long	time_since_last_meal;
	int			nbr_meals_eaten;

	pthread_mutex_lock(&philosopher->times_eaten_mutex);
	nbr_meals_eaten = philosopher->times_eaten;
	pthread_mutex_unlock(&philosopher->times_eaten_mutex);
	time_since_last_meal = current_time() - get_last_time_meal(philosopher);
	if (time_since_last_meal > philosopher->simulation->table->time_to_die
		&& nbr_meals_eaten < philosopher->mini_nbr_meals)
	{
		return (0);
	}
	return (1);
}

/***
 * @note the condition number of philosophers >= 1 is useless
 * the first philo starts left and then we alternate
 */
void	*philosopher_routine(t_philosopher *philosopher)
{
	t_table	*table;
	int		left_fork;
	int		right_fork;
	int		side;

	table = philosopher->simulation->table;
	side = philosopher->id % 2;
	get_forks_ids(philosopher->id, &left_fork, &right_fork,
		table->num_philosophers);
	// sleep_till(philosopher->simulation->start_simulation);
	if (philosopher->id % 2 == 0)
		usleep(DELAY_AFTER_CREATION);
	while (!is_simulation_over(philosopher->simulation))
	{
		// if (table->num_philosophers >= 1)
		// {
		think(philosopher);
		// handle_greediness(*philosopher);
		take_forks(philosopher, side);
		eat(philosopher);
		get_a_nap(philosopher);
		// }
	}
	// ft_putstr("im out\n");
	unlock_my_forks(philosopher);
	return (NULL);
}
