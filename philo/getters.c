/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:54:02 by azerfaou          #+#    #+#             */
/*   Updated: 2024/12/20 15:23:56 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_times_eaten(t_philosopher *philosopher)
{
	int	times_eaten;

	lock_safely(&philosopher->philo_mutex);
	times_eaten = philosopher->times_eaten;
	unlock_safely(&philosopher->philo_mutex);
	return (times_eaten);
}

long long	get_start_time(t_simulation *simulation)
{
	long long	start_time;

	start_time = simulation->table->start_time;
	return (start_time);
}

int	get_someone_died(t_simulation *simulation)
{
	int	someone_died;

	lock_safely(&simulation->death_mutex);
	someone_died = simulation->someone_died;
	unlock_safely(&simulation->death_mutex);
	return (someone_died);
}

/***
 * @brief Get the philosopher data
 * @note when the philo read a data he is the only one who can change it
 * we dont need to lock the mutex
 */
void	get_philo_data(t_philosopher *philosopher,
		t_philo_shared_data	*data)
{
	lock_safely(&philosopher->philo_mutex);
	data->times_eaten = philosopher->times_eaten;
	data->last_meal_time = philosopher->last_meal_time;
	unlock_safely(&philosopher->philo_mutex);
}
