/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 15:32:29 by azerfaou          #+#    #+#             */
/*   Updated: 2025/01/24 17:21:10 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	report_death(t_philosopher *philosopher)
{
	t_simulation	*simulation;

	simulation = philosopher->simulation;
	set_someone_died(philosopher);
	log_action(simulation, philosopher->id, "died", RED);
}

/***
 *@note the difference between im alive and is alive is that im alive takes 
 the last meal time from the philosopher structure
 without using the mutex, while is alive uses the getter 
 function to get the last meal time
 */
int	im_alive(const t_philosopher *philosopher)
{
	long long	time_since_last_meal;

	time_since_last_meal = (current_time_us() - philosopher->last_meal_time) / 1000LL;
	if (time_since_last_meal > philosopher->simulation->table->time_to_die
		|| (time_since_last_meal == philosopher->simulation->table->time_to_die && !philosopher->is_eating))
	{
		return (0);
	}
	return (1);
}

int	is_alive(const t_simulation *simulation, const t_philo_shared_data *data)
{
	long long	time_since_last_meal;

	time_since_last_meal = (current_time_us() - data->last_meal_time) / 1000LL;
	if (time_since_last_meal > simulation->table->time_to_die)
	{
		return (0);
	}
	return (1);
}
