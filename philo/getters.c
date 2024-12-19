/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:54:02 by azerfaou          #+#    #+#             */
/*   Updated: 2024/12/19 15:47:57 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_last_time_meal(t_philosopher *philosopher)
{
	long long	last_time_meal;

	lock_safely(&philosopher->philo_mutex);
	last_time_meal = philosopher->last_meal_time;
	unlock_safely(&philosopher->philo_mutex);
	return (last_time_meal);
}

// long long	get_meal_end_time(const t_philosopher *philosopher)
// {
// 	long long	meal_end_time;

// 	meal_end_time = philosopher->meal_end_time;
// 	return (meal_end_time);
// }

// long long	get_wake_up_time(const t_philosopher *philosopher)
// {
// 	long long	wake_up_time;

// 	wake_up_time = philosopher->wake_up_time;
// 	return (wake_up_time);
// }

// t_log	*get_log_lst(t_simulation *simulation)
// {
// 	t_log	*log_lst;

// 	lock_safely(&simulation->log_mutex);
// 	log_lst = simulation->log_lst;
// 	unlock_safely(&simulation->log_mutex);
// 	return (log_lst);
// }

int	get_times_eaten(t_philosopher *philosopher)
{
	int	times_eaten;

	lock_safely(&philosopher->philo_mutex);
	times_eaten = philosopher->times_eaten;
	unlock_safely(&philosopher->philo_mutex);
	return (times_eaten);
}

long long 		get_start_time(t_simulation *simulation)
{
	long long	start_time;

	// lock_safely(&simulation->table->start_time_mutex);
	start_time = simulation->table->start_time;
	// unlock_safely(&simulation->table->start_time_mutex);
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
	// t_philo_shared_data	*data;

	// data = (t_philo_shared_data *)malloc(sizeof(t_philo_shared_data));
	// if (data == NULL)
	// 	return (NULL);
	lock_safely(&philosopher->philo_mutex);
	data->times_eaten = philosopher->times_eaten;
	data->last_meal_time = philosopher->last_meal_time;
	unlock_safely(&philosopher->philo_mutex);
	// return (data);
}
