/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   starvation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 20:19:33 by azerfaou          #+#    #+#             */
/*   Updated: 2024/12/05 15:16:26 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	report_starvation(t_philosopher *philosopher)
// {
// 	t_simulation	*simulation;

// 	simulation = philosopher->simulation;
// 	log_action(simulation, philosopher->id, "is starving");
// 	pthread_mutex_lock(&simulation->starvation_mutex);
// 	simulation->someone_starving = philosopher->id + 1;
// 	// pthread_cond_signal(&simulation->starvation_done);
// 	pthread_mutex_unlock(&simulation->starvation_mutex);
// }

int	check_starvation(t_philosopher *philosopher)
{
	long long		time_left;
	long long		starvation_limit;
	t_simulation	*simulation;

	simulation = philosopher->simulation;
	starvation_limit = simulation->table->time_to_eat + 2 * MINI_TIME;
	time_left = simulation->table->time_to_die
		- (current_time() - philosopher->last_meal_time);
	if (time_left > starvation_limit)
	{
		return (0);
	}
	// if (!simulation->someone_starving)
	// 	report_starvation(philosopher);
	return (1);
}

int	is_neighbor_starving(t_philosopher *philosopher)
{
	int	starving_id;

	starving_id = philosopher->simulation->someone_starving;
	if (starving_id)
		starving_id--;
	if(ft_abs(philosopher->id - starving_id) == 1)
		return (1);
	return (0);
}

// void	wait_neighbor_to_eat(t_philosopher *philosopher)
// {
// 	int	print = 1;

// 	while(is_neighbor_starving(philosopher))
// 	{
// 		if (print)
// 			log_action(philosopher->simulation, philosopher->id, "is waiting for his neighbor to eat");
// 		print = 0;
// 		pthread_cond_wait(&philosopher->simulation->starvation_done, &philosopher->simulation->starvation_mutex);
// 	}
// 	log_action(philosopher->simulation, philosopher->id, "is not waiting anymore");
// }
