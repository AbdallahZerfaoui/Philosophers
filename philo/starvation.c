/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   starvation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 20:19:33 by azerfaou          #+#    #+#             */
/*   Updated: 2024/12/03 20:35:16 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	report_starvation(t_philosopher *philosopher)
{
	t_simulation	*simulation;

	simulation = philosopher->simulation;
	print_action(simulation, philosopher->id, "is starving");
	pthread_mutex_lock(&simulation->starvation_mutex);
	simulation->someone_starving = philosopher->id + 1;
	// pthread_cond_signal(&simulation->starvation_done);
	pthread_mutex_unlock(&simulation->starvation_mutex);
}

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
